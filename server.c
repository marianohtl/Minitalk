#include "server.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static t_queue	g_queue;

void	enqueue(int signal_number, siginfo_t *client_info, void *no_use)
{
	int	next;

	(void) no_use;
	g_queue.data[g_queue.end] = signal_number;
	next = (g_queue.end + 1) % QUEUE_SIZE;
	if (next != g_queue.start)
		g_queue.end = next;
	usleep(200);
	kill(client_info->si_pid, SIGUSR1);
}

void	decode(int size)
{
	char	*string;
	int		index;
	int		limit;

	if (size < 1)
		return ;
	string = calloc(1, sizeof(*string) * size);
	index = 0;
	limit = size * 8;
	while (index < limit)
	{
		g_queue.data[g_queue.start] = g_queue.data[g_queue.start] == SIGUSR2;
		string[index / 8] += g_queue.data[g_queue.start] << (7 - (index % 8));
		index++;
		g_queue.start = (g_queue.start + 1) % QUEUE_SIZE;
	}
	write(STDOUT_FILENO, string, size);
	free(string);
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

	g_queue.data = malloc(QUEUE_SIZE * 8);
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
	{
		if (g_queue.start / 8 != g_queue.end / 8)
		{
			if (g_queue.start > g_queue.end)
				decode(QUEUE_SIZE - g_queue.start / 8 + g_queue.end / 8);
			else
				decode(g_queue.end / 8 - g_queue.start / 8);
		}
		pause();
	}
	return (0);
}
