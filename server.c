/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:30:08 by tmariano          #+#    #+#             */
/*   Updated: 2022/11/27 04:52:54 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static t_queue	g_queue;

void	decode(void)
{
	char	value;
	int		index;

	index = 0;
	while (index < 8)
	{
		if (index == 0)
			value = 0;
		if (g_queue.data[g_queue.start + index] == SIGUSR2)
			value += 1 << (7 - (index % 8));
		if (index == 7)
			write(STDOUT_FILENO, &value, 1);
		index++;
	}
}

void	enqueue(int signal_number, siginfo_t *client_info, void *no_use)
{
	static int	index;
	int			next;

	(void) no_use;
	g_queue.data[g_queue.end] = signal_number;
	index++;
	next = (g_queue.end + 1) % QUEUE_SIZE;
	if (next != g_queue.start)
		g_queue.end = next;
	if (index == 8)
	{
		decode();
		g_queue.start = (g_queue.start + 8) % QUEUE_SIZE;
		index = 0;
	}
	usleep(60);
	kill(client_info->si_pid, SIGUSR1);
}

size_t	ft_strlen(char *string)
{
	size_t	size;

	size = 0;
	while (*string++ != '\0')
		size++;
	return (size);
}

void	initialize(struct sigaction *handle)
{
	char	*pid;

	pid = ft_itoa(getpid());
	write(STDOUT_FILENO, "PID: ", 5);
	write(STDOUT_FILENO, pid, ft_strlen(pid));
	write(STDOUT_FILENO, "\n", 1);
	free(pid);
	handle->sa_sigaction = &enqueue;
	handle->sa_flags = SA_SIGINFO;
	sigemptyset(&handle->sa_mask);
	sigaddset(&handle->sa_mask, SIGUSR1);
	sigaddset(&handle->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, handle, NULL);
	sigaction(SIGUSR2, handle, NULL);
}

int	main(void)
{
	struct sigaction	handle;

	initialize(&handle);
	while (1)
		pause();
	return (0);
}
