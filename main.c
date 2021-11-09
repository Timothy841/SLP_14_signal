#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

static void sighandler(int sig){
	if (sig == SIGINT){
		char c[] = "Program exited due to SIGINT.\n";
		int wrfile = open("error.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
		write(wrfile, &c, strlen(c));
		printf("%s\n", c);
		exit(0);
	}
	if (sig == SIGUSR1){
		printf("pid of parent process: %d\n", getppid());
	}
}

int main(){
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	while(1){
		printf("pid: %d\n", getpid());
		sleep(1);
	}
}
