/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:49:26 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/01 15:25:05 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd)
{
	if (!access(cmd, F_OK))
		return (cmd);
	else if (!access(ft_strjoin("/usr/local/bin/", cmd), F_OK))
		return (ft_strjoin("/usr/local/bin/", cmd));
	else if (!access(ft_strjoin("/usr/bin/", cmd), F_OK))
		return (ft_strjoin("/usr/bin/", cmd));
	else if (!access(ft_strjoin("/bin/", cmd), F_OK))
		return (ft_strjoin("/bin/", cmd));
	else if (!access(ft_strjoin("/usr/sbin/", cmd), F_OK))
		return (ft_strjoin("/usr/sbin/", cmd));
	else if (!access(ft_strjoin("/sbin/", cmd), F_OK))
		return (ft_strjoin("/sbin/", cmd));
	else
		error_exit("No valid path found");
	return (NULL);
}

void	child(char **argv, int *fd, char **envp)
{
	char	**sp;
	int		fd1;
	char	*path;

	sp = ft_split(argv[2], ' ');
	path = find_path(sp[0]);
	fd1 = open(argv[1], O_RDONLY, 0777);
	if (fd1 == -1)
		error_exit("Error in opening file1!");
	if (dup2(fd1, STDIN_FILENO) == -1)
		error_exit("Error first dup2 first child!");
	close(fd1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("Error second dup2 first child!");
	close(fd[1]);
	close(fd[0]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error first child!");
}

void	child2(char **argv, int *fd, char **envp)
{
	char	**sp;
	char	*path;
	int		fd2;

	sp = ft_split(argv[3], ' ');
	fd2 = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (fd2 < 0)
		error_exit("Error in opening file2!");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		error_exit("Error first dup2 second child!");
	close(fd2);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("Error second dup2 second child\n");
	close(fd[0]);
	close(fd[1]);
	path = find_path(sp[0]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error second child!");
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int	pid2;

	if (argc != 5)
		return (write(2, "Please put 4 arguments\n", 23));
	if (pipe(fd) == -1)
		error_exit("Pipe problem!");
	pid = fork();
	if (pid == -1)
		error_exit("First fork problem!");
	if (pid == 0)
		child(argv, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("Second fork problem!");
	if (pid2 == 0)
		child2(argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
