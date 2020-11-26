/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prec_argptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:03:56 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 11:20:38 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	search_arg_ptr(t_data *data, const char *format, int i)
{
	if (format[i] == '*')
	{
		data->precision = va_arg(data->args[0], int);
		if (data->precision < 0)
			data->precision = -1;
		return (1);
	}
	else
		return (0);
}

void		parse_arg_ptr(const char *format, t_data *data,
		int start, int end)
{
	int i;
	int y;

	y = 0;
	i = start;
	while (i != end)
	{
		if (format[i] == '*')
		{
			if (format[i - 1] == '.')
				break ;
			data->spaces = va_arg(data->args[0], int);
			if (data->spaces < 0)
			{
				data->spaces *= -1;
				data->flag_index[0] = 1;
			}
		}
		i++;
	}
}

void		parse_precision(const char *format, t_data *data,
		int start, int end)
{
	int		i;
	char	*temp_precision;
	int		y;

	y = 0;
	i = end;
	if (!(temp_precision = (char *)malloc(sizeof(end - start + 1))))
		error_message();
	while (format[i] != '%')
	{
		if (format[i] == '.')
		{
			if (search_arg_ptr(data, format, i + 1) == 1)
				break ;
			i++;
			while (i != end && (format[i] >= '0' && format[i] <= '9'))
				temp_precision[y++] = format[i++];
			temp_precision[y] = '\0';
			data->precision = ft_atoi(temp_precision);
			break ;
		}
		i--;
	}
	free(temp_precision);
}
