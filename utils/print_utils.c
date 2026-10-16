/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:54:30 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/16 12:06:04 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void	write_error(char *message, int error_code)
{
	char	*error_to_write;

	write(2, "Error ", 7);
	error_to_write = ft_itoa(error_code);
	write(2, error_to_write, strlen(error_to_write));
	write(2, ": ", 2);
	write(2, message, strlen(message));
	write(2, "\n", 1);
	free(error_to_write);
}

int	log_activity(t_coder *coder, char *msg)
{
	t_whiteboard	*whiteboard;

	whiteboard = coder->check_whiteboard_ptr;
	if (pthread_mutex_lock(&whiteboard->print_mutex) != 0)
		return (write_error("Failed print_mutex", MUTEX_ERROR), ERROR);
	printf("%ld %d %s\n", get_timestamp(whiteboard), coder->id, msg);
	if (pthread_mutex_unlock(&whiteboard->print_mutex) != 0)
		return (write_error("Failed to unlock print_mutex", MUTEX_ERROR),
			ERROR);
	return (OK);
}
