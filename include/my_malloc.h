/*
** my_malloc.h for my_malloc header in /home/styvaether/Epitech/PSU/PSU_2015_malloc
**
** Made by Nicolas Gascon
** Login   <styvaether@epitech.net>
**
** Started on  Mon Jan 25 09:52:57 2016 Nicolas Gascon
** Last update Sun Feb 14 17:03:45 2016 Nicolas Gascon
*/

#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

# include <unistd.h>

# define FALSE	0
# define TRUE	1

# ifdef __x86_64__
#  define ALIGN_BYTES(x) ((((x - 1) >> 3) << 3) + 8)
# else
#  define ALIGN_BYTES(x) ((((x - 1) >> 2) << 2) + 4)
# endif

void	*malloc(size_t);
void	*realloc(void *, size_t);
void	free(void *);
void	show_alloc_mem();
void	show_alloc_mem_color();

#endif
