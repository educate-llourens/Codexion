/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   int_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 17:08:23 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/14 12:48:02 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	ft_isdigit(int c);

long int	ft_atol(const char *str)
{
	int			sign;
	long int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) == 1)
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (sign * nbr);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (TRUE);
	}
	return (FALSE);
}
