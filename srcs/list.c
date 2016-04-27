#include <lem-in.h>
#include <stdio.h>

void	add_to_list(t_list **list, void *data)
{
	t_list		*new_list;
	t_list		*tmp;
	
	int			i = 0;

	new_list = (t_list*)malloc(sizeof(t_list));
	new_list->data = data;
	new_list->next = NULL;
	new_list->prev = NULL;
	if (!(*list))
		*list = new_list;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list;
		i++;
	}
}

void	pop_first_elem(t_list **list)
{
	*list = ((t_list*)(*list))->next;
}

void	push_front(t_list **list, void *data)
{
	t_list		*new_elem;

	new_elem = (t_list*)malloc(sizeof(t_list));
	new_elem->data = data;
	if (*list)
	{
		new_elem->prev = NULL;
		new_elem->next = *list;
		new_elem->next->prev = new_elem;
	}
	else
	{
		new_elem->next = NULL;
		new_elem->prev = NULL;
	}
	*list = new_elem;
}
