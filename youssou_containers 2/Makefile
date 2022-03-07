# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/03 02:50:19 by youssou          #+#    #+#              #
#    Updated: 2021/12/14 09:26:54 by youssou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_test
NAME2=std_test


CC=clang++ -Wall -Wextra -Werror -std=c++98

RM=rm -rf

SRC= mainfinal.cpp

OBJ=$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	@printf $(blue)
	@$(CC) $(OBJ) -o $(NAME)
	@printf "\e[KCompilation done ./$(NAME) is ready to use\n"
	@printf $(reset_char)


%.o : %.cpp
	@printf $(blue)
	@printf "Generating $< object file\e[K\r"
	@$(CC) $(CDEF)  -o $@ -c $?

$(NAME) : CDEF= -D NS=ft
$(NAME2) : CDEF= -D NS=std

all: clean $(NAME)



$(NAME2): $(OBJ)
	@printf $(blue)
	@$(CC)   $(OBJ) -o $(NAME2)
	@printf "\e[KCompilation done ./$(NAME2) is ready to use\n"
	@printf $(reset_char)


std: clean $(NAME2)

speed_vector:
		cd containers_optimisator && clang++ main.cpp && ./a.out "./vector_speed.sh"

speed_map:
		cd containers_optimisator && clang++ main.cpp && ./a.out "./map_speed.sh"

speed_stack:
		cd containers_optimisator && clang++ main.cpp && ./a.out "./stack_speed.sh"

speed_set:
		cd containers_optimisator && clang++ main.cpp && ./a.out "./set_speed.sh"


clean:
	@printf $(green)
	@$(RM) $(OBJ)
	@printf "Cleared object files\n"
	@printf $(reset_char)
	
fclean: clean
	@printf $(green)
	@$(RM) $(NAME) $(NAME2)
	@printf "Cleared executable files\e[K\n"
	@printf $(reset_char)

noflags: clean
	$(CC) $(SRC) -o $(NAME)

re: fclean all

####	C	O	L	O	R	S	####
black 				=	"[1;30m"
red 				=	"[1;31m"
green 				=	"[1;32m"
yellow 				=	"[1;33m"
blue 				=	"[1;34m"
magenta 			=	"[1;35m"
cyan 				=	"[1;36m"
white 				=	"[1;37m"

bg_black 			=	"[40m"
bg_red 				=	"[41m"
bg_green 			=	"[42m"
bg_yellow 			=	"[43m"
bg_blue 			=	"[44m"
bg_magenta 			=	"[45m"
bg_cyan 			=	"[46m"
bg_white 			=	"[47m"

reset_char 				=	"[0m"
####	C	O	L	O	R	S	####
