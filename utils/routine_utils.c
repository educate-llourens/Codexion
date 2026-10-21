/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/19 17:17:04 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/21 15:29:50 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	release_dongles(t_coder *coder);

int	take_dongles(t_coder *coder, t_dongle *dongle)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_lock(&dongle->mutex) != OK)
		return (write_error("Failed to lock a dongle", MUTEX_ERROR),
			ERROR);
	coder->ticket = dongle->next_ticket;
	dongle->next_ticket += 1;
	while (dongle->dongle_que[0])
	return (OK);
}

int	release_dongles(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_unlock(coder->left_dongle_ptr) != OK)
		return (write_error("Failed to unlock left dongle", MUTEX_ERROR),
			ERROR);
	if (pthread_mutex_unlock(coder->right_dongle_ptr) != OK)
		return (write_error("Failed to unlock right dongle", MUTEX_ERROR),
			ERROR);
	return (OK);
}
