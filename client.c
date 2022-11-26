#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

int	g_continue;

static unsigned int	ft_skip_spaces(const char *nptr)
{
	unsigned int	skip;

	skip = 0;
	while (nptr[skip] == ' ' || nptr[skip] == '\f'
		|| nptr[skip] == '\n' || nptr[skip] == '\r'
		|| nptr[skip] == '\v' || nptr[skip] == '\t')
		skip++;
	return (skip);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	skip;
	unsigned int	digit;
	unsigned int	mult;
	int				result;

	result = 0;
	mult = 1;
	skip = ft_skip_spaces(nptr);
	if (nptr[skip] == '+' || nptr[skip] == '-')
	{
		if (nptr[skip] == '-')
			mult = -1;
		skip++;
	}
	digit = skip;
	while (nptr[digit] >= '0' && nptr[digit] <= '9')
		digit++;
	while (digit > skip)
	{
		digit--;
		result += (nptr[digit] - '0') * mult;
		mult = mult * 10;
	}
	return (result);
}

void	release_client(int signal_number)
{
	(void) signal_number;
	g_continue = 0;
}

void	initialize_signal_handler(void)
{
	struct sigaction	handle;

	handle.sa_handler = &release_client;
	sigemptyset(&handle.sa_mask);
	sigaddset(&handle.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &handle, NULL);
}

int	main(int argc, char **argv)
{
	static int			index;
	static int			index_string;
	int					pid;
	int					signal_number;

	if (argc != 3)
		return (1);
	initialize_signal_handler();
	pid = ft_atoi(argv[1]);
	while (argv[2][index_string] != '\0')
	{
		while (index < 8)
		{
			signal_number = SIGUSR1;
			if ((argv[2][index_string] >> (7 - index++)) & 1)
				signal_number = SIGUSR2;
			g_continue = 1;
			kill(pid, signal_number);
			while (g_continue)
				usleep(20);
		}
		index = 0;
		index_string++;
	}
	return (0);
}
