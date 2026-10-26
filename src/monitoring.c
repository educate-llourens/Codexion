/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 13:30:46 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/26 19:29:51 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int			event_started(t_coder *coder);
void		*monitor_burnout(void *function_arg);
static void	set_burnt(t_whiteboard *whiteboard, t_coder *coder);

/*
	CALCULATES WHEN BURNOUT WILL HAPPEN AND HANDLES IF IT WILL HAPPEN
	IN THE MIDDLE OF A PROCESS
		+ Sleeps until the burnout time
		+ Logs the activity
		+ Sets the whiteboard is_burnt to TRUE

	PARAMETERS:
		- t_coder *coder: Coder we need to check

	RETURN:
		None
*/
int	handle_calculated_burnout(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	usleep((unsigned int)
		(whiteboard->time_to_burnout - coder->time_last_compiled));
	pthread_mutex_lock(&whiteboard->burnt_mutex);
	if (log_activity(coder, "burned out") != OK)
		return (ERROR);
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
	whiteboard->is_burnt = TRUE;
	return (BURNOUT);
}

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
	int				i;
	int				compile_complete;
	t_coder			coder;
	t_whiteboard	*whiteboard;

	i = 0;
	compile_complete = 0;
	whiteboard = (t_whiteboard *)function_arg;
	while (compile_complete < whiteboard->nbr_coders)
	{
		while (i++ < whiteboard->nbr_coders)
		{
			coder = whiteboard->coders[i];
			if (coder.time_last_compiled
				>= (coder.time_last_compiled + whiteboard->time_to_burnout))
				return (set_burnt(whiteboard, &coder), NULL);
			if (coder.nbr_times_compiled == whiteboard->max_nbr_compiles)
				compile_complete += 1;
		}
	}
	return (OK);
}

static void	set_burnt(t_whiteboard *whiteboard, t_coder *coder)
{
	pthread_mutex_lock(&whiteboard->burnt_mutex);
	whiteboard->is_burnt = TRUE;
	log_activity(coder, "burned out");
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
}
