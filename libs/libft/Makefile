# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 13:59:55 by oriabenk          #+#    #+#              #
#    Updated: 2024/10/11 14:31:20 by oriabenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILE = 	cc

FLAGS = 	-Wall -Werror -Wextra

CFILES = 	main/ft_atoi.c \
			main/ft_bzero.c \
			main/ft_calloc.c \
			main/ft_isalpha.c\
			main/ft_isdigit.c \
			main/ft_isalnum.c \
			main/ft_isascii.c \
			main/ft_isprint.c \
			main/ft_itoa.c \
			main/ft_memchr.c \
			main/ft_memcmp.c \
			main/ft_memcpy.c \
			main/ft_memmove.c \
			main/ft_memset.c \
			main/ft_putchar_fd.c \
			main/ft_putendl_fd.c \
			main/ft_putnbr_fd.c \
			main/ft_putstr_fd.c \
			main/ft_split.c \
			main/ft_strchr.c \
			main/ft_strdup.c \
			main/ft_striteri.c \
			main/ft_strjoin.c \
			main/ft_strlcat.c \
			main/ft_strlcpy.c \
			main/ft_strlen.c \
			main/ft_strmapi.c \
			main/ft_strncmp.c \
			main/ft_strnstr.c \
			main/ft_strrchr.c \
			main/ft_strtrim.c \
			main/ft_substr.c \
			main/ft_tolower.c \
			main/ft_toupper.c  \
			printf/ft_printf.c \
			printf/ft_print.c \
			getNextLine/get_next_line.c \

			
CBONUS =	list/ft_lstnew_bonus.c \
			list/ft_lstadd_front_bonus.c \
			list/ft_lstsize_bonus.c \
			list/ft_lstlast_bonus.c \
			list/ft_lstadd_back_bonus.c \
			list/ft_lstdelone_bonus.c \
			list/ft_lstclear_bonus.c \
			list/ft_lstiter_bonus.c \
			list/ft_lstmap_bonus.c 

OFILES = $(CFILES:.c=.o)

OFILES_BONUS = $(CBONUS:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OFILES)
	@ar rcs $@ $^

%.o: %.c libft.h
	@$(COMPILE) -c $(FLAGS) -o $@ $<

clean:
	@$(RM) $(OFILES) $(OFILES_BONUS)

fclean: clean
	@$(RM) $(NAME)

bonus: $(OFILES) $(OFILES_BONUS)
	@ar rc $(NAME) $(OFILES) $(OFILES_BONUS)

re: fclean all
