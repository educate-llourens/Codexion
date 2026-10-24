/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 17:22:27 by lelouren          #+#    #+#             */
/*   Updated: 2026/10/24 17:18:33 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void					free_and_null(void *incoming_memory);
void					clean_whiteboard(t_whiteboard **whiteboard);
void					bonfire(t_whiteboard **whiteboard, char **input_list);

void	cleanup_list(char **list)
{
	char	**list_start;

	list_start = list;
	while (*list)
	{
		free_and_null(&(*list));
		list++;
	}
	free_and_null(&(*list_start));
}

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
			pthread_mutex_destroy(&(*whiteboard)->dongles[i].mutex);
			i++;
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

void	bonfire(t_whiteboard **whiteboard, char **input_list)
{
	cleanup_list(input_list);
	clean_whiteboard(whiteboard);
}
