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
	ft_parserarg(av, data);	
	dup2(data.fdin, STDIN_FILENO);
	dup2(data.pp[1], STDOUT_FILENO);
	close(data.pp[1]);
	close(data.pp[0]);
	execve(av[0], &av[0], ep);
	perror("Error 1: execve failed\n");
	exit(-1);
}

void	child2(t_argdata data, char **ep)
{
	ft_parserarg(av, data);
	dup2(fdout, STDOUT_FILENO);
	dup2(data.pp[0], STDIN_FILENO);
	close(data.pp[1]);
	close(data.pp[0]);
	execve(av[0], &av[0], ep);
	perror("Error 2: execve failed\n");
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
		perror("Error en reserva de memoria en '))sufix'\n");
	sufix = ft_strjoin("/", cmd);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], sufix);
		i++;	
	}
	free(sufix);
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

void	ft_parserarg(char	**av, t_argdata *pdata)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (i != 4)
	{
		while (av[i][j] != 0)
		{
			if (av[i][j] == ' ')
			{
				av[i][j] = '\0';
				break;
			}
			j++;
		}
		j = 0;
		i++;
	}
	pdata->cmd[0] = ft_strdup(av[2]);
	pdata->options[0] = ft_strdup(&av[2][ft_strlen(pdata->cmd[0]) + 1]);
	pdata->cmd[1] = ft_strdup(av[3]);
	pdata->options[1] = ft_strdup(&av[3][ft_strlen(pdata->cmd[1]) + 1]);
}

void	ft_setdata(t_argdata data, char	**av)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	if (!access(av[1], F_OK | R_OK))
		data.fdin = open(av[1], O_RDONLY);
	else
		perror("Error: input file invalid");
	if (!access(av[4]), F_OK | W_OK)
		data.fdout = open(av[4], O_WRONLY);
	else
		perror("Error: output file invalid");
	if (pipe(data.pp) == 1)
	{
		perror("Error: pipe daemon error");
		exit(-1);
	}
	ft_parserarg(av, t_argdata);
}

// int main(int ac, char **av, char **ep)
// {
//     int		pp1[2];
//     int		pid;
//     int		status;
//     t_argdata data;
// 
//     if(ac == 5)
//         ft_setdata(data, av);
//     else{
//         perror("Error: number of arguments not correct");
//         return (0);
//     }
//     if (pipe(data.pp) == 1)
//     {
//         perror("Error al abrir los pipes\n");
//         exit(-1);
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         pid = fork();
//         if (pid == 0)
//         {
//             child(data,ep);
//         }
//         waitpid(pid, &status, 0);
//         child2(data, ep);
//     } 
//     close(pp1[1]);
//     close(pp1[0]);
//     close(data.fdin);
//     close(data.fdout);
//     waitpid(pid, &status, 0);
// } 
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
