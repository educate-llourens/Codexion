/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 15:57:12 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/21 12:15:59 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	list_len(void *list)
{
	void	**arr;
	int		i;

	arr = (void **)list;
	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	swap_coders(t_coder **queue, int i, int j)
{
	t_coder	*temp;

	temp = queue[i];
	queue[i] = queue[j];
	queue[j] = temp;
}
