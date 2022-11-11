/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/11 19:30:22 by vde-prad         ###   ########.fr       */
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

void	ft_freepaths(char	**paths, int	i)
{
	int	n;

	n = 0;
	while (paths[n])
	{
		if (n != i)
			free(paths[n]);	
		n++;
	}
	free(paths);
}

void	ft_setssufix(char	**paths, char	*cmd)
{
	char	*sufix;
	int		i;

	i = 0;
	sufix = malloc((ft_strlen(cmd) + 1) * sizeof(char));
	if (!sufix)
		perror("Error en reserva de memoria en 'sufix'\n");
	sufix = ft_strjoin("/", cmd);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], sufix);
		i++;	
	}
}

char	**ft_chkaccess(char	**paths, char	*cmd, char	*options)
{
	int		i;
	char	**res;

	ft_setssufix(paths, cmd);
	res = malloc(3 * sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], F_OK | R_OK))
		{
			res[0] = ft_strdup(paths[i]);
			res[1] = ft_strdup(options);
			res[2] = NULL;
			ft_freepaths(paths, i);
			return (res);
		}
		i++;
	}
	return (0);
}

char	**ft_getpath(char **ep, char *cmd, char *options)
{
	unsigned int	i;
	char	*pathline;
	char	**paths;

	paths = NULL;
	i = 0;
	while (ep[i])
	{
		pathline = ft_strnstr(ep[i], "PATH", 5);
		if (pathline)
		{
			pathline = ft_substr(pathline, 5, 200);
			paths = ft_split(pathline, ':');
			break;
		}
		i++;
	}
	free(pathline);
	return (ft_chkaccess(paths, cmd, options));
}

// int main(int ac, char **av, char **ep)
// {
//     int		fdin = open("infile", O_RDONLY);
//     int		fdout = open("outfile", O_WRONLY);
//     int		pp1[2];
//     int		pid;
//     int		status;
// 
//     (void)av;
//     (void)ac;
//     if (pipe(pp1) == 1)
//     {
//         printf("Error al abrir los pipes\n");
//         exit(-1);
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         pid = fork();
//         if (pid == 0)
//         {
//             child(fdin, pp1, ep, &argv[0]);
//         }
//         waitpid(pid, &status, 0);
//         child2(fdout, pp1, ep, &argv[3]);
//     } 
//     close(pp1[1]);
//     close(pp1[0]);
//     close(fdin);
//     close(fdout);
//     waitpid(pid, &status, 0);
// } 
// pp[0]--->lectura en pipe
// pp[1]--->escritura en pipe
// char	*argv[] = {"/bin/cat", "-e", 0, "/usr/bin/wc", "-l", 0};

int main(int argc, char *argv[], char **ep)
{
	char	**paths;
	int		i;

	i = -1;
	(void)argc;
	(void)argv;
	paths = ft_getpath(ep, "cat", "-e");
	while (paths[++i])
	{
		puts(paths[i]);
		free(paths[i]);
	}
}
