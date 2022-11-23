#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

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

int main(int argc, char **argv)
{
	static int index;
	static int index_string;
	int	pid;

	if(argc != 3)
		return 1;
	pid = ft_atoi(argv[1]);
	while(argv[2][index_string] != '\0')
	{
		while (index < 8)
		{
			if ((argv[2][index_string] >> (7 - index)) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			index++;
			usleep(120);
		}
		index = 0;
		index_string++;
	}
	return(0);
}