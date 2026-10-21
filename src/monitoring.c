/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 13:30:46 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/21 12:20:35 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	event_started(t_coder *coder);

int	handle_calculated_burnout(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	usleep(whiteboard->time_to_burnout - coder->time_last_compiled);
	if (pthread_mutex_lock(&whiteboard->burnt_mutex) != OK)
		return (write_error("Failed to lock burnt_mutex",
				MUTEX_ERROR), ERROR);
	if (log_activity(coder, "burned out") != OK)
		return (ERROR);
	if (pthread_mutex_unlock(&whiteboard->burnt_mutex) != OK)
		return (write_error("Failed to unlock burnt_mutex",
				MUTEX_ERROR), ERROR);
	whiteboard->is_burnt = TRUE;
}

int	event_started(t_coder *coder)
{
	t_whiteboard	*whiteboard;
	int				result;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_lock(&whiteboard->gate_mutex) != OK)
		return (write_error("Failed to lock gate_mutex",
				MUTEX_ERROR), ERROR);
	result = whiteboard->simulation_started;
	if (pthread_mutex_unlock(&whiteboard->gate_mutex) != OK)
		return (write_error("Failed to unlock burnt_mutex",
				MUTEX_ERROR), ERROR);
	return (result);
}
