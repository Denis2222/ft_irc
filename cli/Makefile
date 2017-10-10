SRCS = main.c \
	connect.c \
	cmd.c \
	io_read.c \
	io_write.c \
	main_loop.c \
	prompt.c \
	prompt2.c \
	t_msg.c \
	view.c \
	msghelp.c

NAME = client
GCC_FLAGS = -Wall -Werror -Wextra -g
CC = clang $(GCC_FLAGS)
SRCDIR = ./
OBJDIR = ./objs
AR = ar -cq
RM = rm -rf
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)
	@echo $(SRC_LIB_O)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) -lft -L../libft/ -lncurses

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $^ -I../libft/

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all
