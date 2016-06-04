/*
** delete_sequel.c for sequel functions to delete node in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sat Jan 30 16:06:47 2016 Nicolas Gascon
** Last update Sun Feb 14 21:58:32 2016 nicolas rusig
*/

#include "../include/my_malloc.h"
#include "../include/rbtree.h"

extern t_malloc	g_malloc;

void		del_rotate_right(t_node *node)
{
  t_node	*y;

  y = node->left;
  node->left = y->right;
  if (y->right != SENTINEL)
    y->right->parent = node;
  if (y != SENTINEL)
    y->parent = node->parent;
  if (node->parent)
    if (node == node->parent->right)
      node->parent->right = y;
    else
      node->parent->left = y;
  else
    g_malloc.root = y;
  y->right = node;
  if (node != SENTINEL)
    node->parent = y;
}

void		del_rotate_left(t_node *node)
{
  t_node	*y;

  y = node->right;
  node->right = y->left;
  if (y->left != SENTINEL)
    y->left->parent = node;
  if (y != SENTINEL)
    y->parent = node->parent;
  if (node->parent)
    if (node == node->parent->left)
      node->parent->left = y;
    else
      node->parent->right = y;
  else
    g_malloc.root = y;
  y->left = node;
  if (node != SENTINEL)
    node->parent = y;
}

void	reequilibrate_left_color(t_node *bro, t_node **node, t_node **parent)
{
  if (bro->right->color == BLACK)
    {
      if (bro->left != SENTINEL)
	bro->left->color = BLACK;
      bro->color = RED;
      del_rotate_right(bro);
      bro = (*parent)->right;
    }
  bro->color = (*parent)->color;
  if (*parent != SENTINEL)
    (*parent)->color = BLACK;
  if (bro->right->color == RED)
    bro->right->color = BLACK;
  del_rotate_left(*parent);
  *node = g_malloc.root;
}

void	reequilibrate_right_color(t_node *bro, t_node **node, t_node **parent)
{
  if (bro->left->color == BLACK)
    {
      if (bro->right != SENTINEL)
	bro->right->color = BLACK;
      bro->color = RED;
      del_rotate_left(bro);
      bro = (*parent)->left;
    }
  bro->color = (*parent)->color;
  if (*parent != SENTINEL)
    (*parent)->color = BLACK;
  if (bro->left->color == RED)
    bro->left->color = BLACK;
  del_rotate_right(*parent);
  *node = g_malloc.root;
}
