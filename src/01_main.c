/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:27:29 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/27 20:33:12 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

static char	**create_argv(int argc, char **argv);
void		handle_single_coder(t_whiteboard *whiteboard);
void		*lone_coder_process(void *thread_arg);

/*
	DISTRIBUTES PROGRAM ACROSS CATEGORISED FUNCTIONS:
		+ Checks input
		+ Initialises the structs with correct information
		+ Runs the simulation
		+ Cleans up on error and/or exit
	
	PARAMETERS: int argc, char **argv
	
	RETURNS: int	Error code or OK
*/
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
		return (bonfire(&whiteboard, input_list, argc), PARSING_ERROR);
	if (whiteboard->nbr_coders == 1)
		return (handle_single_coder(whiteboard), OK);
	status_code = simulation_setup(whiteboard);
	if (status_code != OK)
		return (bonfire(&whiteboard, input_list, argc), status_code);
	bonfire(&whiteboard, input_list, argc);
	return (OK);
}

/*
	CREATES A USABLE ARGUMENT LIST

	PARAMETERS:
		- int argc: Number of program arguments
		- char ** argv: The list of arguments to manipulate

	RETURN: 
		- char **		Argument list
*/
static char	**create_argv(int argc, char **argv)
{
	if (!argv)
		return (NULL);
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	else
		argv = argv + 1;
	return (argv);
}

void	handle_single_coder(t_whiteboard *whiteboard)
{
	t_coder	*coder;

	gettimeofday(&whiteboard->event_start_time, NULL);
	coder = &whiteboard->coders[0];
	pthread_create(&coder->thread, NULL, lone_coder_process, coder);
	pthread_join(coder->check_whiteboard_ptr->coders[0].thread,
		NULL);
}

void	*lone_coder_process(void *thread_arg)
{
	t_coder *coder;

	coder = (t_coder *)thread_arg;
	pthread_mutex_lock(&coder->left_dongle_ptr->mutex);
	log_activity(coder, "has taken a dongle");
	pthread_mutex_unlock(&coder->left_dongle_ptr->mutex);
	usleep((unsigned int)
		(coder->check_whiteboard_ptr->time_to_burnout * 1000));
	log_activity(coder, "burned out");
	return (NULL);
}
