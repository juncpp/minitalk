/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:45:35 by mmeredit          #+#    #+#             */
/*   Updated: 2021/12/16 17:45:37 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>


int ft_pow(int i, int num)
{
    int x;

    x = 2;
    while (num != -1)
    {
        x = x * i;
        num--;
    }
    return (x);
}

static void    sig1(int sig, siginfo_t *info, void *context)
{
    (void) sig;
    (void) *context;
    static int x;
    static int check;

    printf ("check= %d\n", check);
    sleep(5);
    if (sig == SIGUSR2)
    {
        printf ("sig= %d\n", sig);
        check++;
    }
    else
    {
        x += ft_pow(2, check);
        check++;
        kill (info->si_pid, SIGUSR1);
        if (check == 8)
        {
            printf("x2= %c\n", x);
            check = 0;
            x = 0;
            kill (info->si_pid, SIGUSR1);
        }
    }
}

// void    sig2(int sig, siginfo_t *info, void *context)
// {
//     (void) sig;
//     (void) *context;
//     int x;

//     x = 0;
//     kill (info->si_pid, SIGUSR1);
// }

int main()
{
    struct sigaction one;
    struct sigaction zero;

    one.sa_sigaction = &sig1;
    one.sa_flags = SA_SIGINFO;

    zero.sa_sigaction = &sig1;
    zero.sa_flags = SA_SIGINFO;
    printf("Server PID: %d\n", getpid());
    if (sigaction(SIGUSR1, &one, NULL) < 0)
        printf ("Error1");
    if (sigaction(SIGUSR2, &one, NULL) < 0)
        printf ("Error1");
    while(1)
        pause();
    return (0);
}