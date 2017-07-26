SRCS = client.c connect.c

NAME = client
GCC_FLAGS = -Wall -Werror
CC = gcc $(GCC_FLAGS)
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
	$(CC) -o $(NAME) $(OBJS) -lft -L../libft/

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $^ -I../libft/

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all
