#include "minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						negative;
	unsigned long long int	num;

	num = 0;
	i = 0;
	negative = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (num >= 9223372036854775807 && negative > 0)
			return (-1);
		if (num > 9223372036854775807 && negative < 0)
			return (0);
	}
	return ((int) num * negative);
}

void	checkpid(int sig, siginfo_t *info, void *context)
{
	(void) *info;
	(void) context;
	(void) sig;
	//printf ("Сигнал пришел\n");
}

void	mystr(char c, int pid)
{
	int					i;
	struct sigaction	get;

	get.sa_sigaction = &checkpid;
	get.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &get, NULL);
	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		pause();
		//usleep(50);
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main(int pd, char **str)
{
	int	pid;

	pid = ft_atoi(str[1]);
	if (pd != 3)
		return (1);
	while (*(str[2]) != '\0')
		mystr(*(str[2]++), pid);
	mystr(0, ft_atoi(str[1]));
	return (0);
}
