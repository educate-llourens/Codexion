/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 11:31:50 by username      #+#    #+#                 */
/*   Updated: 2026/10/14 16:11:56 by lelouren      ########   odam.nl         */
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
# define MALLOC_FAIL 5
# define MAX_NBR_CODERS 200

typedef struct s_coder	t_coder;
typedef struct timeval	t_time;

typedef struct s_whiteboard
{
	int					nbr_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					times_to_refactor;
	int					min_nbr_compiles;
	int					dongle_cooldown;
	char				*scheduler;
	t_time				current_time;
	int					is_burnt;
	t_time				event_start_time;
	pthread_mutex_t		*dongle_mutex_ptr;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		burnt_mutex;
	pthread_mutex_t		gate_mutex;
	t_coder				*coders;
}						t_whiteboard;

typedef struct s_coder
{
	int					id;
	int					nbr_times_dongle_taken;
	t_time				time_last_compiled;
	pthread_t			thread;
	pthread_mutex_t		*left_dongle_ptr;
	pthread_mutex_t		*right_dongle_ptr;
	t_whiteboard		*check_whiteboard_ptr;
}						t_coder;

// Src Functions
	// Check input
int						check_argc(int argc);
int						check_argv(char **input_list);
int						check_digits(char **input_list);
int						check_int(char **input_list);
int						input_checks(int argc, char **argv);

	// Settings
int						init_whiteboard(t_whiteboard **whiteboard,
							char **input_list);

// Utility functions
char					**ft_split(char const *str, char chr);
char					*ft_itoa(int nbr);

	// Print utils
void					write_error(char *message, int error_code);

	// List utils
int						list_len(void *list);

	// Int utils
long int				ft_atol(const char *str);
int						ft_isdigit(int c);

	// String utils
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
char					*ft_strdup(const char *s);

	// Cleanup utils
void					cleanup_list(char **list);
void					free_and_null(void *incoming_memory);
void					clean_whiteboard(t_whiteboard **whiteboard);
void					bonfire(t_whiteboard **whiteboard, char **input_list);

	// Memory utils
void					*ft_memcpy(void *dest, const void *src, size_t n);

#endif
