/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 10:20:17 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 10:21:53 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

double		ft_double_power(double n, int pow)
{
	if (pow == 0)
		return (1);
	if (pow > 0)
		return (n * ft_double_power(n, pow - 1));
	if (pow < 0)
		return (n / ft_double_power(n, pow + 1));
	return (0);
}

void		free_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

int			count_int_len(intmax_t nbr)
{
	int len;

	len = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while ((nbr /= 10) > 0)
		len++;
	return (len);
}
