/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   02_check_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 14:26:41 by username      #+#    #+#                 */
/*   Updated: 2026/10/13 17:32:46 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	check_argc(int argc);
int	check_argv(char **input_list);
int	check_digits(char **input_list);
int	check_int(char **input_list);

unsigned int	input_checks(int argc, char **argv)
{
	char	**input_list;

	if (argc == 2)
		input_list = ft_split(argv[1], ' ');
	else
		input_list = argv + 1;
	if (!input_list)
		return (write_error("Input split failed | check_input: Line 27", ERROR),
			ERROR);
	if (check_argc(list_len(input_list)) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (check_argv(input_list) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (input_list[7] != "FIFO" && input_list[7] != "EDF")
		return (write_error("Schedular needs to be FIFO or EDF", PARSING_ERROR),
			PARSING_ERROR);
	if (argc == 2)
		cleanup_list(input_list);
	return (OK);
}

int	check_argc(int argc)
{
	if (argc < 7)
		return (write_error("Too few arguments", PARSING_ERROR), PARSING_ERROR);
	if (argc > 7)
		return (write_error("Too many arguments", PARSING_ERROR),
			PARSING_ERROR);
	return (OK);
}

int	check_argv(char **input_list)
{
	if (!input_list)
		return (write_error("Invalid user input", PARSING_ERROR),
			PARSING_ERROR);
	if (check_digits(input_list) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (check_int(input_list) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (OK);
}

int	check_digits(char **input_list)
{
	char	*item;
	int		i;
	int		j;

	i = 0;
	while (input_list[i] && input_list[i + 1])
	{
		item = input_list[i];
		if (*item == '\0')
			return (write_error("Invalid user input", PARSING_ERROR),
				PARSING_ERROR);
		j = 0;
		while (item[j])
		{
			if (ft_isdigit(item[j]) == ERROR)
				return (write_error("Argument is not a number", PARSING_ERROR),
					PARSING_ERROR);
			j++;
		}
		i++;
	}
	return (OK);
}

int	check_int(char **input_list)
{
	char		*item;
	long int	str_to_nbr;
	int			i;

	i = 0;
	while (input_list[i])
	{
		item = input_list[i];
		str_to_nbr = ft_atol(item);
		if (i == 0 && str_to_nbr > MAX_NBR_CODERS)
			return (write_error("Too many coders", PARSING_ERROR),
				PARSING_ERROR);
		if (str_to_nbr > INT_MAX)
			return (write_error("Invalid user input", PARSING_ERROR),
				PARSING_ERROR);
		i++;
	}
	return (OK);
}
