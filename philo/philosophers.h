/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/05 04:10:14 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h> // gettimeofday
# include <stdio.h> //printf
# include <stdlib.h> //malloc free
# include <unistd.h> //write usleep
# include <limits.h>
# include <pthread.h> //mutex : init destroy lock unlock
						//threads : creat join detach



typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;


}	t_fork;


typedef struct s_philosopher
{
	int					philo_id;
	long				meal_count;
	int					full;
	long				last_meal_time;

	//forks on right and left
	t_fork				*right_fork;
	t_fork				*left_fork;

	pthread_t			thread_id;

}	t_philosopher;



typedef struct s_args
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_limit;
	long				simulations_on;
	int					simulation_off;
	t_philosopher		philosophers;
	t_fork				forks;
}	t_args;

void	error_mes_exit(char *error);
void	input_pars(t_args *input, char **av);



#endif



//gettimeofday : int gettimeofday(struct timeval *tv, struct timezone *tz);
//succes return 0, or other value in faillure

//threads : smallest unit of execution in a process . while the process contains the program data, code
// code and ressources ; threads are the the actual execution unit within the process
//
//each thread has its own stack and program counter
//threads within the same process share the same memory space and ressources
//multiple threads can execute concurrently

//CPU //RAM
//Threads are fundamentally execution streams that run on CPU cores.
//The CPU is where the actual computation and instruction execution happen.

// What's in RAM vs. CPU
// >CPU: Executes the thread's instructions; holds the currently executing thread's state in registers
//
// >RAM: Stores the thread's:
// 	Stack (local variables, call history)
// 	Code it will execute
// 	Shared data with other threads
// 	Thread Control Block (TCB) - the OS's representation of the thread

// Thread Scheduling
// The operating system's scheduler determines:

//	> Which threads run on which CPU cores
//	> How long each thread runs before being paused
//	> The priority of threads



/////////////////////////CPU///////////////////////

// What are CPU Cores?
// A CPU core is a physical processing unit within the central processing unit (CPU) chip that reads and executes instructions.
// It represents the fundamental hardware component that performs computation.



//we can consider a thread as a virtual core

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │                                            COMPUTER SYSTEM                                                  │
// │                                                                                                             │
// │  ┌─────────────────────────────────────────────────────────────────────────────────────────────────────┐   │
// │  │                                      OPERATING SYSTEM                                               │   │
// │  │                                                                                                     │   │
// │  │  ┌───────────────────┐     ┌────────────────────────────┐      ┌──────────────────────────┐        │   │
// │  │  │ Thread Scheduler  │     │     Process Management     │      │    Memory Management     │        │   │
// │  │  └───────┬───────────┘     └────────────────────────────┘      └──────────────────────────┘        │   │
// │  │          │                                                                                         │   │
// │  └──────────┼─────────────────────────────────────────────────────────────────────────────────────────┘   │
// │             │                                                                                             │
// │  ┌──────────▼──────────────────────────────┐      ┌─────────────────────────────────────────────────────┐ │
// │  │          CPU (Physical Package)         │      │                       RAM                           │ │
// │  │  ┌─────────────────┐ ┌─────────────────┐│      │ ┌─────────────────────────────────────────────────┐ │ │
// │  │  │   Core 0        │ │   Core 1        ││      │ │               Process Memory                    │ │ │
// │  │  │ ┌─────┐ ┌─────┐ │ │ ┌─────┐ ┌─────┐ ││      │ │ ┌─────────────────────────────────────────────┐ │ │ │
// │  │  │ │Logic│ │Logic│ │ │ │Logic│ │Logic│ ││      │ │ │            Shared Memory Region             │ │ │ │
// │  │  │ │Core0│ │Core1│ │ │ │Core2│ │Core3│ ││      │ │ │ ┌─────────────┐  ┌──────────────────┐       │ │ │ │
// │  │  │ │  T1 │ │     │ │ │ │  T3 │ │  T2 │ ││      │ │ │ │ Input Image │  │ Processing Queue │       │ │ │ │
// │  │  │ └─────┘ └─────┘ │ │ └─────┘ └─────┘ ││      │ │ │ └─────────────┘  └──────────────────┘       │ │ │ │
// │  │  │                 │ │                 ││      │ │ │             ┌────────────────┐              │ │ │ │
// │  │  │ ┌─────────────┐ │ │ ┌─────────────┐ ││      │ │ │             │ Output Buffer  │              │ │ │ │
// │  │  │ │   L1 Cache  │ │ │ │   L1 Cache  │ ││      │ │ │             └────────────────┘              │ │ │ │
// │  │  │ └─────────────┘ │ │ └─────────────┘ ││      │ │ └─────────────────────────────────────────────┘ │ │ │
// │  │  │ ┌─────────────┐ │ │ ┌─────────────┐ ││      │ │                                                 │ │ │
// │  │  │ │   L2 Cache  │ │ │ │   L2 Cache  │ ││      │ │ ┌─────────────────────────────────────────────┐ │ │ │
// │  │  │ └─────────────┘ │ │ └─────────────┘ ││      │ │ │               Thread Stacks                 │ │ │ │
// │  │  └─────────────────┘ └─────────────────┘│      │ │ │ ┌────────┐  ┌────────┐  ┌────────┐  ┌─────┐  │ │ │ │
// │  │  ┌─────────────────────────────────────┐│      │ │ │ │ UI     │  │ Worker │  │ Worker │  │ I/O │  │ │ │ │
// │  │  │           L3 Cache                  ││      │ │ │ │ Thread │  │ Thread │  │ Thread │  │Thread│  │ │ │ │
// │  │  │                                     ││      │ │ │ │ Stack  │  │ Stack 1│  │ Stack 2│  │Stack │  │ │ │ │
// │  │  └─────────────────────────────────────┘│      │ │ │ │ (T1)   │  │ (T2)   │  │ (T3)   │  │(T4) │  │ │ │ │
// │  └──────────────────┬───────────────────────┘      │ │ │ └────────┘  └────────┘  └────────┘  └─────┘  │ │ │ │
// │                     │                              │ │ └─────────────────────────────────────────────┘ │ │ │
// │                     │                              │ │                                                 │ │ │
// │                     │                              │ │ ┌─────────────────────────────────────────────┐ │ │ │
// │  ┌─────────────────▼─────────────────────┐        │ │ │              Program Code                   │ │ │ │
// │  │         System Bus / Memory Bus       │        │ │ │ ┌─────────────┐  ┌─────────────┐            │ │ │ │
// │  └─────────────────┬─────────────────────┘        │ │ │ │ UI Code     │  │ Image       │            │ │ │ │
// │                    │                              │ │ │ │             │  │ Processing  │            │ │ │ │
// │  ┌─────────────────▼─────────────────────┐        │ │ │ └─────────────┘  │ Algorithms  │            │ │ │ │
// │  │                 I/O Bus               │        │ │ │                  └─────────────┘            │ │ │ │
// │  └──┬───────────────────────────────┬────┘        │ │ │ ┌─────────────┐  ┌─────────────┐            │ │ │ │
// │     │                               │             │ │ │ │ Thread      │  │ I/O         │            │ │ │ │
// │     │                               │             │ │ │ │ Management  │  │ Functions   │            │ │ │ │
// │  ┌──▼──────────────┐        ┌──────▼─────┐        │ │ │ │ Functions   │  │             │            │ │ │ │
// │  │     Storage     │        │   Network  │        │ │ │ └─────────────┘  └─────────────┘            │ │ │ │
// │  │  ┌────────────┐ │        │ Controller │        │ │ └─────────────────────────────────────────────┘ │ │ │
// │  │  │ Input      │ │        └────────────┘        │ └─────────────────────────────────────────────────┘ │ │
// │  │  │ Images     │ │                              └─────────────────────────────────────────────────────┘ │
// │  │  └────────────┘ │                                                                                      │
// │  │  ┌────────────┐ │                                                                                      │
// │  │  │ Output     │ │                              ┌────────────────────────────────────────────────────┐  │
// │  │  │ Images     │ │                              │           APPLICATION FLOW (TIME →)                │  │
// │  │  └────────────┘ │                              │                                                    │  │
// │  └─────────────────┘                              │  T1: UI Thread - Handles user interface, dispatches │  │
// │                                                   │      work to worker threads                         │  │
// │                                                   │  T2: Worker Thread 1 - Processes top half of image  │  │
// │                                                   │  T3: Worker Thread 2 - Processes bottom half of img │  │
// │                                                   │  T4: I/O Thread - Loads/saves images from/to disk   │  │
// │                                                   │                                                    │  │
// │                                                   │  Context Switch: When T2 waits for I/O, the CPU     │  │
// │                                                   │  core switches to another ready thread              │  │
// │                                                   └────────────────────────────────────────────────────┘  │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────┘


//pthread_creat ; create thread on a  loop
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
//                  >
//pthread_join ; get return value from the thread
// >pthread_join waits for the specified thread to finish before continuing execution.
//  It's a blocking function that causes the calling thread to pause until the thread being "joined" completes.
