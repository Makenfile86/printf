/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_oO.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:47:00 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/01 11:57:50 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static uintmax_t	get_num(t_data *data)
{
	uintmax_t nbr;

	if (data->conversion == 'O')
		nbr = (unsigned long)(va_arg(data->args[0], unsigned long int));
	else if (data->type[0] == 'h' && data->type[1] == '\0')
		nbr = (unsigned short)(va_arg(data->args[0], unsigned int));
	else if (data->type[0] == 'h' && (data->type[1] == 'h'))
		nbr = (unsigned char)(va_arg(data->args[0], unsigned int));
	else if (data->type[0] == 'l' && (data->type[1] == '\0'))
		nbr = (unsigned long)(va_arg(data->args[0], unsigned long int));
	else if (data->type[0] == 'l' && (data->type[1] == 'l'))
		nbr = (unsigned long long)(va_arg(data->args[0],
					unsigned long long int));
	else if (data->type[0] == 'j' && (data->type[1] == '\0'))
		nbr = (uintmax_t)(va_arg(data->args[0], uintmax_t));
	else if (data->type[0] == 'z' && (data->type[1] == '\0'))
		nbr = (size_t)(va_arg(data->args[0], size_t));
	else
		nbr = (unsigned int)va_arg(data->args[0], unsigned int);
	nbr = (uintmax_t)nbr;
	return (nbr);
}

static int			set_rules_o(t_data *data, uintmax_t nbr, int num_len)
{
	if (nbr == 0 && num_len != 0)
		data->flag_index[4] = 0;
	data->flag_index[1] = 0;
	data->flag_index[2] = 0;
	if (data->precision > -1)
		data->flag_index[3] = 0;
	if (data->flag_index[2] == 1 && data->int_neg != 1)
	{
		print_char(data, ' ');
		data->spaces--;
		data->flag_index[2] = 0;
	}
	if (data->flag_index[4] == 1 && data->conversion == 'o')
		return (1);
	return (0);
}

void				conversion_o(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	uintmax_t	nbr;
	char		*str;
	int			num_len;
	int			zero_sign;

	parse_arg_ptr(format, data, spec_idx, conv_idx);
	parse_precision(format, data, spec_idx, conv_idx);
	parse_data_types(format, data, spec_idx, conv_idx);
	parse_flags(format, data, spec_idx, conv_idx);
	nbr = get_num(data);
	str = ft_itoa_base(nbr, 8, 'a');
	num_len = ft_strlen(str);
	if (data->precision == 0 && nbr == 0)
	{
		ft_bzero(str, ft_strlen(str));
		num_len = 0;
	}
	zero_sign = set_rules_o(data, nbr, num_len);
	padding_preprint(data, num_len + zero_sign);
	if (num_len != 0)
		ft_putstr(str);
	padding_postprint(data, num_len);
	data->len += num_len;
	free(str);
}
