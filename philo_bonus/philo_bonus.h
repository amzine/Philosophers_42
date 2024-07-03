/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:44:18 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/08 02:33:49 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>

struct	s_rules;

typedef struct s_philosopher
{
	int				id;
	int				x_eat;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		death_check;
	pid_t			proces_id;
}					t_philo;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	long long			first_timestamp;
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*writing;
	t_philo				philosophers[250];
}	t_rules;

int			ft_atoi(char *str);
void		print_event(t_rules *rules, int id, char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long present);
void		print_action(t_rules *rules, int id, char *str);
int			begin(t_rules *rules);
void		sleep_philo(long long time, t_rules *rules);
void		exit_philo(t_rules *rules);

#endif