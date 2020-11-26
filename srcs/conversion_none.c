/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:40:40 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/01 11:46:20 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	search_conversion(t_data *data, char c, char *s2)
{
	int i;

	i = 0;
	while (s2[i] != '\0')
	{
		if (c == s2[i])
		{
			data->conversion = s2[i];
			return (1);
		}
		i++;
	}
	return (0);
}

static int	print_conv_none(const char *format, t_data *data,
		int spec_idx, int end)
{
	int len;

	len = 0;
	if (format[end] == '%')
		len = 1;
	if (format[end] == '\0')
		end -= 1;
	parse_flags(format, data, spec_idx, end);
	if (data->spaces > 0)
	{
		if (data->flag_index[0] == 1 && format[end] == '%')
			print_char(data, '%');
	}
	padding_gate_sc(data, 0, len);
	padding_gate_sc(data, 1, len);
	if (format[end] == '%' && (data->flag_index[0] == 0 ||
				(data->flag_index[0] == 1 && data->spaces == 0))
			&& data->udf == 0)
		print_char(data, '%');
	return (end);
}

int			conversion_none(const char *format, t_data *data, int start)
{
	int end;
	int len;

	len = 0;
	if (format[start] == '%')
	{
		print_char(data, '%');
		return (start);
	}
	end = print_scattered_chars(format, data, start, &len);
	if (format[end] == '%' && search_conversion(data, format[end + 1],
				data->conversions) == 1)
	{
		match_conversion(format, data, start, end);
		return (end + 1);
	}
	end = print_conv_none(format, data, start, end);
	return (end);
}
