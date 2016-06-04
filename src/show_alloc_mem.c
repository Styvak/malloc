/*
** show_alloc_mem.c for show alloc meme function in /home/styvaether/Epitech/PSU/PSU_2015_malloc/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Thu Jan 28 14:33:42 2016 Nicolas Gascon
** Last update Sun Feb 14 21:49:25 2016 nicolas rusig
*/

#include <stdio.h>
#include "../include/my_malloc.h"
#include "../include/rbtree.h"

extern t_malloc	g_malloc;

static void	show_node_mem(t_node *node)
{
  if (!node || node == SENTINEL)
    return;
  show_node_mem(node->left);
  if (!node->free)
    printf("0x%lX - 0x%lX : %zu bytes\n", (size_t)node + NODE_SIZE,
	   (size_t)node + NODE_SIZE + node->size,
	   node->size);
  show_node_mem(node->right);
}

void		show_alloc_mem()
{
  printf("break : 0x%lX\n", (size_t)sbrk(0));
  show_node_mem(g_malloc.root);
}
