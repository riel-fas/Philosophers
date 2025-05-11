#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000) + (ct.tv_usec / 1000));
}

unsigned long	program_time(long start_time)
{
	return (timestamp() - start_time);
}

void	await(unsigned long ms, t_pinfo *pinfo)
{
	unsigned long	start_time;

	start_time = timestamp();
	while (timestamp() - start_time < ms && !get_died(pinfo))
		usleep(100);
}
