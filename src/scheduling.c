/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scheduling.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/20 14:52:00 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/20 15:10:23 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

// create bubble sort for time last compiled
t_coder	*edf(t_coder *coder)
{
	int				i;
	int				lifespan;
	t_whiteboard	*whiteboard;
	int				sorted;

	whiteboard = coder->check_whiteboard_ptr;
	lifespan = coder->time_last_compiled + whiteboard->time_to_burnout;
	i = 0;
	while ()

}
