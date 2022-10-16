#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

void scream(int a){
	(void) a;
	write(STDOUT_FILENO,"AAAAAAH!\n",9);
}
void seg_scream(int a){
	(void) a;
	write(STDOUT_FILENO,"BBBBB!\n",9);
}

int main(void)
{
	struct sigaction handle;
	handle.sa_handler = &scream;
	//sigaction(SIGINT, &handle, NULL);
	sigaction(SIGUSR1, &handle, NULL);


	while(1)
	{
		printf("PID: %d\n" , getpid());
		sleep(5);
	}
	return(0);
}