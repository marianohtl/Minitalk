/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:30:13 by tmariano          #+#    #+#             */
/*   Updated: 2022/11/27 04:52:31 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define QUEUE_SIZE 8192

typedef struct s_queue
{
	char	data[QUEUE_SIZE];
	int		start;
	int		end;
}	t_queue;

#endif
