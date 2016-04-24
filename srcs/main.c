#include "lem-in.h"

void	ft_error(char *s)
{
	ft_putstr("Error : ");
	ft_putendl(s);
	exit(1);
}

void	init(t_env *e)
{
	e->rooms = NULL;
	e->read = NULL;
}

int		main()
{
	t_env	e;

	init(&e);
	parser(&e);
	solver(&e);
	return (0);
}