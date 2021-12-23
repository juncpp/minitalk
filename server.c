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
    if (num == 0)
        return (1);
    if (num ==1)
        return (2);
    printf ("num= %d\n", num);
    while (num != 0)
    {
        x = x * i;
        num--;
    }
    return (x);
}

static void    sig1(int sig, siginfo_t *info, void *context)
{
    (void) *context;
    (void) *info;
    static char c;
    static int i;

    //printf ("check2= %d\n", info->si_pid);
    if (sig == SIGUSR1)
        c = (c | (1 << i));
    i++;
    if (i == 8)
    {
        i = 0;
        write (1, &c, 1);
        c = 0;
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
 //   struct sigaction zero;

    one.sa_sigaction = &sig1;
    one.sa_flags = SA_SIGINFO;

    // zero.sa_sigaction = &sig1;
    // zero.sa_flags = SA_SIGINFO;
    printf("Server PID: %d\n", getpid());
    sigaction(SIGUSR1, &one, NULL);
    sigaction(SIGUSR2, &one, NULL);
    while(1)
        pause();
    return (0);
}
