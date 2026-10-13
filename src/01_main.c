/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   01_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 12:27:29 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/13 16:34:02 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	main(int argc, char **argv)
{
	t_whiteboard	*whiteboard;
	signed int		error_check;
	char			**input_list;

	error_check = 0;

	if (input_checks(argc, argv) == ERROR)
		return (PARSING_ERROR);
	return (OK);
}
