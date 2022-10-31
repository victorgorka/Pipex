/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/10/31 12:48:47 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av, char **ep)
{
	int	fdin = open("infile", O_RDONLY);
	int	fdout = open("outfile", O_WRONLY);
	int	pp1[2];
	int pp2[2];
	int	pid;
	char infile[500];

	read(fdin, &infile, 499);
	(void)ac;
	dup2(fdout, STDOUT_FILENO);
	close(fdin);
	close(fdout);
	if (pipe(pp1) == -1 && pipe(pp2) == -1)
	{
		printf("Error al abrir los pipes\n");
		exit(-1);
	}
	close(pp1[0]);
	write(pp1[1], infile, strlen(infile));
	write(STDOUT_FILENO, infile, strlen(infile));
	puts("hola");
	pid = fork();
	if (pid == 0)
	{
		dup2(pp1[0], STDIN_FILENO);
		close(pp1[0]);
		write(pp2[1], "Soy hijo 1\n", 11);
		execve("/bin/cat", &av[1], ep);
		printf("Error: execve failed\n");
		exit(-1);
	}
	printf("final");
	char buff[500];
	close(pp2[1]);
	read(pp2[0], buff, 80);
	close(pp2[0]);
	printf("%s", buff);
	close("outfile");
}
//pp[0]--->lectura en pipe
//pp[1]--->escritura en pipe
