#include "stdio.h"
#include "unistd.h"
#include "chasher.h"

void handle(int nb)
{
	void *ctx;

	ctx = hasher_create();
	struct pollfd cls;

	cls.fd = hasher_getfd(ctx);
	for (int i = 0; i < nb; ++i)
	{
		// poll(&cls, 1, -1);
		read(hasher_getfd(ctx), NULL, 8);
		hasher_update(ctx, "Henlo", strlen("Henlo"));
	}
	printf("%3d: %s\n", nb, hasher_result(ctx));
	hasher_destroy(ctx);
}

int main(int argc, char const *argv[])
{
	handle(150000);
	return 0;
}