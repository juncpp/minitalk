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


char    *ft_copy(char *dest, char *src, char c)
{
    int i;

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

char    *ft_realloc(char *str, int flag, char c)
{
    char    *tmp;

    tmp = (char *)malloc(flag);
    if (tmp == NULL)
        return (NULL);
    tmp = ft_copy(tmp, str, c);
    return (tmp);
}

void    ft_realstr(char c, char **str, int flag)
{
    *str = (char *)ft_realloc(*str, flag + 2, c);
    if (*str == NULL)
    {
        free(str);
        return ;
    }
    (*str)[flag] = c;
    (*str)[flag + 1] = '\0'; 
}

void ft_newStr(char c, int flag)
{
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
        ft_realstr(c, &str, flag);
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

static inline void    sig1(int sig, siginfo_t *info, void *context)
{
    (void) context;
    (void) *info;
    static char c;
    static int i;
    static int flag;

    if (sig == SIGUSR1)
        c = (c | (1 << i));
    i++;
    if (i == 8)
    {
        // i = 0;
        // if (c != 0)
        //     write (1, &c, 1);
        // else
        //     write (1, &"\n", 1);
        // c = 0;
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