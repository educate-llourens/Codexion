/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 15:57:12 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/23 16:58:51 by lelouren      ########   odam.nl         */
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

void	shift_down(t_dongle *dongle, int i)
{
	if (dongle->heap_size < 2)
		return ;
	if (goes_before(dongle->dongle_que[1], dongle->dongle_que[0]) == TRUE)
		swap_coders(dongle->dongle_que, 0, 1);
}

int	add_to_que(t_dongle *dongle, t_coder *coder)
{
	int	i;

	if (dongle->heap_size > 1)
		return (FALSE);
	if ()
	return (TRUE);
}
