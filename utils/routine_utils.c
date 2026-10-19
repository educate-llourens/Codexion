/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/19 17:17:04 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/19 17:22:03 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	take_dongles(t_coder *coder)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_lock(coder->left_dongle_ptr) != 0)
		return (write_error("Could not mutex left dongle",
				MUTEX_ERROR), ERROR);
	if (log_activity(coder, "has taken a dongle") != OK)
		return (ERROR);
	if (pthread_mutex_lock(coder->right_dongle_ptr) != 0)
		return (write_error("Could not mutex right dongle",
				MUTEX_ERROR), ERROR);
	if (log_activity(coder, "has taken a dongle") != OK)
		return (ERROR);
	return (OK);
}
