/*
** free.c for free sources in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sat Jan 30 11:21:56 2016 Nicolas Gascon
** Last update Sun Feb 14 20:34:05 2016 Nicolas Gascon
*/

#include "../include/my_malloc.h"
#include "../include/rbtree.h"

extern t_malloc	g_malloc;

static void	check_page_size()
{
  t_node	*node;
  size_t	rez;

  if (!(node = search_last_node()))
    return;
  if (!node->free)
    return;
  if ((int)node->size > g_malloc.psize)
    {
      rez = node->size / g_malloc.psize * g_malloc.psize;
      sbrk(-rez);
      node->size -= rez;
      g_malloc.end -= rez;
    }
}

static void	check_free(t_node *node)
{
  t_node	*next;

  if (node == SENTINEL || !node)
    return;
  while (node)
    {
      if (node->free)
	{
	  while ((next = search(node->parent ? node->parent : g_malloc.root,
				(void *)node + NODE_SIZE + node->size))
		 && next->free)
	    {
	      node->size += next->size + NODE_SIZE;
	      delete_node(next);
	    }
	  node = next;
	}
      else
	node = search(g_malloc.root, (void *)node + NODE_SIZE + node->size);
    }
}

void		free(void *pt)
{
  t_node	*tmp;

  tmp = search(g_malloc.root, pt - NODE_SIZE);
  if (!tmp)
    return;
  tmp->free = TRUE;
  pthread_mutex_lock(&g_malloc.mutex);
  check_free(g_malloc.root);
  check_page_size();
  pthread_mutex_unlock(&g_malloc.mutex);
}
