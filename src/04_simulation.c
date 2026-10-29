/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:46:52 by lilo              #+#    #+#             */
/*   Updated: 2026/10/29 09:13:49 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int		spawn_coders(t_whiteboard *whiteboard);
void	*coder_process(void	*function_arg);

/*
	SETS UP THE START OF THE SIMULATION AND HANDLES THE END OF THE SIMULATION
		+ Creates the coder threads
		+ Creates the monitor thread
		+ Starts the simulation
		+ Joins the threads

	PARAMETERS:
		- t_whiteboard *whiteboard: The board with the shared information we
		need

	RETURN:
		- int thread_return_data: The result of the monitor thread return
*/
int	simulation_setup(t_whiteboard *whiteboard)
{
	int		i;

	i = 0;
	gettimeofday(&whiteboard->event_start_time, NULL);
	while (i < whiteboard->nbr_coders)
	{
		pthread_create(&whiteboard->coders[i].thread, NULL, coder_process,
			&whiteboard->coders[i]);
		i++;
	}
	pthread_create(&whiteboard->monitor_thread,
		NULL, monitor_burnout, whiteboard);
	pthread_mutex_lock(&whiteboard->gate_mutex);
	whiteboard->simulation_started = TRUE;
	pthread_mutex_unlock(&whiteboard->gate_mutex);
	pthread_join(whiteboard->monitor_thread, NULL);
	i = 0;
	while (i < whiteboard->nbr_coders)
	{
		pthread_join(whiteboard->coders[i].thread, NULL);
		i++;
	}
	return (OK);
}

/* 
	STARTS THE THREAD PROCESS
		+ Checks for event start
		+ Starts the coder routine

	PARAMETERS:
		- void	*function_arg: The coder that is going to run as part of the
		simulation
	
	RETURN:
		- int OK: If it ran successfully without burnout
		- int BURNOUT: If a coder burnt out
*/
void	*coder_process(void	*function_arg)
{
	t_coder			*coder;

	coder = (t_coder *)function_arg;
	while (event_started(coder) != TRUE)
		usleep(1 * 1000);
	run_routine(coder);
	return (OK);
}
