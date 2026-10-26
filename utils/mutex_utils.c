/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/26 12:46:10 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/26 18:24:14 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	check_being_used(t_dongle *dongle);

/*
	CHECKS THE IS_BURNT FLAG
		+ Locks and unlocks burnt_mutex
		+ Checks variable

	PARAMETERS:
		- t_whiteboard *whiteboard: The shared info we need to check
*/
int	check_is_burnt(t_whiteboard *whiteboard)
{
	int	is_burnt;

	pthread_mutex_lock(&whiteboard->burnt_mutex);
	is_burnt = whiteboard->is_burnt;
	pthread_mutex_unlock(&whiteboard->burnt_mutex);
	return (is_burnt);
}

/*
	CHECKS THE DONGLE BEING_USED FLAG
		+ Locks and unlocks the dongle's mutex
		+ Checks variable

	PARAMETERS:
		- t_dongle *dongle: The dongle we need to check
*/
int	check_being_used(t_dongle *dongle)
{
	int	being_used;

	pthread_mutex_lock(&dongle->mutex);
	being_used = dongle->being_used;
	pthread_mutex_unlock(&dongle->mutex);
	return (being_used);
}
