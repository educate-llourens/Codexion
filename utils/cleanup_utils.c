/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 17:22:27 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/27 12:10:01 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void					free_and_null(void *incoming_memory);
void					clean_whiteboard(t_whiteboard **whiteboard);
void					bonfire(t_whiteboard **whiteboard,
							char **input_list, int argc);

/*
	CLEANS AND FREES A LIST

	PARAMETERS:
		- void *list: The list to clean up and clean
*/
void	cleanup_list(void *list)
{
	void	**start;
	void	**cursor;

	if (!list)
		return ;
	start = list;
	cursor = start;
	while (*cursor)
	{
		free_and_null(cursor);
		cursor++;
	}
	free(start);
}

/*
	FREE AND NULL MEMORY
*/
void	free_and_null(void *incoming_memory)
{
	void	**memory;

	memory = (void **)incoming_memory;
	if (*memory)
	{
		free(*memory);
		*memory = NULL;
	}
}

static void	destroy_dongles(t_whiteboard *whiteboard)
{
	int	i;

	i = 0;
	if (!whiteboard->dongles)
		return ;
	while (i < whiteboard->nbr_coders)
	{
		pthread_mutex_destroy(&whiteboard->dongles[i].mutex);
		pthread_cond_destroy(&whiteboard->dongles[i].condition);
		i++;
	}
	free(whiteboard->dongles);
}

/*
	CLEANS AND FREES MEMORY IN THE WHITEBOARD
		+ Unlock and destroy all the dongles mutexes
		+ Unlocks and destroys all the whiteboard mutexes
		+ Free and null the coders, dongles and whiteboard
	
	PARAMETERS:
		- t_whiteboard **whiteboard: Whiteboard to clean and destroy
*/
void	clean_whiteboard(t_whiteboard **whiteboard)
{
	if (!whiteboard || !*whiteboard)
		return ;
	destroy_dongles(*whiteboard);
	pthread_mutex_destroy(&(*whiteboard)->print_mutex);
	pthread_mutex_destroy(&(*whiteboard)->gate_mutex);
	pthread_mutex_destroy(&(*whiteboard)->burnt_mutex);
	pthread_mutex_destroy(&(*whiteboard)->ticket_mutex);
	free((*whiteboard)->coders);
	free(*whiteboard);
	*whiteboard = NULL;
}

/*
	CLEANS AND DESTROYS THE ARG LIST AND WHITEBOARD

	PARAMETERS:
		- t_whiteboard **whiteboard: Shared info to clean and destroy
		- char **input_list: The arg list to clean and destroy
*/
void	bonfire(t_whiteboard **whiteboard, char **input_list, int argc)
{
	if (argc == 2)
		cleanup_list(input_list);
	clean_whiteboard(whiteboard);
}
