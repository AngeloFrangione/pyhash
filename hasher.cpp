#include <stdlib.h>
#include <sys/eventfd.h>
#include <gmodule.h>
#include <stdio.h>
#include <unistd.h>
#include "hasher.h"

void *Hasher::worker(void *o)
{
	uint64_t u = strtoull("1", NULL, 0);
	Hasher *obj = (Hasher*)o;

	while (obj->running)
	{
		action_t *a;
		if (g_async_queue_length(obj->queue_in))
		{
			obj->working = 1;
			if ((a = (action_t*)g_async_queue_pop(obj->queue_in)))
			{
				if (!a->data[0])
				{
					obj->running = 0;
					obj->working = 0;
					close(obj->pfd.fd);
					free(a->data);
					free(a);
					break;
				}
				MD5_Update(&(obj->ctx), a->data, a->bytes);
				free(a->data);
				write(obj->pfd.fd, &u, 8);
				free(a);
			}
		}
		else
		{
			obj->working = 0;
			pthread_cond_wait(&(obj->cond), &(obj->mutex));
		}
	}
	return obj;
}

Hasher::Hasher()
{
	MD5_Init(&ctx);
	pthread_create(&thr, NULL, Hasher::worker, this);
	running		= 1;
	working		= 0;
	cond 		= PTHREAD_COND_INITIALIZER;
	mutex		= PTHREAD_MUTEX_INITIALIZER;
	queue_in	= g_async_queue_new();
	pfd.fd		= eventfd(TOKENS, EFD_CLOEXEC | EFD_SEMAPHORE);
	pfd.events	= POLLIN;
}

void Hasher::Update(char *data, int bytes)
{
	action_t *a;

	a = (action_t*)calloc(sizeof(action_t), 1);
	if (!a)
		return ;
	working = 1;
	a->data = strdup(data);
	a->bytes = bytes;
	g_async_queue_push(queue_in, a);
	pthread_cond_signal(&cond);
}

int Hasher::QueueStatus()
{
	return (g_async_queue_length(queue_in) >= TOKENS);
}


char *Hasher::Result()
{
	static char out[33];
	unsigned char digest[16];

	while(working)
		usleep(10000);
	running = 0;
	pthread_cond_signal(&cond);
	pthread_join(thr, NULL);

	MD5_Final(digest, &ctx);
	for (int i = 0; i < 16; ++i)
		snprintf(&(out[i * 2]), 16 * 2, "%02x", (unsigned int)digest[i]);	
	return out;
}

Hasher::~Hasher()
{
	close(pfd.fd);
	g_async_queue_unref(queue_in);
}
