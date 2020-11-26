# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/22 11:25:20 by mkivipur          #+#    #+#              #
#    Updated: 2020/07/22 11:32:05 by mkivipur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a
LIBFT_A =	libft.a

COMP =		gcc -Wall -Werror -Wextra $(PRINTF_H) $(LIBFT_H) -c -o

PRINTF_H =	-I ./includes/
LIBFT_H = 	-I ./libft/

OBJ_DIR =	obj/
SRC_DIR =	srcs/
LIB_DIR =	./libft/

CFILE =		ft_printf.c \
			init.c \
			parse_prec_argptr.c \
			write.c \
			utils.c \
			conversion_none.c \
			conversion_cs.c \
			conversion_d.c \
			conversion_x.c \
			conversion_u.c \
			conversion_o.c \
			conversion_f.c \
			conversion_lf.c \
			conversion_p.c \
			universal_padding_rules.c \
			padding.c \
			parse_format.c \
			parse_flags_width.c \
			error_message.c \
			itoa_base.c \
			utils_f.c \

CFIND =		$(CFILE:%=$(SRC_DIR)%)

OFILE =		$(CFILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(OFILE))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)
		

$(NAME): $(OBJ)
		
		make -C $(LIB_DIR)
		cp $(LIB_DIR)$(LIBFT_A) .
		mv $(LIBFT_A) $(NAME)
		ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OFILE))
		ranlib $(NAME)
	

$(OBJ): $(CFIND)
		$(MAKE) $(OFILE)

$(OFILE):
	
		$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
		/bin/rm -rf $(OBJ_DIR)
		make -C $(LIB_DIR) clean
		

fclean: clean
		/bin/rm -f $(NAME)
		make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean flcean re