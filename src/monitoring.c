/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:30:46 by lilo              #+#    #+#             */
/*   Updated: 2026/10/27 11:10:22 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int			event_started(t_coder *coder);
void		*monitor_burnout(void *function_arg);
static void	set_burnt(t_whiteboard *whiteboard, t_coder *coder);

/*
	CHECKS IF THE EVENT HAS STARTED

	PARAMETERS:
		- t_coder *coder: Coder that is checking if the event started
	
	RETURN:
		- int TRUE: If the event has started
		- int FALSE: If the event has not started
*/
int	event_started(t_coder *coder)
{
	t_whiteboard	*whiteboard;
	int				result;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_lock(&whiteboard->gate_mutex);
	result = whiteboard->simulation_started;
	pthread_mutex_unlock(&whiteboard->gate_mutex);
	return (result);
}

/*
	CHECKS CONTINUOUSLY IF A CODER HAS BURNT OUT OR SIMULATION ENDED

	PARAMETERS:
		- t_whiteboard *whiteboard: Contains all the coders we need to monitor
*/
void	*monitor_burnout(void *function_arg)
{
	t_whiteboard	*whiteboard;
	int				i;
	int				finished;

	whiteboard = (t_whiteboard *)function_arg;
	while (TRUE)
	{
		i = 0;
		finished = 0;
		while (i < whiteboard->nbr_coders)
		{
			if (whiteboard->coders[i].nbr_times_compiled
					>= whiteboard->max_nbr_compiles)
				finished++;
			else if (get_timestamp(whiteboard)
				>= deadline(&whiteboard->coders[i]))
				return (set_burnt(whiteboard, &whiteboard->coders[i]), NULL);
			i++;
		}
		if (finished == whiteboard->nbr_coders)
			return (NULL);
		usleep(1000);
	}
}

static void	set_burnt(t_whiteboard *whiteboard, t_coder *coder)
{
	pthread_mutex_lock(&whiteboard->print_mutex);
	pthread_mutex_lock(&whiteboard->burnt_mutex);
	whiteboard->is_burnt = TRUE;
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
	printf("%d %d burned out\n", get_timestamp(whiteboard), coder->id);
	pthread_mutex_unlock(&whiteboard->print_mutex);
}
