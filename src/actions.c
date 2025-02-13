

#include "philo.h"

void	print_action(t_philo *philo, int flag, char *action)
{
	pthread_mutex_lock(&philo->sim->action_flag);
	if (comprove_death(philo->sim))
	{
		if (flag == DIE)
		{
			pthread_mutex_lock(&philo->sim->check_flag);
			philo->sim->flag_death = 1;
			pthread_mutex_unlock(&philo->sim->check_flag);
		}
		printf(action, get_sim_time(philo->sim), philo->id + 1, RESET);
	}
	pthread_mutex_unlock(&philo->sim->action_flag);
}

void	action_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork1);
	print_action(philo, FORK, ACT_FORK);
	if (&philo->fork1 != philo->fork2)
	{
		pthread_mutex_lock(philo->fork2);
		print_action(philo, FORK, ACT_FORK);
		pthread_mutex_lock(&philo->last_meal_flag);
		philo->last_meal = get_sim_time(philo->sim);
		philo->n_meals++;
		pthread_mutex_unlock(&philo->last_meal_flag);
		print_action(philo, EAT, ACT_EAT);
		usleep(philo->sim->t_eat * 1000);
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(&philo->fork1);
	}
	else
		usleep(philo->sim->t_death * 1000);
}

static void	action_sleep(t_philo *philo)
{
	print_action(philo, SLEEP, ACT_SLEEP);
	usleep(philo->sim->t_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_action(philo, THINK, ACT_THINK);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (comprove_death(philo->sim) && philo->id % 2 != 0)
		usleep((philo->sim->t_eat - 1) * 1000);
	while (comprove_death(philo->sim) && philo->n_meals != philo->sim->n_meals)
	{
		action_eat(philo);
		if (philo->n_meals != philo->sim->n_meals)
		{
			action_sleep(philo);
			think(philo);
		}
	}
	return (0);
}
