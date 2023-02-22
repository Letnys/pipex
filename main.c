/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:37:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/08 22:09:15 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*access_p(char **path, char *cmd)
{
	char	*check_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		check_path = ft_strjoinfree(path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, cmd, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	perror("command not found");
	exit(EXIT_FAILURE);
}

void	child(int *fd, int fd_tmp, char **cmd, t_data *p)
{
	char	*path;

	path = access_p(p->path, *cmd);
	dup2(fd_tmp, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (execve(path, cmd, p->envp) == -1)
	{
		perror("execve errror");
		exit(EXIT_FAILURE);
	}
	free(path);
	close(fd_tmp);
	close(fd[1]);
	close(fd[0]);
}

void	last_child(int *fd, int *fd_tmp, char **cmd, t_data *p)
{
	char	*path;

	path = access_p(p->path, *cmd);
	dup2(fd_tmp[0], STDIN_FILENO);
	dup2(fd_tmp[1], STDOUT_FILENO);
	if (execve(path, cmd, p->envp) == -1)
	{
		perror("execve errror");
		exit(EXIT_FAILURE);
	}
	free(path);
	close(fd_tmp[0]);
	close(fd_tmp[1]);
	close(fd[1]);
	close(fd[0]);
}

int	pipe_loop(int *fd_tmp, char **cmd, t_data *p, bool last)
{
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	p->pid = fork();
	if (p->pid < 0)
		exit(EXIT_FAILURE);
	else if (p->pid == 0 && last)
		last_child(fd, fd_tmp, cmd, p);
	else if (p->pid == 0)
		child(fd, *fd_tmp, cmd, p);
	else
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		io[2];
	int		fd_tmp[2];
	t_data	p;
	int		i;

	i = -1;
	p.path = parsing(argc, argv, io, envp);
	fill_data(&p, argc, argv, envp);
	while (p.cmd[++i])
	{
		fd_tmp[0] = io[0];
		if (i == p.max_cmd - 1)
		{
			fd_tmp[1] = io[1];
			io[0] = pipe_loop(fd_tmp, p.cmd[i], &p, true);
		}
		else
			io[0] = pipe_loop(fd_tmp, p.cmd[i], &p, false);
		close(fd_tmp[0]);
	}
	close(io[1]);
	close(io[0]);
	close(fd_tmp[1]);
	waitpid(p.pid, NULL, 0);
}
