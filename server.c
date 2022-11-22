#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

typedef struct s_queue
{
	char * content;
	int start;
	int end;
} t_queue;


static t_queue queue;

void scream(int signal_number){
	static int index;
	const unsigned char	bit = 0b10000000;

	if(signal_number == SIGUSR2)
		queue.content[queue.end] = queue.content[queue.end] | (bit >> index);
	index++;
	if(index == 8)
	{
		queue.end = (queue.end + 1)%4096;
		index = 0;
	}

}
void seg_scream(int a){
	(void) a;
	write(STDOUT_FILENO,"BBBBB!\n",9);
}

int main(void)
{
	struct sigaction handle;
	// struct sigaction handle2;
	queue.content = malloc(4096);

	printf("PID: %d\n" , getpid());


	handle.sa_handler = &scream;
	sigemptyset(&handle.sa_mask);
	sigaddset(&handle.sa_mask, SIGUSR1);
	sigaddset(&handle.sa_mask, SIGUSR2);
	// handle2.sa_handler = &scream;
	// sigemptyset(&handle2.sa_mask);
	// sigaddset(&handle2.sa_mask, SIGUSR1);
	// sigaddset(&handle2.sa_mask, SIGUSR2);
	//sigaction(SIGINT, &handle, NULL);
	sigaction(SIGUSR1, &handle, NULL);
	sigaction(SIGUSR2, &handle, NULL);
	// sigaction(SIGUSR1, &handle2, NULL);
	// sigaction(SIGUSR2, &handle2, NULL);

	while(1)
	{
		usleep(10);
		if(queue.start != queue.end)
		{
			if(queue.start > queue.end)
			{
				write(1, queue.content , 4096 - queue.start);
				queue.start = write(1, queue.content , queue.end);
			}
			else
				queue.start += write(1, queue.content , queue.end - queue.start);
		}
		else
			pause();
	}
	return(0);
}