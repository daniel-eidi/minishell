# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 23:31:06 by daeidi-h          #+#    #+#              #
#    Updated: 2022/08/19 01:34:42 by daeidi-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS    = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
            ft_toupper.c ft_tolower.c ft_strlen.c  ft_strlcpy.c ft_strnstr.c \
            ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcat.c \
            ft_bzero.c ft_memset.c ft_memchr.c ft_memcpy.c ft_memmove.c \
            ft_memcmp.c \
            ft_atoi.c \
            ft_calloc.c ft_strdup.c \
            ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
            ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
            ft_putendl_fd.c ft_putnbr_fd.c ft_countword.c get_next_line.c\
			ft_atoi_base.c\
			ft_printf.c\
			printf_utils.c\
			ft_putchar.c\
			ft_issign.c\
			

OBJS = $(SRCS:.c=.o)

NAME = libft.a

#MAIN = main.c

#OBJ_MAIN = $(MAIN:.c=.o)

#TEST = test

CC = cc
RM = rm -f
CCLIB = ar rcs

CFLAGS = -Wall -Wextra -Werror

#LFLAGS = -L. -lft

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CCLIB) $(NAME) $(OBJS)

all: $(NAME)

# main: $(OBJS) $(OBJ_MAIN)
# 	$(CC) $(CFLAGS) -o $(TEST) $(OBJ_MAIN) $(LFLAGS) -lbsd
# 	./$(TEST)

clean:
	$(RM) $(OBJS) $(OBJ_MAIN)

fclean: clean
	$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re run main