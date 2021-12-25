/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:24:16 by mmeredit          #+#    #+#             */
/*   Updated: 2021/12/25 15:24:58 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int  ft_strlen(const char *s)
{
    int  i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}


void    ft_realstr(char c, char **str)
{
    //char    *tmp;
    int i;

    i = ft_strlen(*str);
    *str = (char *)realloc(*str, i + 2);
    if (*str == NULL)
    {
        free(str);
        return ;
    }
    *str[i] = c;
    *str[i + 1] = '\0'; 
   // free(tmp);
}

static void ft_newStr(char c, int flag)
{
    int i;
    static char *str;
    int j;

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
    {
        //ft_realstr(c, &str);
        i = ft_strlen(str);
        str = (char *)realloc(str, i + 2);
        if (str == NULL)
        {
            free(str);
            return ;
        }
        str[i] = c;
        str[i + 1] = '\0';
    }
    else
    {
        while(str[j])
        {
            write (1, &str[j], 1);
            j++;
        } 
        write (1, "\n", 1);
        free(str);
    }
}

static void    sig1(int sig, siginfo_t *info, void *context)
{
    (void) *context;
    (void) *info;
    static char c;
    static int i;
    static int flag;
  //  static char *str;

    if (sig == SIGUSR1)
        c = (c | (1 << i));
    i++;
    if (i == 8)
    {
        i = 0;
        if (c == 0)
        {
            ft_newStr(c, -1);
            flag = 0;
        }
        else
            ft_newStr(c, flag++);
        c = 0;
    }
}

int main()
{
    struct sigaction one;

    one.sa_sigaction = &sig1;
    one.sa_flags = SA_SIGINFO;


    printf("Server PID: %d\n", getpid());
    sigaction(SIGUSR1, &one, NULL);
    sigaction(SIGUSR2, &one, NULL);
    while(1)
        pause();
    return (0);
}

