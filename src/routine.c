/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 15:01:35 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/19 18:12:20 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	debugging(t_coder *coder);
int	refactoring(t_coder *coder);
int	run_routine(t_coder *coder);

int	compiling(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (take_dongles(coder) != OK)
		return (ERROR);
	coder->nbr_times_compiled += 1;
	if (will_burnout(coder, whiteboard->time_to_compile) == TRUE)
		return (handle_calculated_burnout(coder), BURNOUT);
	if (log_activity(coder, "is compiling") != OK)
		return (ERROR);
	coder->time_last_compiled = get_timestamp(coder->check_whiteboard_ptr);
	usleep(whiteboard->time_to_compile * 1000);
	return (OK);
}

int	debugging(t_coder *coder)
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

int	run_routine(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	while (coder->nbr_times_compiled < whiteboard->max_nbr_compiles)
	{
		// Scheduler
		if (compiling(coder) != OK)
			return (ERROR);
		if (debugging(coder) != OK)
			return (ERROR);
		if (refactoring(coder) != OK)
			return (ERROR);
	}
	return (OK);
}
