#include "lem-in.h"
#include <stdio.h>


void	test(t_env *e)
{
	t_list	*tmp;
	t_list	*tmp0;
	t_room	*tmp_room;

	tmp = e->rooms;
	while (tmp)
	{
		tmp_room = ((t_room*)(tmp->data));
		printf("ptr : %p, name : %s, x : %d, y : %d\n", tmp_room, tmp_room->name, tmp_room->x, tmp_room->y);
		tmp0 = ((t_list*)(tmp_room->link));
		while (tmp0)
		{
			printf("linked room ptr: %s\n", ( (t_room*)( (t_link*)(tmp0->data) )->linked_rooms )->name );
			tmp0 = tmp0->next;
		}
		tmp = tmp->next;
	}
}

void		test_path(t_env *e)
{
	t_list	*tmp;

	tmp = e->path;
	printf("Yo\n");
	while (tmp)
	{
		printf("solution : %s\n", ((t_room*)(tmp->data))->name);
		tmp = tmp->next;
	}
}

t_room		*first_node(t_list *room)
{
	t_list	*tmp;

	tmp = room;
	while (tmp)
	{
		if ( ((t_room*)(tmp->data))->start_end == START )
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

int		end_reached(t_room *r)
{
	if (r->start_end == 2)
		return (1);
	else
		return (0);
}

void		visit_neighbour(t_list **queue)
{
	t_room	*room;
	t_list	*tmp;
	t_room	*neighbour;
	t_link	*link;

	room = ((t_room*)((*queue)->data));
	tmp = room->link;
	while (tmp)
	{
		link = ((t_link*)(tmp->data));
		neighbour = ((t_room*)(link->linked_rooms));
		if (neighbour->visited == 0)
		{
			neighbour->visited = 1;
			neighbour->parent = room;
			add_to_list(queue, neighbour);
		}
		tmp = tmp->next;
	}
}

void	find_path(t_env *e, t_room *end)
{
	t_room	*room;

	room = end;
	while (room)
	{
		push_front(&e->path, room);
		room = room->parent;
	}
}

int		solver(t_env *e)
{
	t_list	*queue;
	t_room	*tmp;
	int		i;

	// test(e);
	queue = NULL;
	i = 0;
	add_to_list(&queue, first_node(e->rooms));
	((t_room*)(queue->data))->visited = 1;
	while (queue)
	{
		tmp = ((t_room*)(queue->data));
		if (tmp->start_end == END)
		{
			find_path(e, tmp);
			break ;
		}
		visit_neighbour(&queue);
		pop_first_elem(&queue);
		i++;
	}
	// test_path(e);
	return (0);
}