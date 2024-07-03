/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 23:50:58 by amimouni          #+#    #+#             */
/*   Updated: 2022/09/04 23:53:44 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct	s_rules;

typedef struct s_philosopher
{
	int				id;
	int				x_eat;
	int				left_fork;
	int				right_fork;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					died;
	int					all_eat;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philo				philosophers[250];
}	t_rules;

int			ft_atoi(char *str);
void		print_event(t_rules *rules, int id, char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long present);
void		print_action(t_rules *rules, int id, char *str);
int			begin(t_rules *rules);
void		sleep_philo(long long time, t_rules *rules);
void		death_check(t_rules *r, t_philo *p);
void		exit_phi(t_rules *rules, t_philo *philo);

#endif