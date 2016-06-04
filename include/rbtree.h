/*
** rbtree.h for rbtree header in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Thu Jan 28 11:05:29 2016 Nicolas Gascon
** Last update Sun Feb 14 22:11:18 2016 Nicolas Gascon
*/

#ifndef RBTREE_H_
# define RBTREE_H_

# include <unistd.h>
# include <pthread.h>
# include "my_malloc.h"

# define RED		0
# define BLACK		1

# define MAGIC		0xDBA64

typedef struct		s_node
{
  int			magic;
  char			free;
  char			color;
  size_t		size;
  struct s_node		*left;
  struct s_node		*right;
  struct s_node		*parent;
}			t_node;

typedef struct		s_malloc
{
  int			psize;
  size_t		psizeav;
  size_t		num_nodes;
  void			*end;
  void			*first;
  t_node		*root;
  pthread_mutex_t	mutex;
}			t_malloc;

# define PARENT(x)	((x)->parent)
# define GRANDMA(x)	(PARENT(x)->parent)
# define UNCLE_LEFT(x)	(GRANDMA(x)->left)
# define UNCLE_RIGHT(x)	(GRANDMA(x)->right)
# define UNCLE(x)	((UNCLE_RIGHT(x)) ? UNCLE_RIGHT(x) : UNCLE_LEFT(x))
# define NODE_SIZE	sizeof(t_node)

extern t_malloc		g_malloc;
extern t_node		*g_sentinel;

# define SENTINEL	g_sentinel

void	reequilibrate_left_color(t_node *, t_node **, t_node **);
void	reequilibrate_right_color(t_node *, t_node **, t_node **);
t_node	*search(t_node *, t_node *);
t_node	*search_free_block(t_node *, size_t);
void	insert_node(t_node *);
void	delete_node(t_node *);
void	rotate_left(t_node *);
void	rotate_right(t_node *);
void	del_rotate_left(t_node *);
void	del_rotate_right(t_node *);
size_t	create_page(size_t);
t_node	*search_last_node();

#endif
