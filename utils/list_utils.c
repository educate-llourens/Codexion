/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 15:57:12 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/26 19:33:21 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

void	swap_coders(t_coder **queue, int i, int j);
void	shift_down(t_dongle *dongle);
int		add_to_que(t_dongle *dongle, t_coder *coder);
void	remove_from_que(t_dongle *dongle, t_coder *coder);

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

/*
	SWAPS THE CODERS IN THE HEAP

	PARAMETERS:
		- t_coder **queue: The que we need to rearrange
		- int i: Position of the first coder to swap
		- int j: Position of the second coder to swap
*/
void	swap_coders(t_coder **queue, int i, int j)
{
	t_coder	*temp;

	temp = queue[i];
	queue[i] = queue[j];
	queue[j] = temp;
}

/*
	CHECKS WHICH CODER SHOULD GO FIRST AND SWAPS ACCORDINGLY

	PARAMETERS:
		- t_dongle *dongle: The dongle who's que we are rearranging
*/
void	shift_down(t_dongle *dongle)
{
	if (dongle->heap_size < 2)
		return ;
	if (goes_before(dongle->dongle_que[1], dongle->dongle_que[0]) == TRUE)
		swap_coders(dongle->dongle_que, 0, 1);
}

/*
	ADD A CODER TO THE DONGLE QUE IN THE CORRECT ORDER
		+ If no coders in the que, just add in 0 position
		+ If too many coders in the heap, return FALSE
		+ Add to the back of the que
		+ If not correct order, swap accordingly

	PARAMETERS:
		- t_dongle *dongle: The dongle whose que we are checking
		- t_coder *coder: The coder wh we are adding to the que

	RETURN:
		- int OK: If coder successfully added to the dongle que
		- int FALSE: If coder could not be added to the que
*/
int	add_to_que(t_dongle *dongle, t_coder *coder)
{
	if (dongle->heap_size > 1)
		return (FALSE);
	if (dongle->heap_size < 1)
	{
		dongle->dongle_que[0] = coder;
		return (TRUE);
	}
	else
		dongle->dongle_que[1] = coder;
	dongle->heap_size += 1;
	if (goes_before(dongle->dongle_que[1], dongle->dongle_que[0]) == TRUE)
		swap_coders(dongle->dongle_que, 0, 1);
	return (TRUE);
}

/*
	REMOVE A CODER FROM THE DONGLE QUE
		+ If 2 coders in the heap, swap the coders and remove from the back
		+ If 1 coder, set position 0 to NULL

	PARAMETERS:
		- t_dongle *dongle: The dongle que we need to manipulate
		- t_coder *coder: The coder we need to remove from the que
*/
void	remove_from_que(t_dongle *dongle, t_coder *coder)
{
	if (dongle->heap_size < 1)
		return ;
	else if (dongle->heap_size > 1)
	{
		if (dongle->dongle_que[0] == coder)
			swap_coders(dongle->dongle_que, 0, 1);
		dongle->dongle_que[dongle->heap_size - 1] = NULL;
	}
	else
		dongle->dongle_que[0] = NULL;
	dongle->heap_size -= 1;
}
