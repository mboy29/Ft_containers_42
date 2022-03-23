# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboy <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 13:35:38 by mboy              #+#    #+#              #
#    Updated: 2022/03/23 13:35:40 by mboy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT		=	FT
STL		=	STL

FTSRCS		=	./Sources/FT/FtMain.cpp \
				./Sources/FT/FtTestingVector.cpp \
				./Sources/FT/FtTestingStack.cpp \
				./Sources/FT/FtTestingMap.cpp

STLSRCS		= 	./Sources/STL/StlMain.cpp \
				./Sources/STL/StlTestingVector.cpp \
				./Sources/STL/StlTestingStack.cpp \
				./Sources/STL/StlTestingMap.cpp 

CXX			=	c++
RM			=	rm -rf
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
RESET   	=	$'\033[0m
COLOR     	=	$'\033[1;36m

FTOBJS		=	$(FTSRCS:.cpp=.o)
STLOBJS		=	$(STLSRCS:.cpp=.o)

FTOUT 		=	./Output/ft_output
STLOUT 		=	./Output/stl_ouput
DIFFOUT 	=	./Output/diff_output

all: $(FT) $(STL)

%.o:%.c
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(FT): $(FTOBJS)
	@echo "$(COLOR)--> Compiling $(FT)...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $(FT) $(FTOBJS)
	@echo "$(COLOR)--> $(FT) is ready to be used ! $(RESET)"

$(STL): $(STLOBJS)
	@echo "$(COLOR)--> Compiling $(STL)...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $(STL) $(STLOBJS)
	@echo "$(COLOR)--> $(STL) is ready to be used ! $(RESET)"

test: $(FT) $(STL)
	@if ! [ -d "./Output" ]; then \
        mkdir ./Output; \
    fi
	@echo "$(COLOR)--> Excuting and comparing $(FT) and $(STL)... $(RESET)"
	@./$(FT) > $(FTOUT)
	@./$(STL) > $(STLOUT)
	@diff -a $(FTOUT) $(STLOUT) > $(DIFFOUT) || exit 0
	@echo "$(COLOR)--> Outputs in ./Output folder ! $(RESET)"

time: $(FT) $(STL)
	@if ! [ -d "./Output" ]; then \
        mkdir ./Output; \
    fi
	@echo "$(COLOR)--> Excuting and comparing $(FT) and $(STL)... $(RESET)"
	@echo "\n$(COLOR)--> $(FT) time perfomance : $(RESET)"
	@time ./$(FT) > $(FTOUT)
	@echo "\n$(COLOR)--> $(STL) time perfomance : $(RESET)"
	@time ./$(STL) > $(STLOUT)
	@diff -a $(FTOUT) $(STLOUT) > $(DIFFOUT) || exit 0
	@echo "\n$(COLOR)--> Outputs in ./Output folder ! $(RESET)"

clean:
	@echo "$(COLOR)--> Cleaning ...$(RESET)"
	$(RM) $(FTOBJS) $(STLOBJS) 

fclean: clean
	$(RM) $(FT) $(STL) ./Output

re: fclean all

.PHONY: all clean fclean re
