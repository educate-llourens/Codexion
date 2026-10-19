/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 15:58:50 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/19 15:10:32 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	get_timestamp(t_whiteboard *whiteboard)
{
	t_time		current_time;
	long int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - whiteboard->event_start_time.tv_sec)
		* 1000 + (current_time.tv_usec - whiteboard->event_start_time.tv_usec)
		/ 1000;
	return ((int)timestamp);
}

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
