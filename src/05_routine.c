/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:01:35 by lilo              #+#    #+#             */
/*   Updated: 2026/10/27 11:08:29 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	debugging(t_coder *coder);
int	refactoring(t_coder *coder);
int	run_routine(t_coder *coder);

/*
	COMPILING PROCESS
		+ Take dongles (left then right with checks)
		+ Check if will burnout in middle of this process
		+ Compile and log it (sleep + increase times compiled)
		+ Release dongles

	PARAMETERS:
		- t_coder *coder: The coder that needs to do the compiling

	RETURN:
		- int OK: Coder successfully compiled
		- int ERROR: If there was amn error with compiling
		- int BURNOUT: If a coder burnt out
*/
int	compiling(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (take_both(coder) != OK)
		return (BURNOUT);
	if (log_activity(coder, "is compiling") != OK)
		return (ERROR);
	coder->time_last_compiled = get_timestamp(coder->check_whiteboard_ptr);
	usleep((unsigned int)(whiteboard->time_to_compile * 1000));
	coder->nbr_times_compiled += 1;
	release_dongles(coder);
	return (OK);
}

/*
	DEBUGGING PROCESS
		+ Check if will burnout in the middle of the process
		+ Log it
		+ Sleep for the debug time

	PARAMETERS:
		- t_coder *coder: The coder that needs to debug

	RETURN:
		- int OK: If successfully debugged
		- int ERROR: If there was an issue with logging
*/
int	debugging(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (log_activity(coder, "is debugging") != OK)
		return (ERROR);
	usleep((unsigned int)(whiteboard->time_to_debug * 1000));
	return (OK);
}

/*
	REFACTORING PROCESS
		+ Check if will burnout in the middle of the process
		+ Log the activity
		+ Sleep for the refactor time

	PARAMETERS:
		- t_coder *coder: The coder that needs to refactor

	RETURN:
		- int OK: If successfully debugged
		- int ERROR: If there was an issue with logging
*/
int	refactoring(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (log_activity(coder, "is refactoring") != OK)
		return (ERROR);
	usleep((unsigned int)(whiteboard->times_to_refactor * 1000));
	return (OK);
}

/*
	MAIN ROUTINE DISTRIBUTER

	PARAMETERS:
		- t_coder *coder: Coder that needs to run the routine

	RETURN:
		- int OK: If the routine ran successfully
		- int ERROR: If there was an issue with anything in the routine
*/
int	run_routine(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	while (coder->nbr_times_compiled < whiteboard->max_nbr_compiles)
	{
		if (compiling(coder) != OK)
			return (ERROR);
		if (debugging(coder) != OK)
			return (ERROR);
		if (refactoring(coder) != OK)
			return (ERROR);
	}
	return (OK);
}
