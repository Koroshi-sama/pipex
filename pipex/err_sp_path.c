/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_sp_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:15:40 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/17 16:09:52 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	error_exit(char *str, int x)
{
	perror(str);
	exit(x);
}

void	check_space(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == ' ')
		error_exit("command not found", 127);
	while (argv[i])
	{
		if (argv[i] == ' ' && argv[i + 1] == '\0')
			error_exit("command not found", 127);
		i++;
	}
}

char	*find_path2(char **envp, char *cmd)
{
	char	*path;
	char	**sp;
	int		i;
	char	*path_cmd;

	if (slash_chr(cmd) && !access(cmd, F_OK))
		return (cmd);
	path = env_path(envp);
	sp = ft_split(path, ':');
	i = 0;
	while (sp[i])
	{
		path_cmd = ft_strjoin(sp[i], cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		i++;
		system("leaks pipex");
	}
	error_exit("No valid path found", 127);
	return (NULL);
}

int	exit_number(int status)
{
	int	x;

	x = 0;
	if (WIFEXITED(status))
		x = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		x = 128 + WTERMSIG(status);
	return (x);
}
