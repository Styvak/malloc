/*
** delete.c for delete node in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sat Jan 30 10:24:14 2016 Nicolas Gascon
** Last update Sun Feb 14 21:42:19 2016 nicolas rusig
*/

#include "../include/my_malloc.h"
#include "../include/rbtree.h"

extern t_malloc	g_malloc;

static void	reequilibrate_left(t_node *bro, t_node **node, t_node **parent)
{
  bro = (*parent)->right;
  if (bro->color == RED)
    {
      bro->color = BLACK;
      (*parent)->color = RED;
      del_rotate_left(*parent);
      bro = (*parent)->right;
    }
  if (bro->left->color == BLACK && bro->right->color == BLACK)
    {
      if (bro != SENTINEL)
	bro->color = RED;
      *node = *parent;
      *parent = (*node)->parent;
    }
  else
    reequilibrate_left_color(bro, node, parent);
}

static void	reequilibrate_right(t_node *bro, t_node **node, t_node **parent)
{
  bro = (*parent)->left;
  if (bro->color == RED)
    {
      bro->color = BLACK;
      (*parent)->color = RED;
      del_rotate_right(*parent);
      bro = (*parent)->left;
    }
  if (bro->right->color == BLACK && bro->left->color == BLACK)
    {
      if (bro != SENTINEL)
	bro->color = RED;
      *node = *parent;
      *parent = (*node)->parent;
    }
  else
    reequilibrate_right_color(bro, node, parent);
}

static void	reequilibrate(t_node *node, t_node *parent)
{
  t_node	*bro;

  bro = NULL;
  while (node != g_malloc.root && node->color == BLACK)
    {
      if (node == parent->left)
	reequilibrate_left(bro, &node, &parent);
      else
	reequilibrate_right(bro, &node, &parent);
    }
  node->color = BLACK;
}

static void	delete_node_reeq(t_node *node, t_node *parent, t_node *y,
				 t_node *x)
{
  if (parent)
    {
      if (y == parent->left)
	parent->left = x;
      else
	parent->right = x;
    }
  else
    g_malloc.root = x;
  y->right = node->right;
  y->left = node->left;
  if (y->right == y)
    y->right = SENTINEL;
  if (y->left == y)
    y->left = SENTINEL;
  if (y->color == BLACK && x != SENTINEL)
      reequilibrate(x, parent);
  --g_malloc.num_nodes;
}

void		delete_node(t_node *node)
{
  t_node	*y;
  t_node	*x;
  t_node	*parent;

  if (!node || node == SENTINEL)
    return;
  if (node->right == SENTINEL || node->left == SENTINEL)
    y = node;
  else
    {
      y = node->right;
      while (y->left != SENTINEL)
	y = y->left;
    }
  if (y->left != SENTINEL)
    x = y->left;
  else
    x = y->right;
  parent = y->parent;
  if (x != SENTINEL)
    x->parent = parent;
  delete_node_reeq(node, parent, y, x);
}
