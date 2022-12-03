SRCS = 	src/ft_printf.c src/print_c.c src/print_s.c src/print_p.c src/print_x.c src/print_diu.c src/print_helps.c src/flags_aux.c

NAME  = libftprintf.a

CC    = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS  = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar crs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

tester:
	@git clone https://github.com/Tripouille/printfTester.git 2> /dev/null || true

test:
	@make fclean 2> /dev/null
	@make tester 2> /dev/null
	@cd printfTester && make m

testb:
	@make fclean 2> /dev/null
	@make tester 2> /dev/null
	@cd printfTester && make b
	
norm:
	@norminette src/
