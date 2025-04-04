/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/04 18:35:46 by riel-fas         ###   ########.fr       */
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

















#endif



//gettimeofday : int gettimeofday(struct timeval *tv, struct timezone *tz);
//succes return 0, or other value in faillure

//threads : smallest unit of execution in a process . while the process contains the program data, code
// code and ressources ; threads are the the actual execution unit within the process
//
//each thread has its own stack and program counter
//threads within the same process share the same memory space and ressources
//multiple threads can execute concurrently
