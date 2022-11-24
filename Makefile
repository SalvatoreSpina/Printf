NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CL = rm -rf

SRC =	mandatory/ft_printf.c

SRCB =	*.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

$(NAME): $(OBJ)
	@ar r $(NAME) $(OBJ)

all: $(NAME)

clean:
	@$(CL) $(OBJ) $(OBJB)

fclean: clean
	@$(CL) $(NAME)
	@rm -rf printfTester

re: fclean all

bonus: fclean $(OBJB)
	@ar r $(NAME) $(OBJB)

tester:
	@git clone https://github.com/Tripouille/printfTester.git 2> /dev/null || true

test:
	@make tester 2> /dev/null
	@cd printfTester && make m
	
norm:
	@norminette mandatory/