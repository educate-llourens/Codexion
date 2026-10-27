/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:58:50 by lilo              #+#    #+#             */
/*   Updated: 2026/10/27 11:09:31 by lilo             ###   ########.fr       */
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
