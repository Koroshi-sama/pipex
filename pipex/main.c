/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:49:26 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/16 18:17:44 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	child(char **argv, int *fd, char **envp)
{
	char	**sp;
	int		fd1;
	char	*path;

	if (!*argv[2])
		error_exit("command not found", 127);
	check_space(argv[2]);
	sp = ft_split(argv[2], ' ');
	path = find_path2(envp, sp[0]);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		error_exit("Error in opening file1!", 1);
	if (dup2(fd1, STDIN_FILENO) == -1)
		error_exit("Error first dup2 first child!", errno);
	close(fd1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("Error second dup2 first child!", errno);
	close(fd[1]);
	close(fd[0]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error first child!", errno);
}

void	child2(char **argv, int *fd, char **envp)
{
	char	**sp;
	char	*path;
	int		fd2;

	if (!*argv[3])
		error_exit("command not found", 127);
	check_space(argv[3]);
	sp = ft_split(argv[3], ' ');
	path = find_path2(envp, sp[0]);
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
		error_exit("Error in opening file2!", 1);
	if (dup2(fd2, STDOUT_FILENO) == -1)
		error_exit("Error first dup2 second child!", errno);
	close(fd2);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("Error second dup2 second child\n", errno);
	close(fd[0]);
	close(fd[1]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error second child!", errno);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int	pid2;
	int	status;

	if (argc != 5)
		return (write(2, "Please put 4 arguments\n", 23));
	if (pipe(fd) == -1)
		error_exit("Pipe problem!", errno);
	pid = fork();
	if (pid == -1)
		error_exit("First fork problem!", errno);
	if (pid == 0)
		child(argv, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("Second fork problem!", errno);
	if (pid2 == 0)
		child2(argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	status = 0;
	waitpid(pid, NULL, 0);
	waitpid(pid2, &status, 0);
	return (exit_number(status));
}
