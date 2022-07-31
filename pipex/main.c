/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:49:26 by aerrazik          #+#    #+#             */
/*   Updated: 2022/07/31 03:23:37 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void    child(char *cmd1, int *fd)
{
	char **sp;
	char **args;
	int i;
	int fd1;
	char *path;
	
	i = 0;
	sp = ft_split(cmd1, ' ');
	while(sp[i])
		i++;
	args = (char **)malloc(i * sizeof(char *));
	i = 0;
	while (sp[i])
	{
		args[i] = sp[i];
		i++;
	}
	args[i] = NULL;
	path = ft_strjoin("/bin/", args[0]);
	fd1 = open("file1", O_RDONLY, 0777);
	dup2(fd1, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execve(path, args, NULL);
	close(fd[1]);
	close(fd1);
}

void	parent(char *cmd2, int *fd)
{
	char **args;
	char **sp;
	char *path;
	int i;
	int fd2;

	i = 0;
	sp = ft_split(cmd2, ' ');
	while(sp[i])
		i++;
	args = (char **)malloc(i * sizeof(char *));
	i = 0;
	while (sp[i])
	{
		args[i] = sp[i];
		i++;
	}
	args[i] = NULL;
	fd2 = open("file2", O_WRONLY, 0777);
	dup2(fd2, STDOUT_FILENO);
	close(fd[1]);
	path = ft_strjoin("/usr/bin/", args[0]);
	dup2(fd[0], STDIN_FILENO);
	execve(path, args, NULL);
	close(fd[0]);
	close(fd2);
}

int main(int argc, char **argv)
{
	int fd[2];
	int pid;
	if (argc != 5)
		return(0);
	if (pipe(fd) == -1)
	{
		perror("Error with pipe :");
		return(0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork didn't work correctly: ");
		return (0);
	}
	if (pid == 0)
		child(argv[2], fd);
	else
	{
		waitpid(pid, NULL, 0);
		parent(argv[3], fd);
	}
	return(0);
}