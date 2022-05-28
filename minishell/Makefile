NAME = minishell

HEADER = minishell.h

CC = cc

INCLUDES = minishell.h


SRC =	minishell.c					\
		ft_strtrim.c				\
		ft_strjoin.c				\
		parser/ft_check_arg.c		\
		parser/get_varb.c 			\
		parser/ft_split.c	 		\
		parser/ft_atoi.c	 		\
		parser/ft_split_2.c	 		\
		commends/echo.c 			\
		commends/pip.c				\
		commends/cd.c				\
		commends/export.c			\
		commends/unset.c			\
		ft_strdup.c					\

OBJECTS = $(SRC:.c=.o)
OBJECTSB = $(SRCB:.c=.o)

all: $(NAME)
	@echo "------------------minishell-----------------\n\n\n"
# -L /goinfre/zait-sli/.brew/opt/readline/lib I/goinfre/zait-sli/.brew/opt/readline/include
$(NAME): $(OBJECTS)
	@$(CC) -lreadline  $(OBJECTS) -o $(NAME)

%.o : %.c $(INCLUDES)
	@$(CC) -o $@ -c $<
clean:
	@rm -rf $(OBJECTS) $(OBJECTSB) 

fclean: clean
	@rm -rf $(NAME) $(NAME2)

re: fclean all