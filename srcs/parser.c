#include "lem-in.h"
#include <stdio.h>
#include <unistd.h>

void		nb_ants(t_env *e, char *line)
{
	int		i;

	i = 0;
	get_next_line(0, &line);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			ft_error("ants number must be digit only");
		i++;
	}
	e->ants_nb = ft_atoi(line);
}

void		error_parsing(int flag)
{
	if (flag == 1)
		printf("Wrong parameters\n");
	if (flag == 2)
		printf("Coordinates is digit only\n");
}

int			check_pos_room(char **split)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (split[i])
	{
		while (split[i][j] != '\0')
		{
			if (!ft_isdigit(split[i][j]))
				error_parsing(2);
			j++;
		}
		i++;
	}
	if (i != 3)
		error_parsing(1);
	return (0);
}

void		room_spec(t_env *e, char *line, int start_end)
{
	t_room	*room;
	char	**split;

	// printf("start_end : %d, line : %s\n", start_end, line);
	split = ft_strsplit(line, ' ');
	check_pos_room(split);
	room = (t_room*)malloc(sizeof(t_room));
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	room->free = 0;
	room->start_end = start_end;
	room->link = NULL;
	add_to_list(&e->rooms, room);
}

t_room		*check_linked_rooms(t_env *e, char *name)
{
	t_list	*tmp;

	tmp = e->rooms;
	while (tmp)
	{
		if (!ft_strcmp(((t_room*)(tmp->data))->name, name))
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}		

void		link_spec(t_env *e, char *line)
{
	char	**split;
	t_list	*tmp_room;
	t_link	*link;

	tmp_room = e->rooms;
	split = ft_strsplit(line, '-');
	while (tmp_room)
	{
		if (!ft_strcmp(split[0], ((t_room*)(tmp_room->data))->name))
		{
			link = (t_link*)malloc(sizeof(t_link));
			// link->linked_rooms = check_linked_rooms(e, ((t_room*)(tmp_room->data))->name);
			link->linked_rooms = check_linked_rooms(e, split[1]);
			add_to_list(&((t_room*)(tmp_room->data))->link, link);
		}
		tmp_room = tmp_room->next;
	}
}

void		start_end(t_env *e, t_list *tmp)
{
	int		start_end;

	start_end = ROOM;
	if (!ft_strcmp(LINE, "##start"))
		start_end = START;
	if (!ft_strcmp(LINE, "##end"))
		start_end = END;
	tmp = tmp->next;
	room_spec(e, LINE, start_end);
}

void		reader(t_env *e)
{
	char	*line;
	t_read	*read;

	while (get_next_line(0, &line) > 0)
	{
		read = (t_read*)malloc(sizeof(t_read));
		read->line = line;
		ft_putendl(line);
		add_to_list(&e->read, read);
	}
}

void		parser(t_env *e)
{
	int			bool_start_end;
	t_list		*tmp;
	int			k = 0;

	reader(e);
	tmp = e->read;
	nb_ants(e, LINE);
	tmp = tmp->next;
	while (tmp)
	{
		printf("k: %d\n", k);
		bool_start_end = 0;
		if (LINE[1] && LINE[0] == '#' && LINE[1] == '#')
		{
			bool_start_end = 1;
			start_end(e, tmp);
			tmp = tmp->next;
		}
		if (LINE[0] == '#')
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_strchr(LINE, '-'))
			link_spec(e, LINE);
		else if (bool_start_end == 0)
			room_spec(e, LINE, ROOM);
		tmp = tmp->next;
		k++;
	}
}
