/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   04_simulation.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 14:46:52 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/23 15:44:51 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int		spawn_coders(t_whiteboard *whiteboard);
void	*coder_process(void	*function_arg);

int	simulation_setup(t_whiteboard *whiteboard)
{
	int		i;
	void	*thread_return_data;

	i = 0;
	if (spawn_coders(whiteboard) != OK)
		return (ERROR);
	gettimeofday(&whiteboard->event_start_time, NULL);
	if (pthread_mutex_lock(&whiteboard->gate_mutex) != 0)
		return (write_error("Failed to lock gate_mutex", MUTEX_ERROR), ERROR);
	whiteboard->simulation_started = TRUE;
	if (pthread_mutex_unlock(&whiteboard->gate_mutex) != 0)
		return (write_error("Failed to unlock gate_mutex", MUTEX_ERROR), ERROR);
	while (i < whiteboard->nbr_coders)
	{
		if (pthread_join(whiteboard->coders[i].thread, &thread_return_data)
			!= OK || (thread_return_data != OK))
			return ((int)thread_return_data);
		i++;
	}
	return (OK);
}

int	spawn_coders(t_whiteboard *whiteboard)
{
	int		i;
	t_coder	*coder;
	int		right_position;

	i = 0;
	while (i < whiteboard->nbr_coders)
	{
		coder = &whiteboard->coders[i];
		coder->time_last_compiled = 0;
		right_position = (i + 1) % whiteboard->nbr_coders;
		coder->id = i + 1;
		coder->left_dongle_ptr
			= &coder->check_whiteboard_ptr->dongles[i];
		coder->right_dongle_ptr
			= &coder->check_whiteboard_ptr->dongles[right_position];
		if (pthread_create(&coder->thread, NULL, coder_process, coder) != OK)
			return (write_error("Failed to create thread", THREAD_ERROR),
				ERROR);
		i++;
	}
	return (OK);
}

/* Coders simulation
- Lock, read flag, unlock
*/
void	*coder_process(void	*function_arg)
{
	t_coder			*coder;
	t_whiteboard	*whiteboard;
	int				i;

	coder = (t_coder *)function_arg;
	whiteboard = coder->check_whiteboard_ptr;
	while (event_started(coder) != TRUE)
		usleep(1 * 1000);
	if (run_routine(coder) != OK)
		thread_exit(coder);
	return (OK);
}
