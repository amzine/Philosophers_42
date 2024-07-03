/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:44:09 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/09 23:27:12 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	print_action(rules, philo->id, "has taken a fork");
	sem_wait(rules->forks);
	print_action(rules, philo->id, "has taken a fork");
	sem_wait(rules->meal_check);
	print_action(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	sem_post(rules->meal_check);
	sleep_philo(rules->time_eat, rules);
	(philo->x_eat)++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	*death_checker(void *void_philo)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	while (1)
	{
		sem_wait(rules->meal_check);
		if (time_diff(philo->t_last_meal, timestamp()) > rules->time_death)
		{
			print_action(rules, philo->id, "died");
			exit(1);
		}
		sem_post(rules->meal_check);
		usleep(1000);
		if (philo->x_eat >= rules->nb_eat && rules->nb_eat != -1)
			break ;
	}
	return (NULL);
}

void	process_philo(void *philo_void)
{
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	rules = philo->rules;
	philo->t_last_meal = timestamp();
	pthread_create(&(philo->death_check), NULL, death_checker, philo_void);
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		philo_eats(philo);
		if (philo->x_eat >= rules->nb_eat && rules->nb_eat != -1)
			break ;
		print_action(rules, philo->id, "is sleeping");
		sleep_philo(rules->time_sleep, rules);
		print_action(rules, philo->id, "is thinking");
	}
	pthread_join(philo->death_check, NULL);
	exit(0);
}

void	exit_philo(t_rules *rules)
{
	int	i;
	int	x;

	i = 0;
	while (i < rules->nb_philo)
	{
		waitpid(-1, &x, 0);
		if (x != 0)
		{
			i = -1;
			while (++i < rules->nb_philo)
				kill(rules->philosophers[i].proces_id, 15);
			break ;
		}
		i++;
	}
	sem_close(rules->forks);
	sem_close(rules->writing);
	sem_close(rules->meal_check);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
}

int	begin(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (++i < rules->nb_philo)
	{
		philo[i].proces_id = fork();
		if (philo[i].proces_id < 0)
			return (1);
		if (philo[i].proces_id == 0)
			process_philo(&(philo[i]));
		usleep(100);
	}
	exit_philo(rules);
	return (0);
}
