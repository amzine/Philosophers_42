/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:53:01 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/06 06:01:16 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	print_action(rules, philo->id, " has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	print_action(rules, philo->id, " has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	print_action(rules, philo->id, " is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	sleep_philo(rules->time_eat, rules);
	(philo->x_eat)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
}

void	*action(void *void_philo)
{
	int			i;
	t_philo		*philo;
	t_rules		*rules;

	i = 0;
	philo = (t_philo *)void_philo;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->died) && rules->all_eat == 0)
	{
		philo_eats(philo);
		print_action(rules, philo->id, " is sleeping");
		sleep_philo(rules->time_sleep, rules);
		print_action(rules, philo->id, " is thinking");
		i++;
	}
	return (NULL);
}

void	death_check(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_eat))
	{
		i = 0;
		while (i < r->nb_philo && !(r->died))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				print_action(r, i, " died");
				r->died = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
			i++;
		}
		if (r->died)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_eat >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_eat = 1;
	}
}

void	exit_phi(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_detach(philo[i].thread_id);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
}

int	begin(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, action, &philo[i]))
		{
			printf("error when creating the threads\n");
			return (1);
		}
		philo[i].t_last_meal = timestamp();
		i++;
	}
	death_check(rules, rules->philosophers);
	exit_phi(rules, philo);
	return (0);
}
