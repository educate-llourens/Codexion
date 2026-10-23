/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 11:31:50 by username      #+#    #+#                 */
/*   Updated: 2026/10/23 16:16:41 by lelouren      ########   odam.nl         */
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

# define ERROR -1
# define MALLOC_FAIL -2
# define PARSING_ERROR -3
# define THREAD_ERROR -4
# define MUTEX_ERROR -5
# define BURNOUT -9
# define OK 0
# define TRUE 1
# define FALSE 2
# define EDF 3
# define FIFO 4
# define MAX_NBR_CODERS 200

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct timeval	t_time;

typedef struct s_whiteboard
{
	int					nbr_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					times_to_refactor;
	int					max_nbr_compiles;
	int					dongle_cooldown;
	int					scheduler;
	int					is_burnt;
	int					simulation_started;
	t_time				event_start_time;
	t_dongle			*dongles;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		burnt_mutex;
	pthread_mutex_t		gate_mutex;
	t_coder				*coders;
}						t_whiteboard;

typedef struct s_coder
{
	int					id;
	int					nbr_times_compiled;
	int					time_last_compiled;
	int					ticket;
	pthread_t			thread;
	t_dongle			*left_dongle_ptr;
	t_dongle			*right_dongle_ptr;
	t_whiteboard		*check_whiteboard_ptr;
}						t_coder;

typedef struct s_dongle
{
	int					being_used;
	int					time_available;
	int					next_ticket;
	int					heap_size;
	pthread_mutex_t		mutex;
	pthread_cond_t		condition;
	t_coder				*dongle_que[2];
}						t_dongle;

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
int						set_whiteboard_info(t_whiteboard *whiteboard,
							char **input_list);
int						set_mutexes(t_whiteboard *whiteboard);
int						create_dongles(t_whiteboard *whiteboard);
int						create_coders(t_whiteboard *whiteboard);

	// Simulation
int						simulation_setup(t_whiteboard *whiteboard);
int						spawn_coders(t_whiteboard *whiteboard);
void					*coder_process(void	*function_arg);
	// Routine
int						compiling(t_coder *coder);
int						debugging(t_coder *coder);
int						refactoring(t_coder *coder);
int						run_routine(t_coder *coder);

	// Monitoring
int						handle_calculated_burnout(t_coder *coder);
int						event_started(t_coder *coder);

	// Scheduling
int						goes_before(t_coder *coder_a, t_coder *coder_b);

// Utility functions
char					**ft_split(char const *str, char chr);
char					*ft_itoa(int nbr);

	// Print utils
void					write_error(char *message, int error_code);
int						log_activity(t_coder *coder, char *msg);

	// Routine utils
int						take_dongle(t_coder *coder, t_dongle *dongle);
int						release_dongles(t_coder *coder);

	// List utils
int						list_len(void *list);
void					swap_coders(t_coder **coders_list, int i, int j);

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

	// Time utils
int						get_timestamp(t_whiteboard *whiteboard);
int						will_burnout(t_coder *coder, int deadline_ms);
int						deadline(t_coder *coder);

#endif
