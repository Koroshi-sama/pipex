/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:37:13 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/16 18:35:20 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<unistd.h>
# include<sys/wait.h>
# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<string.h>
# include <errno.h>
# include"get_next_line.h"

typedef struct t_pipex
{
	char	**av;
	int		ac;
	int		i;
	char	**ev;
	int		fd1[2];
	int		fd2[2];
	int		*p_fd1;
	int		*p_fd2;
	int		file1;
	int		file2;
	int		sink;
	int		fd_b;
	int		cmd_index;
	int		cmd;
}	t_pip;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *hst, const char *ndl, size_t len);
void	error_exit(char *str, int x);
char	*env_path(char **envp);
int		slash_chr(char *cmd);
int		exit_number(int status);
char	*find_path2(char **envp, char *cmd);
void	check_space(char *argv);
void	child_b(t_pip *pi, char **argv, char **envp);
int		cmp(char *str1, char *str2);

#endif