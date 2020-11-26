/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:23:18 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 11:02:45 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*deci_part(double dbl, int accu, t_data *data)
{
	char	*res;
	int		i;

	i = -1;
	while (++i < accu)
		dbl *= 10;
	res = save_decimals(accu, dbl);
	if (data->precision == 0)
	{
		i = 0;
		if (res[i] >= (5 + '0'))
			data->udf = 1;
		ft_bzero(res, ft_strlen(res));
		return (res);
	}
	if (res[i - 1] >= (5 + '0'))
		res = round_up(res, i);
	else
		res = round_down(res, data, i);
	return (res);
}

static char		*integ_part(double *dbl)
{
	int		pow_max;
	int		i;
	double	tmp;
	char	*res;

	*dbl = (*dbl < 0 ? -*dbl : *dbl);
	tmp = *dbl;
	pow_max = 0;
	while (tmp > 10.0)
	{
		pow_max++;
		tmp /= 10;
	}
	if (!(res = ft_strnew(pow_max + 1)))
		error_message();
	i = 0;
	while (pow_max >= 0)
	{
		tmp = *dbl / ft_double_power(10, pow_max);
		res[i] = '0' + (int)tmp;
		*dbl -= (double)((int)tmp * ft_double_power(10, pow_max));
		pow_max--;
		i++;
	}
	return (res);
}

static void		set_more_rules_f(t_data *data, int num_len)
{
	if (data->spaces <= num_len)
		data->spaces = 0;
	data->precision = -1;
	if (data->flag_index[1] == 1)
		data->flag_index[2] = 0;
	if (data->flag_index[0] == 1)
		data->flag_index[3] = 0;
	if (data->int_neg != 1 && data->flag_index[1] == 1 &&
			(data->spaces == 0 || data->flag_index[0] == 1))
	{
		print_char(data, '+');
		data->spaces -= 1;
	}
	if (data->flag_index[2] == 1 && data->int_neg != 1)
	{
		print_char(data, ' ');
		data->spaces--;
		data->flag_index[2] = 0;
	}
}

static void		set_rules_f(t_data *data, double *nbr)
{
	if (*nbr < 0 && *nbr != -2147483648 && *nbr != (-9223372036854775807 - 1))
	{
		data->int_neg = 1;
		*nbr *= -1;
	}
	else
		data->int_neg = -1;
	if (data->precision == -1)
		data->precision = 6;
}

void			conversion_f(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	double	nbr;
	char	*integ;
	char	*deci;
	char	*str;

	parse_arg_ptr(format, data, spec_idx, conv_idx);
	parse_precision(format, data, spec_idx, conv_idx);
	parse_flags(format, data, spec_idx, conv_idx);
	nbr = (double)(va_arg(data->args[0], double));
	set_rules_f(data, &nbr);
	integ = integ_part(&nbr);
	deci = deci_part(nbr, (data->precision + 1), data);
	if (data->precision == 0)
		str = no_precision_dbl(data, integ);
	else
	{
		integ = ft_strcat(integ, ".");
		str = ft_strjoin(integ, deci);
	}
	set_more_rules_f(data, ft_strlen(str));
	padding_preprint(data, ft_strlen(str));
	ft_putstr(str);
	padding_postprint(data, ft_strlen(str));
	data->len += ft_strlen(str);
	free_strs(integ, deci, str);
}
