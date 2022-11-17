/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setdata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:48:26 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/17 19:09:08 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_parserarg(char	**av, t_argdata *pdata)
{
	pdata->options[0] = ft_split(av[2], ' ');
	pdata->options[1] = ft_split(av[3], ' '); 
	//modificar splkit. Que corte hasta que encuentre comillas y no cortar hasta
	//encontrar comillas de cierre

	pdata->cmd[0] = ft_strdup(pdata->options[0][0]);
	pdata->cmd[1] = ft_strdup(pdata->options[1][0]);
}

//set fdin, fdout, pp, cmd and options in data structure
void	ft_setdata(t_argdata *pdata, char	**av)
{
	if (!access(av[1], F_OK | R_OK))
		pdata->fdin = open(av[1], O_RDONLY);
	else
	{
		ft_putstr_fd("Error: input file\n", 2);
		exit(127);
	}
	pdata->fdout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pdata->fdout < 0)
	{
		ft_putstr_fd("Error: output file\n", 2);
		exit(127);
	}
	if (pipe(pdata->pp) == 1)
	{
		ft_putstr_fd("Error: pipe\n", 2);
		exit(127);
	}
	ft_parserarg(av, pdata);
}
