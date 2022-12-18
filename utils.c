/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:30:18 by tmariano          #+#    #+#             */
/*   Updated: 2022/11/27 04:30:19 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_digit(int numerator)
{
	int	digit;

	digit = 1;
	while (numerator > 9)
	{
		numerator = numerator / 10;
		digit++;
	}
	return (digit);
}

static void	ft_make_char_number(int n, char *number, int digit, char signal)
{
	number[digit] = '\0';
	digit--;
	while (digit >= 0)
	{
		number[digit] = n % 10 + '0';
		n = n / 10;
		digit--;
	}
	if (signal == 1)
		number[digit + 1] = '-';
}

char	*ft_itoa(int n)
{
	char	*number;
	char	signal;
	int		digit;

	signal = 0;
	if (n < 0)
	{
		n *= -1;
		signal = 1;
	}
	digit = ft_get_digit(n) + signal;
	number = malloc(digit + 1);
	if (number == NULL)
		return (number);
	ft_make_char_number(n, number, digit, signal);
	return (number);
}

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
