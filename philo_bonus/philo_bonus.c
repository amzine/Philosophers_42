/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:44:12 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/09 22:36:45 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_arg(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_death = ft_atoi(av[2]);
	rules->time_eat = ft_atoi(av[3]);
	rules->time_sleep = ft_atoi(av[4]);
	if (rules->nb_philo < 0 || rules->time_death < 0
		|| rules->nb_eat < 0 || rules->time_sleep < 0)
	{
		printf("at least one wrong argument");
		return (1);
	}
	if (av[5])
	{
		rules->nb_eat = ft_atoi(av[5]);
		if (rules->nb_eat <= 0)
		{
			printf("at least one wrong argument");
			return (1);
		}
	}
	else
		rules->nb_eat = -1;
	return (0);
}

int	init_smaphores(t_rules *rules)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
	rules->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, rules->nb_philo);
	rules->writing = sem_open("/philo_write", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("/philo_mealcheck", O_CREAT, S_IRWXU, 1);
	if (rules->forks <= 0 || rules->meal_check <= 0 || rules->writing <= 0)
	{
		printf("error when creating semaphore");
		return (1);
	}
	return (0);
}

int	init_philos(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_eat = 0;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong ammount of arguments\n");
		return (0);
	}
	if (get_arg(&rules, av))
		return (0);
	if (init_smaphores(&rules))
		return (0);
	init_philos(&rules);
	if (begin(&rules))
		return (0);
	return (0);
}
