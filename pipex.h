/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:03:43 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/12 17:10:13 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
//*********************** STANDARD LIBRARIES *********************************
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include "libft/libft.h"
//************************** DEFINITIONS *************************************
typedef struct s_argdata{
	int		fdin;
	int		fdout;
	int		pp[2];
	char	*cmd[2];
	char	*options[2];
}	t_argdata;
//*************************** FUNCTIONS **************************************
void	ft_setdata(t_argdata *pdata, char	**av);
void	ft_parserarg(char	**av, t_argdata *pdata);
char	**ft_getpath(char **ep, char *cmd, char *options);
char	**ft_chkaccess(char	**paths, char	*cmd, char	*options);
void	ft_setssufix(char	**paths, char	*cmd);
void	ft_freepaths(char	**paths, int i);
#endif
