/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:33:02 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/16 18:55:44 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	child_here_doc(int *fd, char **argv, t_pip *pi)
{
	char	*line;

	line = get_next_line(0);
	while (cmp(argv[2], line))
	{
		write(fd[1], line, ft_strlen(line));
		line = get_next_line(0);
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

void	here_doc(char **argv, t_pip *pi)
{
	int		fd[2];
	int		file;
	int		pid;

	if (cmp(argv[1], "here_doc") != 0)
	{
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			error_exit("Error in opening infile!", 1);
		pi->fd_b = file;
	}
	else
	{
		if (pipe(fd) == -1)
			error_exit("Pipe problem!", errno);
		pid = fork();
		if (pid == -1)
			error_exit("Fork problem!", errno);
		if (pid == 0)
			child_here_doc(fd, argv, pi);
		close(fd[1]);
		pi->fd_b = fd[0];
		waitpid(pid, NULL, 0);
	}
}
