#include "minitalk_bonus.h"

char	*ft_copy(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}

char	*ft_realloc(char *str, int flag, char c)
{
	char	*tmp;

	tmp = (char *) malloc(flag);
	if (tmp == NULL)
		return (NULL);
	tmp = ft_copy(tmp, str, c);
	free(str);
	return (tmp);
}

void	ft_realstr(char c, char **str, int flag)
{
	char	*tmp;

	tmp = (char *) malloc(flag + 2);
	if (tmp == NULL)
	{
		free(*str);
		return ;
	}
	tmp = ft_copy(tmp, *str, c);
	free(*str);
	*str = tmp;
}

void	ft_newstr(char c, int flag)
{
	static char	*str;
	int			j;

	j = 0;
	if (flag == 0)
	{
		str = (char *)malloc(sizeof(char) + 1);
		if (str == NULL)
			return ;
		str[0] = c;
		str[1] = '\0';
	}
	else if (flag > 0)
		ft_realstr(c, &str, flag);
	else
	{
		while (str[j])
		{
			write (1, &str[j], 1);
			j++;
		}
		write (1, "\n", 1);
		free(str);
	}
}

void	sig1(int sig, siginfo_t *info, void *context)
{
	static int	i;
	static char	c;
	static int	flag;

	(void) context;
	if (sig == SIGUSR1)
		c = (c | (1 << i));
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			ft_newstr(c, -1);
			flag = 0;
		}
		else
			ft_newstr(c, flag++);
		c = 0;
	}
	usleep(150);
	kill(info->si_pid, SIGUSR1);
}

int	main()
{
	struct sigaction	one;

	one.sa_sigaction = &sig1;
	one.sa_flags = SA_SIGINFO;
	printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &one, NULL);
	sigaction(SIGUSR2, &one, NULL);
	while (1)
		pause();
	return (0);
}