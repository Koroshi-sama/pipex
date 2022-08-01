/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:49:14 by aerrazik          #+#    #+#             */
/*   Updated: 2022/07/31 01:53:21 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (i > 0 && s[i - 1] != c && (s[i] == c || s[i] == '\0'))
			count++;
		while (s[i] == c)
			i++;
		if (i <= (int)ft_strlen(s))
			i++;
	}
	return (count);
}

char	*sp(const char *s, int e, int b)
{
	int		i;
	char	*sp;

	sp = (char *)malloc(sizeof(char) * (e - b + 1));
	if (!sp)
		return (0);
		i = 0;
	while (b < e)
	{
		sp[i] = s[b];
		i++;
		b++;
	}
	sp[i] = '\0';
	return (sp);
}

char	**ft_split(char const *s, char c)
{
	char	**spl;
	int		i;
	int		j;
	int		b;

	if (!s)
		return (NULL);
	spl = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	b = -1;
	while (++i <= (int)ft_strlen(s))
	{
		if (s[i] != c && s[i] && b == -1)
			b = i;
		if ((s[i] == c || s[i] == '\0') && b >= 0)
		{
			spl[j++] = sp(s, i, b);
			b = -1;
		}
	}
	spl[j] = 0;
	return (spl);
}
/*
int main()
{
	char s[] = "lorem ipsum dolor sit amet, consectetur ";
	int i;
	char	**str = ft_split(s, 'i');
	i = 0;
	while (str[i])
	{
		printf("->%s\n", str[i]);
		i++;
	}
	printf("-> %d\n", count(s, ' '));
}
*/