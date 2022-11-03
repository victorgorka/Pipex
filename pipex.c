/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/03 15:10:23 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"


void	child(int fdin, int *pipe, char **ep, char **av)
{
	dup2(fdin, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	close(pipe[0]);
	execve(av[0], &av[0], ep);
	printf("Error 1: execve failed\n");
	exit(-1);
}

void	child2(int fdout, int *pipe, char **ep, char **av)
{
	dup2(fdout, STDOUT_FILENO);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[1]);
	close(pipe[0]);
	execve(av[0], &av[0], ep);
	printf("Error 2: execve failed\n");
	exit(-1);
}

// void	findpath(char **ep)
// {
//     
// }

int main(int ac, char **av, char **ep)
{
	int		fdin = open("infile", O_RDONLY);
	int		fdout = open("outfile", O_WRONLY);
	int		pp1[2];
	int		pid;
	int		status;
	char	*argv[] = {"/bin/cat", "-e", 0, "/usr/bin/wc", "-l", 0};

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
			child(fdin, pp1, ep, &argv[0]);
		}
		waitpid(pid, &status, 0);
		child2(fdout, pp1, ep, &argv[3]);
	} 
	close(pp1[1]);
	close(pp1[0]);
	close(fdin);
	close(fdout);
	waitpid(pid, &status, 0);
}
//pp[0]--->lectura en pipe
//pp[1]--->escritura en pipe
