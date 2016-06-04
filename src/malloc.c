/*
** malloc.c for malloc sources file in /home/styvaether/Epitech/PSU/PSU_2015_malloc/test/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sun Feb  7 17:18:08 2016 Nicolas Gascon
** Last update Sun Feb 14 22:15:20 2016 Nicolas Gascon
*/

#include <stdio.h>
#include <string.h>
#include "../include/rbtree.h"
#include "../include/block.h"

t_malloc	g_malloc;

extern t_node	*g_sentinel;

static void	create_sentinel()
{
  g_malloc.psizeav -= NODE_SIZE;
  g_sentinel = g_malloc.end;
  g_malloc.end += NODE_SIZE;
  g_malloc.first = g_malloc.end;
  g_sentinel->magic = MAGIC;
  g_sentinel->free = FALSE;
  g_sentinel->color = BLACK;
  g_sentinel->size = 0;
  g_sentinel->left = SENTINEL;
  g_sentinel->right = SENTINEL;
  g_sentinel->parent = NULL;
}

static size_t	min(size_t a, size_t b)
{
  if (a < b)
    return (a);
  return (b);
}

void	*malloc(size_t size)
{
  void	*ptr;

  size = ALIGN_BYTES(size);
  if (size < 48)
    size = 48;
  if (!g_malloc.root)
    {
      g_malloc.psize = sysconf(_SC_PAGESIZE);
      g_malloc.end = sbrk(0);
      g_malloc.first = g_malloc.end;
      sbrk(g_malloc.psize);
      g_malloc.psizeav = g_malloc.psize;
      create_sentinel();
      g_malloc.root = SENTINEL;
    }
  pthread_mutex_lock(&(g_malloc.mutex));
  if (g_malloc.psizeav < size + NODE_SIZE)
    if (create_page((size + NODE_SIZE)) == (size_t)-1)
      {
	pthread_mutex_unlock(&(g_malloc.mutex));
	return (NULL);
      }
  ptr = create_block(size);
  pthread_mutex_unlock(&(g_malloc.mutex));
  return (ptr);
}

void		*realloc(void *node, size_t size)
{
  void		*new;
  t_node	*tmp;

  tmp = search(g_malloc.root, node - NODE_SIZE);
  if (!tmp)
    return (malloc(size));
  if (!size)
    {
      free(node);
      return (NULL);
    }
  if (tmp->size > ALIGN_BYTES(size))
    return (node);
  if (!(new = malloc(size)))
    return (NULL);
  pthread_mutex_lock(&(g_malloc.mutex));
  memcpy(new, (void *)tmp + NODE_SIZE, min(tmp->size, size));
  pthread_mutex_unlock(&(g_malloc.mutex));
  free(tmp);
  return (new);
}

void	*calloc(size_t num, size_t size)
{
  void	*ptr;

  if (!num || !size)
    return (NULL);
  if (!(ptr = malloc(num * size)))
    return (NULL);
  pthread_mutex_lock(&(g_malloc.mutex));
  bzero(ptr, num * size);
  pthread_mutex_unlock(&(g_malloc.mutex));
  return (ptr);
}
