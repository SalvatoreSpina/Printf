NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CL = rm -rf

HEADER = ft_printf.h ft_printf_bonus.h

SRC =	mandatory/ft_printf.c mandatory/ft_printf_aux.c

SRCB =	*.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

$(NAME): $(OBJ)
	@ar r $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(CL) $(OBJ) $(OBJB)

fclean: clean
	$(CL) $(NAME)
	@rm -rf printfTester

re: fclean all

bonus: fclean $(OBJB)
	@ar r $(NAME) $(OBJB)

tester:
	@git clone https://github.com/Tripouille/printfTester.git

test:
	@cd printfTester && make m
	

