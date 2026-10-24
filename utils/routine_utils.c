/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:17:04 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/24 19:02:04 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	release_dongles(t_coder *coder);
int	wait_for_turn(t_coder *coder, t_dongle *dongle);

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	int	status;

	pthread_mutex_lock(&dongle->mutex);
	coder->ticket = dongle->next_ticket;
	dongle->next_ticket += 1;
	add_to_que(dongle, coder);
	status = wait_for_turn(coder, dongle);
	dongle_remove(dongle, coder);
	if (status == OK)
		dongle->being_used = TRUE;
	pthread_mutex_unlock(&dongle->mutex);
	if (status != OK)
		return (status);
	return (log_activity(coder, "has taken a dongle"));
}

int	release_dongles(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_unlock(coder->left_dongle_ptr);
	pthread_mutex_unlock(coder->right_dongle_ptr);
	return (OK);
}

// int	wait_for_turn(t_coder *coder, t_dongle *dongle)
// {
// 	t_whiteboard	*whiteboard;
// 	struct timespec	ts;

// 	whiteboard = coder->check_whiteboard_ptr;
// 	while (simulation_over(whiteboard) != TRUE)
// 	{
// 		if (dongle->dongle_que[0] == coder && dongle->being_used == FALSE
// 			&& get_timestamp(whiteboard) >= dongle->time_available)
// 			return (OK);
// 		if (dongle->dongle_que[0] == coder && dongle->being_used == FALSE)
// 		{
// 			ts = make_deadline(whiteboard, dongle->time_available);
// 			pthread_cond_timedwait(&dongle->condition, &dongle->mutex, &ts);
// 		}
// 		else
// 			pthread_cond_wait(&dongle->condition, &dongle->mutex);
// 	}
// 	return (BURNOUT);
// }
