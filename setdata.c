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
	pdata->options[0] = ft_strdup(&av[2][ft_strlen(pdata->cmd[0]) + 1]);
	pdata->cmd[1] = ft_strdup(av[3]);
	pdata->options[1] = ft_strdup(&av[3][ft_strlen(pdata->cmd[1]) + 1]);
	puts("sale de ft_parserarg");
}
//set fdin, fdout, pp, cmd and options in data structure
void	ft_setdata(t_argdata *pdata, char	**av)
{
	if (!access(av[1], F_OK | R_OK))
		pdata->fdin = open(av[1], O_RDONLY);
	else
	{
		perror("Error: input file invalid");
		exit(-1);
	}
	if (!access(av[4], F_OK | W_OK))
		pdata->fdout = open(av[4], O_WRONLY);
	else
	{
		perror("Error: output file invalid");
		exit(-1);
	}
	if (pipe(pdata->pp) == 1)
	{
		perror("Error: pipe daemon error");
		exit(-1);
	}
	ft_parserarg(av, pdata);
	puts("sale de setdata");
}

