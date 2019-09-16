#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <gmodule.h>
#include <glib.h>
#include "hasher.h"
#include "chasher.h"

void *hasher_create(void)
{
	Hasher *obj	= new Hasher();
	return obj;
}

int hasher_getfd(void *obj)
{
	if (obj == NULL)
		return 0;
	Hasher *o;
	o = static_cast<Hasher*>((Hasher*)obj);
	return o->pfd.fd;
}


void hasher_update(void *obj, char *data, int bytes)
{
	if (obj == NULL)
		return ;
	Hasher *o;
	o = static_cast<Hasher*>((Hasher*)obj);
	o->Update(data, bytes);
}

char *hasher_result(void *obj)
{
	if (obj == NULL)
		return NULL;
	Hasher *o;
	o = static_cast<Hasher*>((Hasher*)obj);
	return o->Result();
}

void hasher_destroy(void *obj)
{
	if (obj == NULL)
		return ;
	Hasher *o;
	o = static_cast<Hasher*>((Hasher*)obj);
	delete o;
}
