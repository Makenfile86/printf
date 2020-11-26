/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 10:02:05 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 10:13:25 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	parse_conversions_str(t_data *data, const char *s1, char *s2, int i)
{
	int y;

	while (s1[i] != '\0' && s1[i] != '%')
	{
		y = 0;
		while (s2[y] != '\0')
		{
			if (s1[i] == s2[y])
			{
				data->conversion = data->conversions[y];
				return (i);
			}
			y++;
		}
		i++;
	}
	return (-1);
}

static int	parse_validity(const char *format, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
	{
		if (ft_isdigit(format[start]) == 0)
		{
			if (format[start] != 'l' && format[start] != 'h' &&
					format[start] != 'L' && format[start] != 'z'
					&& format[start] != 'j')
			{
				if (format[start] != '-' && format[start] != '+'
						&& format[start] != ' ' && format[start] != '#'
						&& format[start] != '.' && format[start] != '*')
					return (0);
			}
		}
		start++;
	}
	return (1);
}

int			parse_data_types(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	int i;
	int y;

	y = 0;
	i = conv_idx;
	while (i != spec_idx)
	{
		i--;
		if (format[i] == 'l' || format[i] == 'h' || format[i] == 'L'
				|| format[i] == 'z' || format[i] == 'j')
		{
			while (y < 2 && (format[i] == 'l' || format[i] == 'h' ||
						format[i] == 'L' || format[i] == 'z'
						|| format[i] == 'j'))
			{
				data->type[y] = format[i];
				y++;
				i--;
			}
			data->type[y] = '\0';
			return (1);
		}
	}
	return (0);
}

int			match_conversion(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	if (data->conversion == 's')
		conversion_s(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'c')
		conversion_c(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'd' || data->conversion == 'i'
			|| data->conversion == 'D')
		conversion_d(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'p')
		conversion_p(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'u')
		conversion_u(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'o' || data->conversion == 'O')
		conversion_o(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'x' || data->conversion == 'X')
		conversion_x(format, data, spec_idx, conv_idx);
	else if (data->conversion == 'f')
	{
		parse_data_types(format, data, spec_idx, conv_idx);
		if (data->type[0] == 'L' && data->type[1] == '\0')
			conversion_lf(format, data, spec_idx, conv_idx);
		else
			conversion_f(format, data, spec_idx, conv_idx);
	}
	re_init(data);
	return (conv_idx);
}

int			parse_data(t_data *data)
{
	size_t	i;
	int		y;
	size_t	len;

	i = 0;
	len = ft_strlen(data->format);
	while (i < len)
	{
		if (data->format[i] == '%' && data->format[i + 1] != '\0')
		{
			i++;
			y = parse_conversions_str(data, data->format, data->conversions, i);
			if (y != -1 && (parse_validity(data->format, i, y) == 1))
				i = match_conversion(data->format, data, i, y);
			else
				i = conversion_none(data->format, data, i);
		}
		else if (data->format[i] == '%' && data->format[i + 1] == '\0')
			return (0);
		else
			print_char(data, data->format[i]);
		i++;
	}
	return (0);
}
