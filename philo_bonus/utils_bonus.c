/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:33 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/08 02:36:33 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + (t.tv_usec / 1000));
}

void	sleep_philo(long long time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	print_action(t_rules *rules, int id, char *str)
{
	sem_wait(rules->writing);
	printf("%lli ", timestamp() - rules->first_timestamp);
	printf("%i ", id + 1);
	printf("%s\n", str);
	sem_post(rules->writing);
	return ;
}
