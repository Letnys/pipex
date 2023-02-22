/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:48:52 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/10 01:58:58 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	mess_error(void)
{
	ft_fprintf(2, "invalid input");
	exit(EXIT_FAILURE);
}

char	**parsing(int argc, char **argv, int *fd, char **envp)
{
	int		i;
	char	*str;
	char	**buf;

	i = -1;
	if (argc != 5)
		mess_error();
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 000644);
	if (fd[0] == -1 || fd[1] == -1)
		mess_error();
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

char	***get_cmd(int argc, char **argv, t_data *p)
{
	int		i;
	int		j;
	char	***cmd;
	char	*buf;

	i = 1;
	j = -1;
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
