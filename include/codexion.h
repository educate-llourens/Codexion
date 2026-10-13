/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 11:31:50 by username      #+#    #+#                 */
/*   Updated: 2026/10/13 17:25:30 by lelouren      ########   odam.nl         */
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
# include <string.h>

# define TRUE 1
# define FALSE 2
# define PARSING_ERROR -41
# define OK 0
# define ERROR -1
# define MAX_NBR_CODERS 200

typedef struct s_coder	t_coder;
typedef struct timeval	t_time;

typedef struct s_whiteboard
{
	unsigned int		nbr_coders;
	unsigned int		time_to_burnout;
	unsigned int		time_to_compile;
	unsigned int		time_to_debug;
	unsigned int		times_to_refactor;
	t_time				current_time;
	unsigned int		is_burnt;
	t_time				event_start_time;
	pthread_mutex_t		*forks_mutex_ptr;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		burnt_mutex;
	pthread_mutex_t		gate_mutex;
	t_coder				*coders;
}						t_whiteboard;

typedef struct s_coder
{
	unsigned int		id;
	unsigned int		nbr_meals_eaten;
	t_time				time_last_compiled;
	pthread_t			thread;
	pthread_mutex_t		*left_dongle_ptr;
	pthread_mutex_t		*right_dongle_ptr;
	t_whiteboard		*check_whiteboard_ptr;
}	t_coder;

// Src Functions
	// Check input
unsigned int			input_checks(int argc, char **argv);

// Utility functions
char					**ft_split(char const *str, char chr);
char					*ft_itoa(int nbr);

	// Print utils
void					write_error(char *message, int error_code);

	// List utils
unsigned int			list_len(void **list);

	// Int utils
long int				ft_atol(const char *str);
int						ft_isdigit(int c);

	// Cleanup utils
void					cleanup_list(char **list);
void					free_and_null(void *incoming_memory);

#endif
