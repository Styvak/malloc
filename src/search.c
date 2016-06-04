/*
** search.c for search sources in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sat Jan 30 17:32:53 2016 Nicolas Gascon
** Last update Sun Feb 14 21:56:00 2016 Nicolas Gascon
*/

#include "../include/rbtree.h"

/*
** Work in progress : Iterative mode
*/
t_node		*search_free_block(t_node *node, size_t size)
{
  t_node	*tmp;

  return (NULL);
  if (!node || node == SENTINEL)
    return (NULL);
  if (node->free && size < node->size && node->magic == MAGIC)
    return (node);
  tmp = search_free_block(node->left, size);
  if (!tmp)
    tmp = search_free_block(node->right, size);
  return (tmp);
}

t_node	*search(t_node *node, t_node *research)
{
  while (node && node != SENTINEL && (void *)node < g_malloc.end)
    {
      if (node == research && node->magic == MAGIC)
	return (node);
      if (research < node)
	node = node->left;
      else
	node = node->right;
    }
  return (NULL);
}

t_node		*search_last_node()
{
  t_node	*tmp;

  tmp = g_malloc.root;
  if (tmp == SENTINEL)
    return (NULL);
  while (tmp->right != SENTINEL)
    tmp = tmp->right;
  return (tmp);
}
