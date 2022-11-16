#include "pipex.h"

void	ft_parserarg(char	**av, t_argdata *pdata)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	pdata->options[0] = NULL;
	pdata->options[1] = NULL;
	while (i != 4)
	{
		while (av[i][j] != 0)
		{
			if (av[i][j] == ' ')
			{
				av[i][j] = '\0';
				pdata->options[i - 2] = ft_strdup(&av[i][ft_strlen(&av[i][0]) + 1]);
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	pdata->cmd[0] = ft_strdup(av[2]);
	pdata->cmd[1] = ft_strdup(av[3]);
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
	pdata->fdout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pdata->fdout < 0)
	{
		perror("Error: cannot open file");
		exit(-1);
	}
	if (pipe(pdata->pp) == 1)
	{
		perror("Error: pipe daemon error");
		exit(-1);
	}
	ft_parserarg(av, pdata);
}
