/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 09:45:29 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 09:52:58 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		post_padding_addons_xpo(t_data *data)
{
	if (data->conversion == 'X')
		write(1, "0X", 2);
	else if (data->conversion == 'x' || data->conversion == 'p')
		write(1, "0x", 2);
	else
		print_char(data, '0');
	if (data->conversion != 'o')
		data->len += 2;
}

static int	padding_addons_p(t_data *data, int space_pad)
{
	if (space_pad == 0)
	{
		write(1, "0x", 2);
		data->len += 2;
		return (0);
	}
	else
		return (1);
}

static int	padding_addons_xo(t_data *data, int len)
{
	if (data->flag_index[3] == 1 || data->spaces <= len)
	{
		if (data->conversion == 'X')
			write(1, "0X", 2);
		if (data->conversion == 'x')
			write(1, "0x", 2);
		if (data->conversion == 'o')
			print_char(data, '0');
		else
			data->len += 2;
		return (0);
	}
	return (1);
}

void		padding_postprint(t_data *data, int len)
{
	int space_pad;

	if (data->flag_index[0] == 1)
	{
		if (data->conversion == 'f' && data->int_neg == 1)
			len++;
		if (data->flag_index[4] == 1 && data->conversion == 'o')
			len++;
		if (data->precision > len || data->precision + data->int_neg > len)
		{
			if (data->int_neg == 1)
				len--;
			space_pad = (data->spaces - len - (data->precision - len));
		}
		else
			space_pad = (data->spaces - len);
		if (data->int_neg == 1 && data->spaces > data->precision &&
				data->precision > len)
			space_pad--;
		while (space_pad > 0)
		{
			print_char(data, ' ');
			space_pad--;
		}
	}
}

void		padding_preprint(t_data *data, int len)
{
	int space_pad;
	int zero_pad;
	int zerox_sign;

	zero_pad = 0;
	space_pad = 0;
	zerox_sign = 0;
	if (data->spaces > len && data->spaces > data->precision)
	{
		if (data->flag_index[3] == 1 && data->precision == -1 &&
				data->flag_index[0] == 0)
			zero_noprec_right(data, &len, &zero_pad);
		else
			others(data, &len, &zero_pad, &space_pad);
	}
	else if (data->precision >= data->spaces)
		precision_prevail(data, &len, &zero_pad, &space_pad);
	else
		len_prevail(data, &space_pad);
	if (data->flag_index[4] == 1 && (data->conversion == 'x' ||
				data->conversion == 'X' || data->conversion == 'o'))
		zerox_sign = padding_addons_xo(data, len);
	if (data->conversion == 'p')
		zerox_sign = padding_addons_p(data, space_pad);
	print_padding(data, space_pad, zero_pad, zerox_sign);
}
