

#include "philo.h"

unsigned int	get_current_time(void)
{
	struct timeval		tmp;
	unsigned int		current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned int)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}

unsigned int	get_sim_time(t_table *sim)
{
	return (get_current_time() - sim->t_start);
}

int	comprove_death(t_table *sim)
{
	int	caput;

	caput = 1;
	pthread_mutex_lock(&sim->check_flag);
	if (sim->flag_death == 1)
		caput = 0;
	pthread_mutex_unlock(&sim->check_flag);
	return (caput);
}
