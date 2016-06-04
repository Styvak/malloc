/*
** page.c for page sources file in /home/styvaether/Epitech/PSU/PSU_2015_malloc/test/src
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Sun Feb  7 17:48:00 2016 Nicolas Gascon
** Last update Sun Feb 14 18:18:54 2016 Nicolas Gascon
*/

#include <errno.h>
#include "../include/rbtree.h"

size_t		create_page(size_t size)
{
  size_t	allocate;

  allocate = ((size / g_malloc.psize) + 1) * g_malloc.psize;
  if (sbrk(allocate) == (void *)-1)
    {
      errno = ENOMEM;
      return ((size_t)-1);
    }
  g_malloc.psizeav += allocate;
  return (allocate);
}
