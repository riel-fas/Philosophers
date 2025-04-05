# include <pthread.h>
#include <stdio.h>
# include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void	*routine_f(){
	printf("waaaaaaaaaaaaaaa\n%d\n", getpid());
	sleep(3);
	printf("waaaaaaaaaaaaaaa22222222222\n%d\n", getpid());

}



int main(int ac, char **av){

	pthread_t	thread1;
	pthread_t	thread2;


	pthread_create(&thread1, NULL, &routine_f, NULL);
	pthread_create(&thread2, NULL, &routine_f, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	// int pid;


	// int pid = fork();
	// if (pid == -1)
	// 	return (1);
	// printf("wilililili%d\n", getpid());
	// if (pid != 0)
	// 	wait(NULL);

	return (0);
}
