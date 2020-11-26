/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 09:41:15 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 09:42:35 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int		result;
	t_data	*data;

	data = NULL;
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		error_message();
	data->format = format;
	init(data);
	if (format)
	{
		va_start(data->args[0], format);
		result = parse_data(data);
		va_end(data->args[0]);
	}
	result = data->len;
	free(data->type);
	free(data);
	return (result);
}
