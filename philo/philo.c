/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:34:24 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/09 23:59:25 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	recuperer_arg(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_death = ft_atoi(av[2]);
	rules->time_eat = ft_atoi(av[3]);
	rules->time_sleep = ft_atoi(av[4]);
	rules->all_eat = 0;
	rules->died = 0;
	if (rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0 || rules->nb_philo <= 0)
	{
		printf("at least one wrong argument\n");
		return (1);
	}
	if (av[5])
	{
		rules->nb_eat = ft_atoi(av[5]);
		if (rules->nb_eat <= 0)
		{
			printf("at least one wrong argument\n");
			return (1);
		}
	}
	else
		rules->nb_eat = -1;
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
		{
			printf("error when initiallizing mutex\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
	{
		printf("error when initiallizing mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(rules->meal_check), NULL))
	{
		printf("error when initiallizing mutex\n");
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
		rules->philosophers[i].left_fork = i;
		rules->philosophers[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philosophers[i].x_eat = 0;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].id = i;
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
	if (recuperer_arg(&rules, av))
		return (0);
	if (init_mutex(&rules))
		return (0);
	init_philos(&rules);
	if (begin(&rules))
		return (0);
	return (0);
}
