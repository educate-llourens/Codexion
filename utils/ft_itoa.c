/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/06 10:58:53 by lilo          #+#    #+#                 */
/*   Updated: 2026/10/13 17:07:43 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

static char	*exceptions(long l_nbr);
static int	count_digits(long l_nbr);
static char	*calculations_and_fill(long l_nbr, char *printable_nbr);

char	*ft_itoa(int nbr)
{
	int		nbr_size;
	char	*printable_nbr;
	char	*str_end;
	long	l_nbr;

	l_nbr = (long)nbr;
	printable_nbr = exceptions(l_nbr);
	if (printable_nbr)
		return (printable_nbr);
	else if (l_nbr == 0 || l_nbr == -2147483648)
		return (NULL);
	nbr_size = count_digits(nbr);
	printable_nbr = malloc(sizeof(char) * (size_t)(nbr_size + 1));
	if (!printable_nbr)
		return (NULL);
	str_end = printable_nbr + nbr_size;
	*str_end = '\0';
	calculations_and_fill(nbr, str_end);
	if (!printable_nbr)
		return (NULL);
	return (printable_nbr);
}

static char	*exceptions(long l_nbr)
{
	char	*return_str;

	if (l_nbr == -2147483648)
	{
		return_str = ft_strdup("-2147483648");
		if (!return_str)
			return (NULL);
		return (return_str);
	}
	else if (l_nbr == 0)
	{
		return_str = ft_strdup("0");
		if (!return_str)
			return (NULL);
		return (return_str);
	}
	else
		return (NULL);
}

static int	count_digits(long l_nbr)
{
	int	size;

	size = 1;
	if (l_nbr < 0)
	{
		size++;
		l_nbr = -l_nbr;
	}
	while (l_nbr >= 10)
	{
		l_nbr = l_nbr / 10;
		size++;
	}
	return (size);
}

static char	*calculations_and_fill(long l_nbr, char *printable_nbr)
{
	long	sign;

	sign = l_nbr;
	if (l_nbr < 0)
		l_nbr = -l_nbr;
	while (l_nbr / 10)
	{
		printable_nbr--;
		*printable_nbr = (char)(l_nbr % 10) + '0';
		l_nbr = l_nbr / 10;
	}
	printable_nbr--;
	*printable_nbr = (char)(l_nbr % 10) + '0';
	if (sign < 0)
	{
		printable_nbr--;
		*printable_nbr = '-';
	}
	return (printable_nbr);
}
