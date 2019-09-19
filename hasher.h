#ifndef _HASHER_HPP
# define _HASHER_HPP
# include <openssl/md5.h>
# include <pthread.h>
# include <gmodule.h>
# include <poll.h>

# define TOKENS 8

typedef struct	action
{
	char *data;
	int bytes;
}				action_t;

class Hasher
{
	public:
		Hasher();
		static void *worker(void *obj);
		void Update(char *data, int bytes);
		int QueueStatus();
		char *Result();
		~Hasher();
		MD5_CTX ctx;
		char *out;
		pthread_t thr;
		pthread_cond_t cond;
		pthread_mutex_t mutex;
		int running;
		struct pollfd pfd;
		GAsyncQueue *queue_in;
		int working;
};

#endif
