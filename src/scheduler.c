/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:01:35 by lilo              #+#    #+#             */
/*   Updated: 2026/10/16 19:26:37 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	debugging(t_coder *coder);
int	refactoring(t_coder *coder);

int	take_dongles(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_lock(coder->left_dongle_ptr) != 0)
		return (write_error("Could not mutex left dongle",
			MUTEX_ERROR), ERROR);
	if (log_activity(coder, "has taken a dongle") != OK)
		return (ERROR);
		if (pthread_mutex_lock(coder->right_dongle_ptr) != 0)
		return (write_error("Could not mutex right dongle",
			MUTEX_ERROR), ERROR);
	if (log_activity(coder, "has taken a dongle") != OK)
		return (ERROR);
	coder->nbr_times_dongle_taken += 1;
	coder->time_last_compiled = get_timestamp(coder->check_whiteboard_ptr);
	if (log_activity(coder, "is compiling") != OK)
		return (ERROR);
	if (will_burnout(coder, whiteboard->time_to_compile) == TRUE)
			handle_calculated_burnout(coder);
	usleep(whiteboard->time_to_compile * 1000);
	return (OK);
}

int debugging(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (will_burnout(coder, whiteboard->time_to_debug) == TRUE)
		handle_calculated_burnout(coder);
	if (log_activity(coder, "is debugging") != OK)
		return (ERROR);
	usleep(whiteboard->time_to_debug * 1000);
	return (OK);
}

int	refactoring(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (will_burnout(coder, whiteboard->time_to_debug) == TRUE)
		handle_calculated_burnout(coder);
	if (log_activity(coder, "is refactoring") != OK)
		return (ERROR);
	usleep(whiteboard->times_to_refactor * 1000);
}
