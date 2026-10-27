/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:47:49 by lilo              #+#    #+#             */
/*   Updated: 2026/10/27 12:13:18 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	    try_take(t_coder *coder, t_dongle *first, t_dongle *second);
int	    is_ready(t_coder *coder, t_dongle *dongle);
void	join_queues(t_coder *coder, t_dongle *first, t_dongle *second);

void	join_queues(t_coder *coder, t_dongle *first, t_dongle *second)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_lock(&whiteboard->ticket_mutex);
	coder->ticket = whiteboard->next_ticket;
	whiteboard->next_ticket += 1;
	pthread_mutex_unlock(&whiteboard->ticket_mutex);
	pthread_mutex_lock(&first->mutex);
	add_to_que(first, coder);
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	add_to_que(second, coder);
	pthread_mutex_unlock(&second->mutex);
}

int	is_ready(t_coder *coder, t_dongle *dongle)
{
	if (dongle->dongle_que[0] == coder && dongle->being_used == FALSE
		&& get_timestamp(coder->check_whiteboard_ptr) >= dongle->time_available)
		return (TRUE);
	return (FALSE);
}

int	try_take(t_coder *coder, t_dongle *first, t_dongle *second)
{
	int	taken;

	taken = FALSE;
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	if (is_ready(coder, first) == TRUE && is_ready(coder, second) == TRUE)
	{
		remove_from_que(first, coder);
		remove_from_que(second, coder);
		first->being_used = TRUE;
		second->being_used = TRUE;
		taken = TRUE;
	}
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	return (taken);
}
