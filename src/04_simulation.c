/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:46:52 by lilo              #+#    #+#             */
/*   Updated: 2026/10/24 17:10:54 by lilo             ###   ########.fr       */
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
	pthread_mutex_lock(&whiteboard->gate_mutex);
	whiteboard->simulation_started = TRUE;
	pthread_mutex_unlock(&whiteboard->gate_mutex);
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
		pthread_create(&coder->thread, NULL, coder_process, coder);
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
