/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 09:53:43 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 11:21:47 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		save_flags(const char *format, t_data *data,
		int curr_idx, int flag_index)
{
	int i;
	int y;

	i = curr_idx;
	y = flag_index;
	if (format[i] == '0' && format[i - 1] == '%')
		data->flag_index[y] = 1;
	else if (format[i] != '0')
		data->flag_index[y] = 1;
}

static void		treat_zero_flag(t_data *data, int *curr_idx)
{
	data->flag_index[3] = 1;
	*curr_idx += 1;
}

int				parse_width(const char *format, t_data *data,
		int curr_idx, int conv_idx)
{
	int		i;
	int		y;
	char	*spaces;

	y = 0;
	i = 0;
	if (!(spaces = (char *)malloc(sizeof(conv_idx - curr_idx + 1))))
		error_message();
	if (format[curr_idx] == '0')
		treat_zero_flag(data, &curr_idx);
	if (ft_isdigit(format[curr_idx]) == 0)
		return (0);
	i = curr_idx;
	while (format[i] != '\0' && i != conv_idx && (ft_isdigit(format[i]) == 1))
	{
		if (format[i - 1] == '.')
			break ;
		spaces[y++] = format[i++];
	}
	spaces[y] = '\0';
	data->spaces = ft_atoi(spaces);
	free(spaces);
	return (1);
}

void			parse_flags(const char *format, t_data *data,
		int spec_idx, int conv_idx)
{
	int y;
	int i;
	int precision_pointer;

	precision_pointer = 0;
	y = 0;
	if (format[spec_idx - 1] == ' ' && data->conversion != '\0')
		data->flag_index[2] = 1;
	while (data->flags[y] != '\0')
	{
		i = spec_idx;
		while (format[i] != '\0' && i != conv_idx)
		{
			if (format[i] == '.')
				precision_pointer = 1;
			if ((ft_isdigit(format[i]) == 1) && data->spaces == 0
					&& precision_pointer == 0)
				parse_width(format, data, i, conv_idx);
			if (format[i] == data->flags[y])
				save_flags(format, data, i, y);
			i++;
		}
		y++;
	}
}
