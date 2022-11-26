#ifndef SERVER_H
# define SERVER_H
# define QUEUE_SIZE 8192

typedef struct s_queue
{
	char	*data;
	int		start;
	int		end;
}	t_queue;

#endif
