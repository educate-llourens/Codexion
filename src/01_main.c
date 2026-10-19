/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   01_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 12:27:29 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/19 15:23:40 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

char	**create_argv(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_whiteboard	*whiteboard;
	char			**input_list;
	int				status_code;

	if (input_checks(argc, argv) == PARSING_ERROR)
		return (PARSING_ERROR);
	input_list = create_argv(argc, argv);
	if (!input_list)
		return (write_error("input_list didn't initialise", ERROR), ERROR);
	if (init_whiteboard(&whiteboard, input_list) != OK)
		return (bonfire(&whiteboard, input_list), PARSING_ERROR);
	status_code = simulation_setup(whiteboard);
	if (status_code != OK)
		return (bonfire(&whiteboard, input_list), status_code);
	bonfire(&whiteboard, input_list);
	return (OK);
}

char	**create_argv(int argc, char **argv)
{
	if (!argv)
		return (NULL);
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	else
		argv = argv + 1;
	return (argv);
}
