
#include "bircd.h"

int	main(int ac, char **av)
{
  t_env	e;

	printf("main\n");
  init_env(&e);
  get_opt(&e, ac, av);
  srv_create(&e, e.port);
	printf("main\n");
  main_loop(&e);

  return (0);
}
