/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 14:54:30 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/13 16:20:45 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void	write_error(char *message, int error_code)
{
	char	*error_to_write;

	write(2, "Error ", 7);
	error_to_write = ft_itoa(error_code);
	write(2, error_to_write, ft_strlen(error_to_write));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	free(error_to_write);
}
