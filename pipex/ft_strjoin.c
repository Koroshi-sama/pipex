/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:59:08 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/16 18:42:15 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	res = (char *)malloc(sizeof(*s1) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '/';
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

int	cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
	}
	return (0);
}

char	*env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!cmp(envp[i], "PATH="))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	slash_chr(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
