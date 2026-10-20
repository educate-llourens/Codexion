/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 15:57:12 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/20 15:15:05 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void swap_coders(t_coders)