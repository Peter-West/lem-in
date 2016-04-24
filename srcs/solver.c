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

int		solver(t_env *e)
{
	test(e);

	return (0);
}