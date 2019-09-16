#ifndef _HASHER_H
# define _HASHER_H
# ifdef __cplusplus
extern "C"
{
# endif
# include "hasher.h"
# include <glib.h>
# include <gmodule.h>

void		*hasher_create(void);
int			hasher_getfd(void *context);
void		hasher_update(void *context, char *data, int bytes);
char		*hasher_result(void *context);
void		hasher_destroy(void *context);

# ifdef __cplusplus
}
# endif
#endif
