/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 10:58:39 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/01 11:04:56 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	padding_sc(t_data *data, int len, char c)
{
	int spaces;

	if (data->precision > 0 && data->precision < len)
		len = data->precision;
	if (data->precision == 0)
		len = 0;
	spaces = (data->spaces - len);
	if (data->flag_index[2] == 1 && data->spaces <= 0 &&
			data->flag_index[0] == 0)
		print_char(data, ' ');
	while (spaces > 0)
	{
		if (data->flag_index[3] == 1 && data->flag_index[0] == 0)
			c = '0';
		print_char(data, c);
		spaces--;
	}
}

void	padding_gate_sc(t_data *data, int flag_value, int len)
{
	if ((data->spaces > 0 || data->precision > 0) &&
			data->flag_index[0] == flag_value)
		padding_sc(data, len, ' ');
}

void	conversion_s(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	char	*str;
	int		len;

	parse_arg_ptr(format, data, spec_idx, conv_idx);
	parse_precision(format, data, spec_idx, conv_idx);
	parse_flags(format, data, spec_idx, conv_idx);
	parse_data_types(format, data, spec_idx, conv_idx);
	str = va_arg(data->args[0], char *);
	if (str)
		str = ft_strdup(str);
	else if (!str)
		str = ft_strdup("(null)");
	len = ft_strlen(str);
	padding_gate_sc(data, 0, len);
	print_str(data, str);
	padding_gate_sc(data, 1, len);
	free(str);
}

void	conversion_c(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	wint_t c;

	parse_arg_ptr(format, data, spec_idx, conv_idx);
	parse_precision(format, data, spec_idx, conv_idx);
	parse_data_types(format, data, spec_idx, conv_idx);
	parse_flags(format, data, spec_idx, conv_idx);
	if (data->type[0] == 'l' && data->type[1] == '\0')
		c = (unsigned long)va_arg(data->args[0], unsigned long);
	else
		c = (char)va_arg(data->args[0], int);
	c = (wint_t)c;
	data->precision = -1;
	padding_gate_sc(data, 0, 1);
	write(1, &c, 1);
	data->len++;
	padding_gate_sc(data, 1, 1);
}
