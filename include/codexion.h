/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 11:31:50 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/13 12:47:36 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 2

typedef struct s_coder			t_coder;
typedef struct timeval			t_time;

typedef struct s_whiteboard
{
	signed int					nbr_coders;
	signed int					time_to_burnout;
	signed int					time_to_compile;
	signed int					time_to_debug;
	signed int					times_to_refactor;
	t_time						current_time;
	signed int					is_burnt;
	t_time						event_start_time;
	pthread_mutex_t				*forks_mutex_ptr;
	pthread_mutex_t				print_mutex;
	pthread_mutex_t				burnt_mutex;
	pthread_mutex_t				gate_mutex;
	t_coder						*coders;
}								t_whiteboard;

typedef struct s_coder
{
	signed int 					id;
	signed int					nbr_meals_eaten;
	t_time						time_last_compiled;
	pthread_t					thread;
	pthread_mutex_t				*left_dongle_ptr;
	pthread_mutex_t				*right_dongle_ptr;
	t_whiteboard				*check_whiteboard_ptr;
}								t_coder;

#endif