/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/26 12:46:10 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/28 13:22:55 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int		check_is_burnt(t_whiteboard *whiteboard);
int		get_last_compiled(t_coder *coder);
int		get_times_compiled(t_coder *coder);
void	set_compile_start(t_coder *coder);
void	increase_compiled(t_coder *coder);

/*
	CHECKS THE IS_BURNT FLAG
		+ Locks and unlocks burnt_mutex
		+ Checks variable

	PARAMETERS:
		- t_whiteboard *whiteboard: The shared info we need to check
*/
int	check_is_burnt(t_whiteboard *whiteboard)
{
	int	is_burnt;

	pthread_mutex_lock(&whiteboard->burnt_mutex);
	is_burnt = whiteboard->is_burnt;
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
	return (is_burnt);
}

/*
	SAFE RETRIEVAL OF LAST TIME COMPILED

	PARAMETERS:
		- t_coder *coder: The coder we need to check

	RETURN:
		- int	time_compiled: The value of the last time coder compiled
*/
int	get_last_compiled(t_coder *coder)
{
	int	time_compiled;

	pthread_mutex_lock(&coder->coder_mutex);
	time_compiled = coder->time_last_compiled;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (time_compiled);
}

/*
	SAFE RETRIEVAL OF NUMBER OF TIMES COMPILED

	PARAMETERS:
		- t_coder *coder: The coder we need to check

	RETURN:
		- int	compile_count: Number of times compiled
*/
int	get_times_compiled(t_coder *coder)
{
	int	compile_count;

	pthread_mutex_lock(&coder->coder_mutex);
	compile_count = coder->nbr_times_compiled;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (compile_count);
}

/*
	SAFELY SETS THE COMPILE START TIME

	PARAMETERS:
		- t_coder *coder: Coder we need to set the compile time for
*/
void	set_compile_start(t_coder *coder)
{
	int	now;

	now = get_timestamp(coder->check_whiteboard_ptr);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->time_last_compiled = now;
	pthread_mutex_unlock(&coder->coder_mutex);
}

/*
	SAFELY INCREASES THE NUMBER OF TIMES CODER COMPILED

	PARAMETERS:
		- t_coder *coder: Coder we need to set the information for
*/
void	increase_compiled(t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mutex);
	coder->nbr_times_compiled += 1;
	pthread_mutex_unlock(&coder->coder_mutex);
}
