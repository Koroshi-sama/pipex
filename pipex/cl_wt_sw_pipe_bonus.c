/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wt_sw_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:29:18 by aerrazik          #+#    #+#             */
/*   Updated: 2022/08/17 13:48:31 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

int	ret_er(void)
{
	write(1, "Put at least 4 arguments!\n", 26);
	exit(0);
}

void	close_it(t_pip *pi)
{
	close(pi->p_fd1[0]);
	close(pi->p_fd1[1]);
}

void	switch_fd(t_pip *pi)
{
	if (pi->sink == 1)
	{
		pi->p_fd2 = pi->fd1;
		pi->p_fd1 = pi->fd2;
		pi->sink = 0;
	}
	else
	{
		pi->p_fd1 = pi->fd1;
		pi->p_fd2 = pi->fd2;
		pi->sink = 1;
	}
}

int	wt(t_pip pi, int argc, char **argv)
{
	int	i;
	int	status;
	int	nmb_of_cmds;

	i = 0;
	nmb_of_cmds = argc - 3;
	if (cmp(argv[1], "here_doc") == 0)
		nmb_of_cmds++;
	while (i < nmb_of_cmds)
	{
		if (pi.pid == pi.last_pid)
			waitpid(pi.last_pid, &status, 0);
		else
			waitpid(-1, NULL, 0);
		i++;
	}
	return (status);
}

void	pipe_it(t_pip *pi)
{
	if (pi->sink == 1)
	{
		if (pipe(pi->fd1) == -1)
			error_exit("Pipe problem!", errno);
	}
	else
	{
		if (pipe(pi->fd2) == -1)
			error_exit("Pipe problem!", errno);
	}
}
