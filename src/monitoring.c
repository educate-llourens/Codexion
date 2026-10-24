/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:30:46 by lilo              #+#    #+#             */
/*   Updated: 2026/10/24 17:11:58 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	event_started(t_coder *coder);

int	handle_calculated_burnout(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	usleep(whiteboard->time_to_burnout - coder->time_last_compiled);
	pthread_mutex_lock(&whiteboard->burnt_mutex);
	if (log_activity(coder, "burned out") != OK)
		return (ERROR);
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
	whiteboard->is_burnt = TRUE;
}

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
