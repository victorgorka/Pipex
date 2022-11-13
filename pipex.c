/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/12 19:06:35 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"


void	child(t_argdata data, char **ep)
{
	char	**av;

	av = ft_getpath(ep, data.cmd[0], data.options[0]);
	dup2(data.fdin, STDIN_FILENO);
	dup2(data.pp[1], STDOUT_FILENO);
	close(data.pp[1]);
	close(data.pp[0]);
	perror("estoy en hijo 1");
	execve(av[0], &av[0], ep);
	perror("Error 1: execve failed\n");
	exit(-1);
}

void	child2(t_argdata data, char **ep)
{
	char	**av;
	//char buffer[900];
	//char *arg[20] = {"wc", "-c", "infile", NULL};

	av = ft_getpath(ep, data.cmd[1], data.options[1]);
	dup2(data.fdout, STDOUT_FILENO);
	dup2(data.pp[0], STDIN_FILENO);
	close(data.pp[0]);
	close(data.pp[1]);
	//read(0, buffer, 800);
	//printf("buffer: %s\n", buffer);
	printf("av: %s, av1: %s\n", av[0], av[1]);
	av[1] = NULL;
	perror("estoy en hijo 2");
	execve(av[0], &av[0], ep);
	perror("Error 2: execve failed\n");
	exit(-1);
}

int main(int ac, char **av, char **ep)
{
	 int		pid;
	 int		status;
	 t_argdata data;
 

	if(ac == 5)
		ft_setdata(&data, av);
	else{
		perror("Error: number of arguments not correct");
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			 child(data,ep);
		}
		wait(&status);
		//waitpid(pid, &status, 0);
		child2(data, ep);
	} 
	close(data.pp[1]);
	close(data.pp[0]);
	//waitpid(pid, &status, 0);
	wait(&status);
	puts("llego padre");
	close(data.fdin);
	close(data.fdout);
} 
// pp[0]--->lectura en pipe
// pp[1]--->escritura en pipe
// char	*argv[] = {"/bin/cat", "-e", 0, "/usr/bin/wc", "-l", 0};

// int main(int argc, char *argv[], char **ep)
// {
//     char	**paths;
//     int		i;
// 
//     i = -1;
//     (void)argc;
//     (void)argv;
//     paths = ft_getpath(ep, "cat", "-e");
//     while (paths[++i])
//     {
//         puts(paths[i]);
//         free(paths[i]);
//     }
// }
