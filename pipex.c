/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/02 12:27:07 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av, char **ep)
{
	int		fdin = open("infile", O_RDONLY);
	int		fdout = open("outfile", O_WRONLY);
	int		pp1[2];
	int		pid;

	(void)ac;
	if (pipe(pp1) == 1)
	{
		printf("Error al abrir los pipes\n");
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(pp1[0]);
		close(pp1[1]);
		write(STDOUT_FILENO, "Soy hijo 1\n", 11);
		execve("/bin/cat", &av[1], ep);
		printf("Error: execve failed\n");
		exit(-1);
	} 
	close(pp1[1]);
	close(pp1[0]);
	close(fdin);
	close(fdout);
}
//pp[0]--->lectura en pipe
//pp[1]--->escritura en pipe
