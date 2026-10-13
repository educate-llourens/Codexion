/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   01_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 12:27:29 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/13 19:03:54 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	main(int argc, char **argv)
{
	// t_whiteboard	*whiteboard;
	// char			**input_list;

	if (input_checks(argc, argv) == ERROR)
		return (PARSING_ERROR);
	printf("All passed!");
	return (OK);
}
