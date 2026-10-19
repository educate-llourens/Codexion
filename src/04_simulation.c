/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   04_simulation.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/15 14:46:52 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/19 18:15:18 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	simulation_setup(t_whiteboard *whiteboard)
{
	if (spawn_coders(whiteboard) != OK)
		return (ERROR);
	
}

int	spawn_coders(t_whiteboard *whiteboard)
{
	int		i;
	t_coder	*coder;
	int		right_position;

	i = 0;
	while (i < whiteboard->nbr_coders)
	{
		coder = &whiteboard->coders[i];
		right_position = (i + 1) % whiteboard->nbr_coders;
		coder->id = i + 1;
		coder->left_dongle_ptr
			= &coder->check_whiteboard_ptr->dongle_mutex_list[i];
		coder->right_dongle_ptr
			= &coder->check_whiteboard_ptr->dongle_mutex_list[right_position];
		if (pthread_create(&coder->thread, NULL, coder_process, coder) != OK)
			return (write_error("Failed to create thread", THREAD_ERROR),
				ERROR);
		i++;
	}
	return (OK);
}

/* Coders simulation
- Lock, read flag, unlock
*/
void	*coder_process(void	*function_arg)
{
	t_coder			*coder;
	t_whiteboard	*whiteboard;
	int				i;

	coder = (t_coder *)function_arg;
	whiteboard = coder->check_whiteboard_ptr;
	while (event_started(coder) != TRUE)
		usleep(1 * 1000);
	if (coder->id % 2 != 0)
		usleep(1 * 1000);
	if (run_routine(coder) != OK)
		thread_exit(coder);
	return (OK);
}
