/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_padding_rules.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 10:14:35 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 10:19:52 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	others(t_data *data, int *len, int *zero_pad, int *space_pad)
{
	{
		*zero_pad = data->precision - *len;
		if (data->precision > 0 && data->precision >= *len
				&& data->int_neg == 1)
			*zero_pad += 1;
	}
	if (data->flag_index[0] == 1 && data->int_neg == 1)
		print_char(data, '-');
	if (*zero_pad > 0)
	{
		*space_pad = data->spaces - *zero_pad - *len;
		if (data->conversion == 'p')
			*space_pad -= 2;
		if (data->int_neg == 1 && data->precision > 0)
			*space_pad += 1;
	}
	else
	{
		*space_pad = data->spaces - *len;
		if (data->int_neg == 1 && data->precision < *len
				&& data->conversion != 'f')
			*space_pad += 1;
	}
}

void	zero_noprec_right(t_data *data, int *len, int *zero_pad)
{
	if (data->int_neg == 1)
	{
		print_char(data, '-');
		if (data->conversion == 'f')
			*len += 1;
	}
	*zero_pad = data->spaces - *len;
	if (data->flag_index[2] == 1 && data->int_neg != 1)
	{
		*zero_pad -= 1;
		data->spaces -= 1;
		print_char(data, ' ');
	}
	if (data->int_neg == -1 && data->flag_index[1] == 1)
	{
		*zero_pad -= 1;
		data->spaces -= 1;
		print_char(data, '+');
	}
}

void	precision_prevail(t_data *data, int *len, int *zero_pad, int *space_pad)
{
	*zero_pad = data->precision - *len;
	if (data->int_neg == 1)
	{
		*space_pad = 1;
		*zero_pad += 1;
		if (data->flag_index[0] == 1)
			print_char(data, '-');
	}
	else if (data->int_neg == -1 && data->spaces > 0
			&& data->flag_index[1] == 1)
		*space_pad = 1;
	else
		*space_pad = 0;
}

void	len_prevail(t_data *data, int *space_pad)
{
	if (data->int_neg == 1)
	{
		*space_pad = 1;
		if (data->flag_index[0] == 1)
			print_char(data, '-');
	}
	if (data->int_neg == -1)
	{
		if (data->flag_index[1] == 1 && data->flag_index[0] == 0
				&& data->spaces > 0)
			*space_pad = 1;
	}
}
