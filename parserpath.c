#include "pipex.h"

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

