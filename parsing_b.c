/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:48:52 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/10 01:55:24 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(int argc, char **argv, int *fdres)
{
	char	*tmp;
	char	*str;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	tmp = NULL;
	str = ft_strjoinfree(argv[2], "\n", false, false);
	while (!ft_strcmp(tmp, str))
	{
		ft_fprintf(1, "> ");
		tmp = get_next_line(0);
		if (!ft_strcmp(tmp, str))
			ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
	free(str);
	close(fd[1]);
	if (argc < 4)
	{
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	fdres[0] = fd[0];
	fdres[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 000644);
}

char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**buf;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			str = ft_strrem(envp[i], "PATH=");
			buf = ft_split(str, ':');
			free (str);
			return (buf);
		}
	}
	return (NULL);
}

char	**parsing(int argc, char **argv, int *fd, char **envp)
{
	if (argc < 3)
	{
		ft_fprintf(2, "invalid input");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc"))
		heredoc(argc, argv, fd);
	else
	{
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 000644);
	}
	if (fd[0] == -1 || fd[1] == -1)
	{
		ft_fprintf(2, "invalid input");
		exit(EXIT_FAILURE);
	}
	return (get_path(envp));
}

char	***get_cmd(int argc, char **argv, t_data *p)
{
	int		i;
	int		j;
	char	***cmd;
	char	*buf;

	i = 1;
	j = -1;
	if (ft_strcmp(argv[1], "here_doc"))
		i++;
	cmd = malloc(sizeof(char **) * (argc - 1));
	while (++i < argc - 1)
	{
		cmd[++j] = ft_split(argv[i], ' ');
		buf = cmd[j][0];
		if (ft_strrchr(buf, '/'))
		{
			cmd[j][0] = mlc_strrchr(buf, '/');
			free(buf);
		}
	}
	cmd[++j] = NULL;
	p->max_cmd = j;
	return (cmd);
}

void	fill_data(t_data *p, int argc, char **argv, char **envp)
{
	if (!p->path)
	{
		perror("could not find path variable");
		exit(EXIT_FAILURE);
	}
	p->cmd = get_cmd(argc, argv, p);
	p->envp = envp;
}
