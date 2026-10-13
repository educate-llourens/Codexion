/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 17:22:27 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/13 17:24:21 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

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
