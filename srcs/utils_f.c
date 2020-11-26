/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:23:18 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 11:02:05 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*no_precision_dbl(t_data *data, char *integ)
{
	char	*str;
	int		temp_int;

	temp_int = ft_atoi(integ);
	if (data->udf == 1)
		temp_int += 1;
	str = ft_itoa(temp_int);
	if (data->flag_index[4] == 1)
		str = ft_strcat(str, ".");
	return (str);
}

char	*round_up(char *res, int i)
{
	int y;

	y = 2;
	res[i - 1] = '\0';
	if (res[i - 2] == '9')
		res[i - 2] = '0';
	else
		res[i - 2] += 1;
	while (res[i - y] == '0' && (i - y > 0))
	{
		if (res[i - y - 1] == '9')
			res[i - y - 1] = '0';
		else
			res[i - y - 1] += 1;
		i--;
	}
	return (res);
}

char	*round_down(char *res, t_data *data, int i)
{
	i = data->precision;
	while (res[i] != '\0')
	{
		res[i] = '\0';
		i++;
	}
	res[data->precision] = '\0';
	return (res);
}

char	*save_decimals(int accu, double dbl)
{
	int		i;
	char	*res;
	double	tmp;

	i = 0;
	if (!(res = ft_strnew(19 + 1)))
		error_message();
	while (--accu >= 0)
	{
		tmp = dbl / ft_double_power(10.0, accu);
		if (accu == 0 && ((int)tmp + '0' == 5))
		{
			accu++;
			dbl *= 10;
		}
		res[i++] = '0' + (int)tmp;
		dbl -= (double)((int)tmp * ft_double_power(10.0, accu));
	}
	return (res);
}

char	*save_decimals_long(int accu, double dbl)
{
	int			i;
	char		*res;
	long double	tmp;

	i = 0;
	if (!(res = ft_strnew(19 + 1)))
		error_message();
	while (--accu >= 0)
	{
		tmp = dbl / ft_double_power(10.0, accu);
		if (accu == 0 && ((int)tmp + '0' == 5))
		{
			accu++;
			dbl *= 10;
		}
		res[i++] = '0' + (int)tmp;
		dbl -= (double)((int)tmp * ft_double_power(10.0, accu));
	}
	return (res);
}
