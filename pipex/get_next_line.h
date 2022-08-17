/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:25:15 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/14 11:56:30 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<fcntl.h>
# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>

char	*get_next_line(int fd);
char	*ft_strjoinn(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*save(char **all);
char	*helpme(char	**all, char	**buf);

#endif