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
    //sleep(5);
    printf ("Что за сигнал %d\n", sig);
}

static void    mystr(char str, int pid)
{
    static char c;
    static int  i;

    printf ("PID= %d\n", pid);
    i = 0;
    c = str;
    while (i < 8)
    {
        if (c & (1 << i))
        {
            kill (pid, SIGUSR1);
            printf ("1\n");
        }
        else
        {
            kill (pid, SIGUSR2);
            printf ("0\n");
        }
        i++;
        usleep(1000);
    }
    c = 0;
  //  printf ("%d\n", i);
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
    int n;

    (void) pid;
    if (pd != 3)
        return (1);
    n = ft_strlen(str[2]);
   // printf ("%d\n", n);
    while (n != 0)
    {
        //printf("%c\n", *(str[2]));
        mystr(*(str[2]), ft_atoi(str[1]));
        str[2]++;
        n--;
    }
    return (0);
}
