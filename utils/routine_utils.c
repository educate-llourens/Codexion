/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:17:04 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/24 17:21:06 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	release_dongles(t_coder *coder);

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_lock(&dongle->mutex);
	coder->ticket = dongle->next_ticket;
	dongle->next_ticket += 1;
	// Add to heap
	
	return (OK);
}

int	release_dongles(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_unlock(coder->left_dongle_ptr);
	pthread_mutex_unlock(coder->right_dongle_ptr);
	return (OK);
}
