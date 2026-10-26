/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   04_simulation.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 14:46:52 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/26 19:09:52 by lelouren      ########   odam.nl         */
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
	if (spawn_coders(whiteboard) != OK)
		return (ERROR);
	pthread_create(&whiteboard->monitor_thread,
		NULL, monitor_burnout, whiteboard);
	gettimeofday(&whiteboard->event_start_time, NULL);
	pthread_mutex_lock(&whiteboard->gate_mutex);
	whiteboard->simulation_started = TRUE;
	pthread_mutex_unlock(&whiteboard->gate_mutex);
	pthread_join(whiteboard->monitor_thread, NULL);
	while (i < whiteboard->nbr_coders)
	{
		pthread_join(whiteboard->coders[i].thread, NULL);
		i++;
	}
	return (OK);
}

/*
	CREATES AND INITIALISES THE CODER
	
	PARAMETERS:
		- t_whiteboard *whiteboard: The whiteboard with the simulation shared
		information
	
	RETURN:
		- int OK: Coders and their threads successfully created
*/
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
	t_whiteboard	*whiteboard;

	coder = (t_coder *)function_arg;
	whiteboard = coder->check_whiteboard_ptr;
	while (event_started(coder) != TRUE)
		usleep(1 * 1000);
	run_routine(coder);
	return (OK);
}
