/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:58:46 by mkivipur          #+#    #+#             */
/*   Updated: 2020/09/01 12:02:36 by mkivipur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	set_rules_p(t_data *data, int num_len)
{
	int added_len;

	added_len = 0;
	data->flag_index[1] = 0;
	data->flag_index[2] = 0;
	data->int_neg = -1;
	if (data->precision >= data->spaces ||
			data->spaces <= (num_len + 2))
		data->spaces = 0;
	if (data->flag_index[0] == 1)
		data->flag_index[3] = 0;
	if (data->precision - num_len >= 0 && num_len != 0)
	{
		if (data->precision + 2 > data->spaces)
			data->spaces += (data->precision - num_len);
	}
	else
		added_len = 2;
	if (data->flag_index[2] == 1 && data->int_neg != 1)
	{
		print_char(data, ' ');
		data->spaces--;
		data->flag_index[2] = 0;
	}
	return (added_len);
}

void		conversion_p(const char *format, t_data *data,
		int spec_index, int conv_index)
{
	uintmax_t	nbr;
	char		*str;
	int			num_len;

	parse_arg_ptr(format, data, spec_index, conv_index);
	parse_precision(format, data, spec_index, conv_index);
	parse_flags(format, data, spec_index, conv_index);
	nbr = (unsigned long)(va_arg(data->args[0], unsigned long int));
	nbr = (uintmax_t)nbr;
	str = ft_itoa_base(nbr, 16, 'a');
	if (nbr == 0 && data->precision == 0)
		num_len = 0;
	else
		num_len = ft_strlen(str);
	padding_preprint(data, num_len + (set_rules_p(data, num_len)));
	if (nbr != 0 || data->precision != 0)
		ft_putstr(str);
	num_len += 2;
	if (data->precision - num_len > 0 && data->spaces > 0)
		data->spaces -= (data->precision - num_len);
	padding_postprint(data, num_len);
	free(str);
	data->len += (num_len -= 2);
}
