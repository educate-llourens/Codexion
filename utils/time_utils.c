/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 15:58:50 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/26 19:37:19 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

/*
	GET THE CURRENT TIME IN MS

	PARAMETERS:
		- t_whiteboard *whiteboard: Struct where we are storing the info

	RETURN:
		- int	timestamp: The current time in ms
*/
int	get_timestamp(t_whiteboard *whiteboard)
{
	t_time	now;
	long	seconds;
	long	ms;

	gettimeofday(&now, NULL);
	seconds = now.tv_sec - whiteboard->event_start_time.tv_sec;
	ms = now.tv_usec - whiteboard->event_start_time.tv_usec;
	return ((int)(seconds * 1000 + ms / 1000));
}

/*
	CALCULATES IF THE CODER WILL BURN OUT IN THE MIDDLE OF THE ACTIVITY

	PARAMETERS:
		- t_coder *coder: The coder we need to calculate for
		- int deadline_ms: The activity time in ms

	RETURN:
		- int TRUE: If the coder will burn out
		- int FALSE: If the coder will not burn out
*/
int	will_burnout(t_coder *coder, int deadline_ms)
{
	int				death_time;
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;

	death_time = get_timestamp(whiteboard) + whiteboard->time_to_burnout;
	if ((coder->time_last_compiled + deadline_ms) > death_time)
		return (TRUE);
	return (FALSE);
}

/*
	CALCULATES WHEN THE CODER WILL BURN OUT

	PARAMETERS:
		- t_coder *coder: The coder we are checking

	RETURN:
		- The time in ms when the coder will burn out
*/
int	deadline(t_coder *coder)
{
	return (coder->time_last_compiled
		+ coder->check_whiteboard_ptr->time_to_burnout);
}
