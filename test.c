#include "pipex.h"

char	**parsepath(char **ep)
{
	unsigned int	i;
	char	*pathline;
	char	**paths;

	i = 0;
	while (ep[i])
	{
		pathline = ft_strnstr(ep[i], "PATH", 5);
		if (pathline)
		{
			pathline = ft_substr(pathline, 5, 200);
			paths = ft_split(pathline, ':');
			free(pathline);
			return (paths);
		}
		i++;
	}
	return 0;
}

int main(int argc, char *argv[], char **ep)
{
	char	**paths;
	int		i;

	(void)argc;
	(void)argv;
	paths = parsepath(ep);
	while (paths[i])
	{
		puts(paths[i]);
		free(paths[i]);
		i++;
	}
}
