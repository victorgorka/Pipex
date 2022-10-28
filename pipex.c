/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/10/28 20:04:24 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unsitd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int ac, char **av, char **ep)
{
	int	fdin = open("infile", O_WRONLY);
	int	fdout = open("outfile", O_RDONLY);
	int	pp[2];
	int	pid;

	dup2(fdin, 0);
	dup2(fdout, 1);
	close(fdin);
	close(fdout);
	if (pipe(pp) == -1)
	{
		printf("Error al abrir los pipes\n");
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pp[0]);
		write(pp[1], "Soy hijo 1\n", 11);
		close(pp[1]);
		execve("/bin/cat", &av[1], ep);
		printf("Error: execve failed\n");
		exit(-1);
	}
	printf("final");
	char buf[500];
	buff = read(pp[0]);

}
//pp[0]--->lectura en pipe
//pp[1]--->escritura en pipe
