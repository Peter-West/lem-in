#ifndef LEM_IN_H
# define LEM_IN_H
# define ROOM		0
# define START		1
# define END		2
# define LINE		((t_read*)(tmp->data))->line
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>

typedef	struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				free;
	int				start_end;
	int				visited;
	struct s_room	*parent;
	t_list			*link;
}					t_room;

typedef	struct		s_link
{
	t_room			*linked_rooms;
}					t_link;

typedef struct		s_read
{
	char			*line;
}					t_read;

typedef struct		s_env
{
	int				ants_nb;
	t_list			*rooms;
	t_list			*read;
	t_list			*path;
}					t_env;

void		parser(t_env *e);
void		ft_error(char *s);
void		add_to_list(t_list **list, void *data);
void		pop_first_elem(t_list **list);
int			solver(t_env *e);
void		push_front(t_list **list, void *data);


#endif
