/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:59:08 by aerrazik          #+#    #+#             */
/*   Updated: 2022/07/31 01:53:42 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	ft_strlen(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	res = (char *)malloc(sizeof(*s1) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int main()
{
	char	s1[] = "I am the bone of my sword ";
	char	s2[] = "Unknown to death nor known to life.";

	printf("-> %s\n", ft_strjoin(s1, s2));
}
*/