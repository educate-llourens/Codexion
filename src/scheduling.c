/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scheduling.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/20 14:52:00 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/21 15:02:06 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

/*
	MAKE SURE TO LOCK COMPILE_QUE_MUTEX WHEN CALLING THIS FUNCTION
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
