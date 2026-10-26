/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/19 17:17:04 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/26 18:09:26 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int			wait_for_turn(t_coder *coder, t_dongle *dongle);
int			take_dongle(t_coder *coder, t_dongle *dongle);
static void	release_one(t_coder *coder, t_dongle *dongle);
int			release_dongles(t_coder *coder);

/*
	CHECKS IF IT IS THE CODERS TURN TO GO
		+ Check if coder burnt out
		+ Is the coder at the front of the que and not being used?
		+ Unlock and lock dongle mutex

	PARAMETERS:
		- t_coder *coder: Coder who is waiting
		- t_dongle *dongle: Dongle the coder is waiting for

	RETURN:
		- int OK: If the coder can proceed
		- int BURNOUT: If the coder burnt out while waiting
*/
int	wait_for_turn(t_coder *coder, t_dongle *dongle)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	while (check_is_burnt(whiteboard) != TRUE)
	{
		if (dongle->dongle_que[0] == coder && dongle->being_used == FALSE
			&& get_timestamp(whiteboard) >= dongle->time_available)
			return (OK);
		pthread_mutex_unlock(&dongle->mutex);
		usleep(1 * 1000);
		pthread_mutex_lock(&dongle->mutex);
	}
	return (BURNOUT);
}

/*
	TAKE A DONGLE IF THE CODER IS ABLE TO
		+ Lock the dongle's mutex
		+ Assign ticket
		+ Add to the dongle que
		+ Wait for turn
		+ Remove from dongle que
		+ Set the dongle as being used
		+ Unlock the dongle mutex
		+ Log the activity

	PARAMETERS:
		- t_coder *coder: Coder who is taking a dongle
		- t_dongle *dongle: The dongle the coder is trtying to take

	RETURN:
		- int OK: if teh coder successfully took the dongle
		- int BURNOUT: If the coder burnt out while trying to take a dongle
*/
int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	coder->ticket = dongle->next_ticket;
	dongle->next_ticket += 1;
	add_to_que(dongle, coder);
	if (wait_for_turn(coder, dongle) != OK)
		return (pthread_mutex_unlock(&dongle->mutex), BURNOUT);
	remove_from_que(dongle, coder);
	dongle->being_used = TRUE;
	pthread_mutex_unlock(&dongle->mutex);
	log_activity(coder, "has taken a dongle");
	return (OK);
}

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
