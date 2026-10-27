/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:17:04 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/27 21:00:57 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

static void	release_one(t_coder *coder, t_dongle *dongle);
int			release_dongles(t_coder *coder);

/*
	RELEASE ONE DONGLE
		+ Lock the dongle mutex
		+ Set the dongle as not used and add the cooldown
		+ Unlock the dongle mutex

	PARAMETERS:
		- t_coder *coder: Coder who needs to release the dongle
		- t_dongle *dongle: The dongle being released
*/
static void	release_one(t_coder *coder, t_dongle *dongle)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	pthread_mutex_lock(&dongle->mutex);
	dongle->being_used = FALSE;
	dongle->time_available = get_timestamp(whiteboard)
		+ whiteboard->dongle_cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

/*
	RELEASE BOTH DONGLES
*/
int	release_dongles(t_coder *coder)
{
	release_one(coder, coder->left_dongle_ptr);
	release_one(coder, coder->right_dongle_ptr);
	return (OK);
}
