/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:38:12 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/10 02:04:16 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data{
	pid_t	pid;
	char	***cmd;
	char	**path;
	char	**envp;
	int		max_cmd;
}	t_data;

char	**parsing(int argc, char **argv, int *fd, char **envp);
char	***get_cmd(int argc, char **argv, t_data *p);
char	*ft_strrem(char *str, char *rem);
char	*mlc_strrchr(char *str, int c);
void	fill_data(t_data *p, int argc, char **argv, char **envp);

#endif