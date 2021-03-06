# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chle-van <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/27 20:46:24 by chle-van          #+#    #+#              #
#    Updated: 2017/10/28 20:39:48 by chle-van         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_PATH=./libft/
CC=gcc
CFLAGS=-Wall -Wextra -Werror 
CLIB=-lmlx
CFRAMWORKS=-framework OpenGL -framework Appkit
SRC=fdf.c\
	main.c\
	events.c\
	draw.c

OBJ=$(SRC:.c=.o)
NAME=fdf
LIB_NAME=libft.a
LIB_FILE=$(LIB_PATH)$(LIB_NAME)
INCLUDES_DIR=$(LIB_PATH)includes/

all:$(NAME)

$(LIB_FILE): 
	cd $(LIB_PATH) && $(MAKE)

$(NAME):$(LIB_FILE) #$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIB) $^ *.c $(CFRAMWORKS) -I$(INCLUDES_DIR)

$(OBJ)%.o: $(SRC)
	$(CC) $(CFLAGS) -c $^ -I $(INCLUDES_DIR)

re:fclean all

clean:
	rm -rf $(OBJ)
	rm -rf $(LIB_FILE) $(LIB)
	cd $(LIB_PATH) && $(MAKE) fclean
fclean:clean
	rm -rf $(NAME)
