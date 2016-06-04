/*
** rbtree.c for rbtree sources in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Thu Jan 28 12:19:29 2016 Nicolas Gascon
** Last update Sun Feb 14 22:10:45 2016 Nicolas Gascon
*/

#include "../include/rbtree.h"

extern t_malloc	g_malloc;

t_node	*g_sentinel;

static void	reequilibrate_parent_right(t_node **node, t_node *uncle)
{
  uncle = GRANDMA(*node)->left;
  if (uncle->color == RED)
    {
      PARENT(*node)->color = BLACK;
      uncle->color = BLACK;
      GRANDMA(*node)->color = RED;
      *node = GRANDMA(*node);
    }
  else
    {
      if (*node == PARENT(*node)->left)
	{
	  *node = PARENT(*node);
	  del_rotate_right(*node);
	}
      PARENT(*node)->color = BLACK;
      GRANDMA(*node)->color = RED;
      del_rotate_left(GRANDMA(*node));
    }
}

static void	reequilibrate_parent_left(t_node **node, t_node *uncle)
{
  uncle = GRANDMA(*node)->right;
  if (uncle->color == RED)
    {
      PARENT(*node)->color = BLACK;
      uncle->color = BLACK;
      GRANDMA(*node)->color = RED;
      *node = GRANDMA(*node);
    }
  else
    {
      if (*node == PARENT(*node)->right)
	{
	  *node = PARENT(*node);
	  del_rotate_left(*node);
	}
      PARENT(*node)->color = BLACK;
      GRANDMA(*node)->color = RED;
      del_rotate_right(GRANDMA(*node));
    }
}

static void	reequilibrate(t_node *root, t_node *node)
{
  t_node	*uncle;

  uncle = NULL;
  while (node != root && node->parent->color == RED)
    {
      if (PARENT(node) == GRANDMA(node)->left)
	reequilibrate_parent_left(&node, uncle);
      else
	reequilibrate_parent_right(&node, uncle);
    }
  g_malloc.root->color = BLACK;
}

void		insert_node(t_node *node)
{
  t_node	*cur;
  t_node	*parent;

  cur = g_malloc.root;
  parent = NULL;
  while (cur != SENTINEL)
    {
      parent = cur;
      if (node < cur)
	cur = cur->left;
      else
	cur = cur->right;
    }
  node->parent = parent;
  if (parent)
    if (node <= parent)
      parent->left = node;
    else
      parent->right = node;
  else
    g_malloc.root = node;
  reequilibrate(g_malloc.root, node);
  ++g_malloc.num_nodes;
}
