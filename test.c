#include "pipex.h"

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
	pdata->options[0] = ft_strdup(&av[2][ft_strlen(pdata->cmd[0] + 1)]);
	pdata->cmd[1] = ft_strdup(av[3]);
	pdata->options[1] = ft_strdup(&av[3][ft_strlen(pdata->cmd[1] + 1)]);
}

int main(int argc, char *argv[], char **ep)
{
	t_argdata data;
	
	(void)argc;
	(void)ep;
	
	data.fdin = 0;
	data.fdout = 0;
	data.pp[0] = 0;
	data.pp[1] = 0;
	ft_parserarg(argv, &data);
	puts(data.cmd[0]);
	puts(data.options[0]);
	puts(data.cmd[1]);
	puts(data.options[1]);
}
