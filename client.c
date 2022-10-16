#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

int main(void)
{
	kill( 8166 ,SIGUSR1);
	return(0);
}