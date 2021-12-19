/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:45:26 by mmeredit          #+#    #+#             */
/*   Updated: 2021/12/16 17:45:28 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include "ft_printf"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


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

void checkpid (int sig, siginfo_t *info, void *context)
{
    (void) sig;
    (void) *info;
    (void) *context;
}

static void    mystr(char *str, int pid)
{
    static char c;
    static int  num;

    if (num == 7)
        num = 0;
    while (*str)
    {
        c = *str;
        str++;
        while (num != 7)
        {
            num++;
            if (c & 1)
            {
                c = c >> 1;
                printf ("Побитово 1\n");
                kill(pid, SIGUSR1);
            }
            else
            {
                c = c >> 1;
                kill(pid, SIGUSR2);
                printf ("Побитово 2\n");
            }
        }
    }
    if (!*str)
        exit(0);
}

int main(int pd, char **str)
{
    struct sigaction sig;
    pid_t pid;
    int n;

    (void) pid;
    (void) n;
    if (pd != 3)
        return (1);
     sig.sa_sigaction = &checkpid;
     sig.sa_flags = SA_SIGINFO;
     sigaction(SIGUSR1, &sig, NULL);
    //sig.sa_handler = &checkpid;
    // Готов ли сервер принимать сигнал.
    mystr(str[2], ft_atoi(str[1]));
    while(1)
        pause();
    return (0);
}