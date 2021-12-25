/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:24:04 by mmeredit          #+#    #+#             */
/*   Updated: 2021/12/25 15:24:47 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int ft_atoi(const char *str)
{
    int                     i;
    int                     negative;
    unsigned long long int  num;

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
    (void) *info;
    (void) *context;
    printf ("Что за сигнал %d\n", sig);
}

static void    mystr(char *str, int pid)
{
    static char c;
    static int  i;

    while (*str)
    {
        c = *str;
        while (i < 8)
        {
            if (c & (1 << i))
                kill (pid, SIGUSR1);
            else
                kill (pid, SIGUSR2);
            i++;
            usleep(25);
        }
        i = 0;
        str++;
    }
    while (i++ < 8)
    {
        kill (pid, SIGUSR2);
        usleep(25);
    }
}

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

int main(int pd, char **str)
{
    pid_t pid;

    (void) pid;
    if (pd != 3)
        return (1);
    mystr(str[2], ft_atoi(str[1]));
    return (0);
}

