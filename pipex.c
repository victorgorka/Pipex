/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/02 19:11:00 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void	child(int fdin, int *pipe, char **ep, char **av)
{
	dup2(fdin, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	execve("/bin/cat", &av[0], ep);
	printf("Aqui si Error: execve failed\n");
	exit(-1);
}

void	child2(int fdout, int *pipe, char **ep, char **av)
{
	dup2(pipe[0], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(pipe[1]);
	execve("/usr/bin/wc", &av[2], ep);
	printf("Aqui Error: execve failed\n");
	exit(-1);
}
int main(int ac, char **av, char **ep)
{
	int	fdin = open("infile", O_RDONLY);
	int	fdout = open("outfile", O_WRONLY);
	int	pp1[2];
	int	pid;
	int	status;
	char *arg[4] = {"cat", "\0", "wc", "\0"};

	(void)av;
	(void)ac;
	if (pipe(pp1) == 1)
	{
		printf("Error al abrir los pipes\n");
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			child(fdin, pp1, ep, arg);
		}
		waitpid(pid, &status, 0);
		child2(fdout, pp1, ep, arg);
	} 
	close(pp1[1]);
	close(pp1[0]);
	close(fdin);
	close(fdout);
	waitpid(pid, &status, 0);
}
//pp[0]--->lectura en pipe
//pp[1]--->escritura en pipe
