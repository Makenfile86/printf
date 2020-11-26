/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:05:22 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/01 11:21:29 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		parse_all(const char *format, t_data *data,
int spec_idx, int conv_idx)
{
	parse_arg_ptr(format, data, spec_idx, conv_idx);
	parse_precision(format, data, spec_idx, conv_idx);
	parse_data_types(format, data, spec_idx, conv_idx);
	parse_flags(format, data, spec_idx, conv_idx);
}

static void		set_rules_d(t_data *data, intmax_t *nbr, int *num_len)
{
	if (*nbr < 0 && *nbr != -2147483648 && *nbr != (-9223372036854775807 - 1))
	{
		data->int_neg = 1;
		*nbr *= -1;
	}
	else if (*nbr == -2147483648)
	{
		*nbr = 2147483648;
		data->int_neg = 1;
	}
	else if (*nbr == (-9223372036854775807 - 1))
	{
		data->int_neg = 1;
		*num_len = 20;
	}
	else
		data->int_neg = -1;
	if (*nbr == 0 && data->precision == 0)
		*num_len = 0;
	if (data->flag_index[1] == 1)
		data->flag_index[2] = 0;
}

static intmax_t	get_num(t_data *data)
{
	intmax_t nbr;

	if (data->conversion == 'D')
		nbr = (long)(va_arg(data->args[0], long int));
	else if (data->type[0] == 'h' && data->type[1] == '\0')
		nbr = (short)(va_arg(data->args[0], int));
	else if (data->type[0] == 'h' && (data->type[1] == 'h'))
		nbr = (signed char)(va_arg(data->args[0], int));
	else if (data->type[0] == 'l' && (data->type[1] == '\0'))
		nbr = (long)(va_arg(data->args[0], long int));
	else if (data->type[0] == 'l' && (data->type[1] == 'l'))
		nbr = (long long)(va_arg(data->args[0], long long int));
	else if (data->type[0] == 'j' && (data->type[1] == '\0'))
		nbr = (intmax_t)(va_arg(data->args[0], intmax_t));
	else if (data->type[0] == 'z' && (data->type[1] == '\0'))
		nbr = (size_t)(va_arg(data->args[0], size_t));
	else
		nbr = (int)va_arg(data->args[0], int);
	nbr = (intmax_t)nbr;
	return (nbr);
}

void			conversion_d(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	intmax_t	nbr;
	int			num_len;

	parse_all(format, data, spec_idx, conv_idx);
	nbr = get_num(data);
	num_len = count_int_len(nbr);
	set_rules_d(data, &nbr, &num_len);
	if (data->int_neg != 1 && data->flag_index[1] == 1 &&
			(data->spaces == 0 || data->flag_index[0] == 1))
	{
		print_char(data, '+');
		data->spaces--;
	}
	if (data->flag_index[2] == 1 && data->int_neg != 1)
	{
		print_char(data, ' ');
		data->spaces--;
		data->flag_index[2] = 0;
	}
	padding_preprint(data, num_len);
	if (nbr != 0 || data->precision != 0)
		ft_putnbrmax_fd(nbr, 1, data);
	padding_postprint(data, num_len);
}
