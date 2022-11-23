#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#define QUEUE_SIZE 8192

typedef struct s_queue
{
	char *content;
	int start;
	int end;
} t_queue;


static t_queue queue;

void scream(int signal_number)
{
	int	next;
	if (signal_number == SIGUSR2)
		queue.content[queue.end] = 1;
	else
		queue.content[queue.end] = 0;
	next = (queue.end + 1) % QUEUE_SIZE;
	if (next != queue.start)
		queue.end = next;
}

void	decode(int	size)
{
	char	*string;
	int		index;
	int		limit;

	string = calloc(1, sizeof(*string) * size);
	index = 0;
	limit = size * 8;
	while (index < limit)
	{
		string[index / 8] += queue.content[queue.start] << (7 - (index % 8));
		index++;
		queue.start = (queue.start + 1) % QUEUE_SIZE;
	}
	write(STDOUT_FILENO, string, size);
	free(string);
}

int main(void)
{
	struct sigaction handle;

	queue.content = malloc(QUEUE_SIZE * 8);
	printf("PID: %d\n" , getpid());

	handle.sa_handler = &scream;
	sigemptyset(&handle.sa_mask);
	sigaddset(&handle.sa_mask, SIGUSR1);
	sigaddset(&handle.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &handle, NULL);
	sigaction(SIGUSR2, &handle, NULL);

	while(1)
	{
		// usleep(10);
		if(queue.start != queue.end)
		{
			sleep(120);
			if(queue.start > queue.end)
			{
				decode(QUEUE_SIZE - queue.start / 8);
				decode(queue.end / 8);
			}
			else
				decode(queue.end / 8 - queue.start / 8);
		}
		else
			pause();
	}
	return(0);
}