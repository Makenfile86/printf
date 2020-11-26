/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 09:42:54 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/03 09:44:04 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	re_init(t_data *data)
{
	data->flag_index[0] = '\0';
	data->flag_index[1] = '\0';
	data->flag_index[2] = '\0';
	data->flag_index[3] = '\0';
	data->flag_index[4] = '\0';
	data->conversion = '\0';
	data->spaces = 0;
	data->precision = -1;
	free(data->type);
	data->type = ft_strdup("\0\0");
	data->int_neg = 0;
	data->udf = 0;
}

void	init(t_data *data)
{
	data->conversions = "cspdiouxXf";
	data->flags = "-+ 0#";
	data->flag_index[0] = '\0';
	data->flag_index[1] = '\0';
	data->flag_index[2] = '\0';
	data->flag_index[3] = '\0';
	data->flag_index[4] = '\0';
	data->conversion = '\0';
	data->spaces = 0;
	data->precision = -1;
	data->type = ft_strdup("\0\0");
	data->len = 0;
	data->int_neg = 0;
	data->udf = 0;
}
