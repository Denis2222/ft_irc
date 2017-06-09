
#include "bircd.h"

void	main_loop(t_env *e)
{
	printf("\nmain_loop:\n");
  while (1)
    {
      init_fd(e);
      do_select(e);
      check_fd(e);
    }
}
