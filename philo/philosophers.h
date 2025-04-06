/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 06:41:21 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				philo_id;
	int				meal_count;
	int				full;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*right_fork;
	t_fork			*left_fork;
	struct s_args	*input; // Link back to main data
}	t_philosopher;

typedef struct s_args
{
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_limit;
	bool			simulation_off;
	long			start_time;
	t_philosopher	*philosophers;
	t_fork			*forks;
	pthread_mutex_t	sim_mutex;
}	t_args;

// Main functions
void	philo_act(t_args *input);
int		input_pars(int ac, char **av, t_args *input);

// Initialization functions
void	init_forks(t_args *input);
void	init_philosophers(t_args *input);
void	create_threads(t_args *input);

// Philosopher routines
void	*philosopher_routine(void *arg);
void	pick_forks(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	release_forks(t_philosopher *philo);

// Utility functions
void	error_mes_exit(char *error);
long	get_current_time(void);
void	precise_sleep(long milliseconds);
void	print_status(t_philosopher *philo, char *status);
void	monitor_philosophers(t_args *input);
void	cleanup_resources(t_args *input);

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
