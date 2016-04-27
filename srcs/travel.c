#include "lem-in.h"
#include <stdio.h>
#include <unistd.h>

int		count_rooms(t_env *e)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = e->path;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
int		count_rooms_occupied(t_env *e)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = e->path;
	while (tmp)
	{
		if (((t_room*)(tmp->data))->ant > 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}*/

void	print(t_list *path)
{
	t_list	*tmp;
	t_room	*room;

	tmp = path;
	while (tmp)
	{
		room = ((t_room*)(tmp->data));
		if (room->ant > 0)
			printf("L%d-%s ", room->ant, room->name);
		tmp = tmp->next;
	}
	printf("\n");
}

void	move_ants(t_env *e)
{
	t_list		*tmp;
	t_room		*start;
	static int	ants = 0;

	tmp = e->path;
	start = ((t_room*)(tmp->data));
	if (ants == e->ants_nb)
		ants = -1;
	if (ants > -1 && ants < (e->ants_nb + 1))
		ants++;
	start->ant = ants;
	print(e->path);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->next)
			((t_room*)(tmp->next->data))->ant = ((t_room*)(tmp->data))->ant;
		tmp = tmp->prev;
	}
}

int		check_path_for_ants(t_env *e)
{
	t_list	*tmp;

	tmp = e->path;
	while (tmp)
	{

		if (((t_room*)(tmp->data))->ant > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		travel(t_env *e)
{
	t_list	*tmp;
	int		len_room;
	int		i;

	i = 0;
	tmp = e->path;
	len_room = count_rooms(e);
	while (1)
	{
		move_ants(e);
		if (check_path_for_ants(e))
			break ;
		i++;
	}
	return (0);
}
