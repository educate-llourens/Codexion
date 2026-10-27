/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 14:52:00 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/27 11:53:03 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	take_both(t_coder *coder);

/*
	CHECKS WHO SHOULD BE AT THE FRONT OF THE QUE
		+ FIFO = ticket number
		+ EDF = deadline based
	
	PARAMETERS:
		- t_coder *coder_a, t_coder *coder_b: Coders to be compared

	RETURN:
		- int TRUE: If coder_a needs to go before coder_b
		- int FALSE: If coder_b needs to go before coder_a
*/
int	goes_before(t_coder *coder_a, t_coder *coder_b)
{
	int	value_a;
	int	value_b;

	if (coder_a->check_whiteboard_ptr->scheduler == FIFO)
	{
		value_a = coder_a->ticket;
		value_b = coder_b->ticket;
	}
	else
	{
		value_a = deadline(coder_a);
		value_b = deadline(coder_b);
	}
	if (value_a < value_b)
		return (TRUE);
	if (value_a == value_b && coder_a->id < coder_b->id)
		return (TRUE);
	return (FALSE);
}

int	take_both(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = coder->left_dongle_ptr;
	second = coder->right_dongle_ptr;
	if (first > second)
	{
		first = coder->right_dongle_ptr;
		second = coder->left_dongle_ptr;
	}
	join_queues(coder, first, second);
	while (check_is_burnt(coder->check_whiteboard_ptr) != TRUE)
	{
		if (try_take(coder, first, second) == TRUE)
		{
			log_activity(coder, "has taken a dongle");
			log_activity(coder, "has taken a dongle");
			return (OK);
		}
		usleep(500);
	}
	return (BURNOUT);
}
