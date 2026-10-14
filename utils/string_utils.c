/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 18:26:39 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/14 13:39:35 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		len_src;
	const char	*end;

	len_src = strlen(src);
	if (!dst || !src)
		return (len_src);
	if (size == 0)
		return (len_src);
	end = src + size - 1;
	while (*src && src != end)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (len_src);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	len_s;

	len_s = strlen((char *)s);
	new_s = malloc(sizeof(char) * (len_s + 1));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s, len_s);
	new_s[len_s] = '\0';
	return (new_s);
}
