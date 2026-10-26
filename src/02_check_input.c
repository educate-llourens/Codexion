/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   02_check_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 14:26:41 by username      #+#    #+#                 */
/*   Updated: 2026/10/26 16:29:15 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	check_argc(int argc);
int	check_argv(char **input_list);
int	check_digits(char **input_list);
int	check_int(char **input_list);

/*
	CHECKS THE USER INPUT
		+ Checks correct number of arguments
		+ Checks number of coders within bounds
		+ Checks arguments 1-6 are numeric
		+ Checks the final argument is either "fifo" or "edf"

	PARAMETERS:
		- int argc: Number of arguments
		- char ** argv: The list to break down and inspect

	RETURN:
		- OK if all checks came back fine
		- ERROR or PARSING_ERROR if there was an issue
*/
int	input_checks(int argc,
				char **argv)
{
	char	**input_list;
	char	*schedular;

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
	schedular = input_list[list_len(input_list) - 1];
	if (strcmp(schedular, "fifo") != 0
		&& strcmp(schedular, "edf") != 0)
		return (write_error("Schedular needs to be fifo or edf", PARSING_ERROR),
			PARSING_ERROR);
	if (argc == 2)
		cleanup_list(input_list);
	return (OK);
}

/*
	CHECKS THE NUMBER OF ARGUMENTS IS CORRECT

	PARAMETERS:
		- int argc: The number of arguments

	RETURN:
		- int OK: If everything went fine
		- int PARSING_ERROR if the number of args is incorrect
*/
int	check_argc(int argc)
{
	if (argc < 8)
		return (write_error("Too few arguments", PARSING_ERROR), PARSING_ERROR);
	if (argc > 8)
		return (write_error("Too many arguments", PARSING_ERROR),
			PARSING_ERROR);
	return (OK);
}

/*
	CHECKS IF THE INPUT VALUES ARE FEASIBLE

	PARAMETERS:
		- char **input_list: The list of arguments we need to check

	RETURN:
		- int OK: If everything is fine
		- int PARSING_ERROR if there is an issue
*/
int	check_argv(char **input_list)
{
	if (!input_list)
		return (write_error("Invalid user input", PARSING_ERROR),
			PARSING_ERROR);
	if (check_digits(input_list) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (check_int(input_list) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (atoi(input_list[0]) < 1)
		return (write_error("Not enough coders", PARSING_ERROR),
			PARSING_ERROR);
	if (atoi(input_list[0]) > MAX_NBR_CODERS)
		return (write_error("Exceeds max number of coders", PARSING_ERROR),
			PARSING_ERROR);
	return (OK);
}

/*
	CHECKS IF ARGS 0-6 ARE NUMBERS

	PARAMETERS:
		- char **input_list: The arg list to check
	
	RETURN:
		- int OK: If there were no issues
		- int PARSING_ERROR: If anything is not a valid number
*/
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
			if (ft_isdigit(item[j]) == FALSE)
				return (write_error("Argument is not a number", PARSING_ERROR),
					PARSING_ERROR);
			j++;
		}
		i++;
	}
	return (OK);
}

/*
	CHECKS THE NUMBERS ARE VALID INT'S

	PARAMETERS:
		- char **input_list: The list of arguments to check
	
	RETURN:
		- int OK: Numbers are valid
		- int PARSING_ERROR: The numbers were not valid ints
*/
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
			return (write_error("Number is too big to be an int",
					PARSING_ERROR), PARSING_ERROR);
		if (str_to_nbr < INT_MIN)
			return (write_error("Number to small to be an int", PARSING_ERROR),
				PARSING_ERROR);
		i++;
	}
	return (OK);
}
