/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 11:32:04 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/17 13:47:39 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

/*childe_1 read from the infile and write it to the first pipe and then
close the file, fd1[0], fd1[1] */
void	child_1(t_pip *pi, char **argv, char **envp)
{
	char	**sp;
	char	*path;

	pi->cmd_index = 2;
	if (cmp(argv[1], "here_doc") == 0)
		pi->cmd_index++;
	if (!*argv[pi->cmd_index])
		error_exit("command not found", 127);
	close(pi->fd1[0]);
	check_space(argv[pi->cmd_index]);
	sp = ft_split(argv[pi->cmd_index], ' ');
	path = find_path2(envp, sp[0]);
	if (dup2(pi->fd_b, STDIN_FILENO) == -1)
		error_exit("Error first dup2 first child!", errno);
	close(pi->fd_b);
	if (dup2(pi->fd1[1], STDOUT_FILENO) == -1)
		error_exit("Error second dup2 first child!--", errno);
	close(pi->fd1[1]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error first child!", errno);
}

/* last_child read from the last pipe and write it to the outfile
 close last_fd[0], last_fd[1], file */
void	last_child(t_pip *pi, char **argv, char **envp, int argc)
{
	char	**sp;
	char	*path;
	int		file;

	close(pi->p_fd1[1]);
	if (!*argv[argc - 2])
		error_exit("command not found", 127);
	check_space(argv[argc - 2]);
	sp = ft_split(argv[argc - 2], ' ');
	path = find_path2(envp, sp[0]);
	file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error_exit("Error in opening outfile!", 1);
	if (dup2(pi->p_fd1[0], STDIN_FILENO) == -1)
		error_exit("Error first dup2 last child!", errno);
	close(pi->p_fd1[0]);
	if (dup2(file, STDOUT_FILENO) == -1)
		error_exit("Error second dup2 last child!", errno);
	close(file);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error last child!", errno);
}

/* middle_childs read from a pipe and then write to the next one7
 close fd1[0], close fd1[1], fd2[0], fd2[1] */
void	child_b(t_pip *pi, char **argv, char **envp)
{
	char	**sp;
	char	*path;
	int		cmd_nmb;

	close(pi->p_fd1[1]);
	close(pi->p_fd2[0]);
	cmd_nmb = pi->i + 2;
	if (!*argv[cmd_nmb])
		error_exit("command not found", 127);
	if (cmp(argv[1], "here_doc") == 0)
		cmd_nmb++;
	check_space(argv[cmd_nmb]);
	sp = ft_split(argv[cmd_nmb], ' ');
	path = find_path2(envp, sp[0]);
	if (dup2(pi->p_fd1[0], STDIN_FILENO) == -1)
		error_exit("Error first dup2 middle child!", errno);
	close(pi->p_fd1[0]);
	if (dup2(pi->p_fd2[1], STDOUT_FILENO) == -1)
		error_exit("Error second dup2 middle child!------", errno);
	close(pi->p_fd2[1]);
	if (execve(path, sp, envp) == -1)
		error_exit("Executing error middle child!", errno);
}

/* pipe_it choose to pipe with fd1 if sink == 1 or fd2 if sink = 0
 if sink == 0 a pointer p_fd1 = fd1 and p_fd2 = fd2 if sink == 1
 then the opposite will happen */
void	children(t_pip *pi, char **argv, char **envp, int argc)
{
	int	pid;
	int	last_cmd;

	last_cmd = argc - 4;
	if (cmp(argv[1], "here_doc") == 0)
		last_cmd--;
	pid = fork();
	if (pid == -1)
		error_exit("It doesn't work!", errno);
	if (pi->i == 0 && pid == 0)
		child_1(pi, argv, envp);
	else if (pi->i == last_cmd && pid == 0)
		last_child(pi, argv, envp, argc);
	else if (pid == 0)
		child_b(pi, argv, envp);
	if (pi->i == last_cmd)
		pi->last_pid = pid;
	pi->pid = pid;
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pi;
	int		status;

	if (argc < 5)
		ret_er();
	pi.i = 0;
	pi.sink = 1;
	pi.cmd = argc - 3;
	if (cmp(argv[1], "here_doc") == 0)
		pi.cmd--;
	here_doc(argv, &pi);
	while (pi.i < pi.cmd)
	{
		if (pi.i < pi.cmd - 1)
			pipe_it(&pi);
		switch_fd(&pi);
		children(&pi, argv, envp, argc);
		if (pi.i > 0)
			close_it(&pi);
		pi.i++;
	}
	status = wt(pi, argc, argv);
	return (exit_number(status));
}
