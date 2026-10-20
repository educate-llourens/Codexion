/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   03_settings.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/14 14:12:44 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/20 12:49:49 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	create_dongles(t_whiteboard *whiteboard);
int	set_whiteboard_info(t_whiteboard *whiteboard, char **input_list);
int	create_coders(t_whiteboard *whiteboard);

int	init_whiteboard(t_whiteboard **whiteboard,
					char **input_list)
{
	*whiteboard = malloc(sizeof(t_whiteboard));
	if (!*whiteboard)
		return (write_error("Whiteboard malloc fail", MALLOC_FAIL), ERROR);
	if (set_whiteboard_info(*whiteboard, input_list) != OK)
		return (ERROR);
	if (create_coders(*whiteboard) != OK)
		return (ERROR);
	return (OK);
}

int	set_whiteboard_info(t_whiteboard *whiteboard,
							char **input_list)
{
	whiteboard->nbr_coders = atoi(input_list[0]);
	whiteboard->time_to_burnout = atoi(input_list[1]);
	whiteboard->time_to_compile = atoi(input_list[2]);
	whiteboard->time_to_debug = atoi(input_list[3]);
	whiteboard->times_to_refactor = atoi(input_list[4]);
	whiteboard->max_nbr_compiles = atoi(input_list[5]);
	whiteboard->dongle_cooldown = atoi(input_list[6]);
	whiteboard->scheduler = input_list[7];
	whiteboard->is_burnt = FALSE;
	whiteboard->simulation_started = FALSE;
	whiteboard->dongle_mutex_list = malloc(sizeof(pthread_mutex_t)
			* whiteboard->nbr_coders);
	if (!whiteboard->dongle_mutex_list)
		return (write_error("Could not malloc dongle ptr", MALLOC_FAIL),
			ERROR);
	if (create_dongles(whiteboard) == ERROR)
		return (cleanup_list(whiteboard->dongle_mutex_list), ERROR);
	if (pthread_mutex_init(&whiteboard->print_mutex, NULL) != OK)
		return (write_error("Could not create print_mutex", -5), ERROR);
	if (pthread_mutex_init(&whiteboard->burnt_mutex, NULL) != OK)
		return (write_error("Could not create burnt_mutex", -5), ERROR);
	if (pthread_mutex_init(&whiteboard->gate_mutex, NULL) != OK)
		return (write_error("Could not create gate_mutex", -5), ERROR);
	return (OK);
}

int	create_dongles(t_whiteboard *whiteboard)
{
	int	i;

	i = 0;
	while (i < whiteboard->nbr_coders)
	{
		if (pthread_mutex_init(&whiteboard->dongle_mutex_list[i], NULL) != OK)
			return (write_error("Could not create a dongle",
					PARSING_ERROR), ERROR);
		i++;
	}
	return (OK);
}

int	create_coders(t_whiteboard *whiteboard)
{
	int	i;
	int	right_dongle_position;

	i = 0;
	whiteboard->coders = malloc(sizeof(t_coder) * whiteboard->nbr_coders);
	if (!whiteboard->coders)
		return (write_error("Could not malloc coders list", MALLOC_FAIL),
			ERROR);
	while (i < whiteboard->nbr_coders)
	{
		whiteboard->coders[i].id = i + 1;
		whiteboard->coders[i].nbr_times_compiled = 0;
		whiteboard->coders[i].check_whiteboard_ptr = whiteboard;
		whiteboard->coders[i].left_dongle_ptr
			= &whiteboard->dongle_mutex_list[i];
		right_dongle_position = (i + 1) % whiteboard->nbr_coders;
		whiteboard->coders[i].right_dongle_ptr
			= &whiteboard->dongle_mutex_list[right_dongle_position];
		i++;
	}
	return (OK);
}
