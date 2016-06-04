/*
** block.c for blocks sources file in /home/styvaether/Epitech/PSU/PSU_2015_malloc/test/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sun Feb  7 17:48:06 2016 Nicolas Gascon
** Last update Sun Feb 14 21:41:23 2016 Nicolas Gascon
*/

#include "../include/rbtree.h"

static void	*create_free_block(t_node *node, size_t size)
{
  t_node	*tmp;

  if ((int)node->size - (int)size - (int)NODE_SIZE * 2 < 0)
    {
      node->free = FALSE;
      return ((void *)node + NODE_SIZE);
    }
  tmp = (void *)node + size + NODE_SIZE;
  tmp->free = TRUE;
  tmp->color = RED;
  tmp->size = node->size - size - NODE_SIZE * 2;
  tmp->left = SENTINEL;
  tmp->right = SENTINEL;
  tmp->magic = MAGIC;
  tmp->parent = NULL;
  insert_node(tmp);
  node->free = FALSE;
  node->size = size;
  node->magic = MAGIC;
  return ((void *)node + NODE_SIZE);
}

void		*create_block(size_t size)
{
  t_node	*node;

  if ((node = search_free_block(g_malloc.root, NODE_SIZE + size)) != NULL)
    return (create_free_block(node, size));
  node = g_malloc.end;
  node->free = FALSE;
  node->color = RED;
  node->size = size;
  node->left = SENTINEL;
  node->right = SENTINEL;
  node->magic = MAGIC;
  node->parent = NULL;
  g_malloc.end = (void *)node + size + NODE_SIZE;
  g_malloc.psizeav -= size + NODE_SIZE;
  insert_node(node);
  return ((void *)node + NODE_SIZE);
}
