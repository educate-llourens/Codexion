/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 17:22:27 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/26 18:38:02 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void					free_and_null(void *incoming_memory);
void					clean_whiteboard(t_whiteboard **whiteboard);
void					bonfire(t_whiteboard **whiteboard, char **input_list);

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
	int	i;

	i = 0;
	if (!whiteboard || !*whiteboard)
		return ;
	if ((*whiteboard)->dongles)
	{
		while (i < (*whiteboard)->nbr_coders)
		{
			pthread_mutex_unlock(&(*whiteboard)->dongles[i].mutex);
			pthread_mutex_destroy(&(*whiteboard)->dongles[i].mutex);
			i++;
			free_and_null(&(*whiteboard)->dongles[i].dongle_que);
		}
		free_and_null((void **)&(*whiteboard)->dongles);
	}
	pthread_mutex_unlock(&(*whiteboard)->print_mutex);
	pthread_mutex_destroy(&(*whiteboard)->print_mutex);
	pthread_mutex_unlock(&(*whiteboard)->gate_mutex);
	pthread_mutex_destroy(&(*whiteboard)->gate_mutex);
	pthread_mutex_unlock(&(*whiteboard)->burnt_mutex);
	pthread_mutex_destroy(&(*whiteboard)->burnt_mutex);
	free_and_null((*whiteboard)->coders);
	free_and_null((*whiteboard)->dongles);
	free_and_null((void *)&(*whiteboard));
}

/*
	CLEANS AND DESTROYS THE ARG LIST AND WHITEBOARD

	PARAMETERS:
		- t_whiteboard **whiteboard: Shared info to clean and destroy
		- char **input_list: The arg list to clean and destroy
*/
void	bonfire(t_whiteboard **whiteboard, char **input_list)
{
	cleanup_list(input_list);
	clean_whiteboard(whiteboard);
}

