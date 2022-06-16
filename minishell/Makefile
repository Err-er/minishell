NAME = minishell

HEADER = minishell.h

CC = cc

INCLUDES = minishell.h

# RLFLAGS = -I/goinfre/zait-sli/.brew/opt/readline/include

# RLFLAGS2 = -L/goinfre/zait-sli/.brew/opt/readline/lib

RLFLAGS = -I/goinfre/asabbar/.brew/opt/readline/include

RLFLAGS2 = -L/goinfre/asabbar/.brew/opt/readline/lib

SRC =	minishell.c						\
		ft_strtrim.c					\
		ft_strjoin.c					\
		parser/ft_check_arg.c			\
		parser/get_varb.c 				\
		parser/ft_split.c	 			\
		parser/ft_atoi.c	 			\
		parser/ft_split_2.c	 			\
		parser/ft_tokinaizer.c  		\
		parser/ft_tokinaizer_utils.c    \
		commends/echo.c 				\
		commends/pip.c					\
		commends/cd.c					\
		commends/export.c				\
		commends/unset.c				\
		commends/env.c 					\
		commends/exit.c 				\
		ft_strdup.c						\
		ft_itoa.c						\
		syntax/check_syntax.c 			\
		syntax/syntax_utils.c 			\

OBJECTS = $(SRC:.c=.o)
OBJECTSB = $(SRCB:.c=.o)

all: $(NAME)
	@echo "------------------minishell-----------------\n\n\n"

$(NAME): $(OBJECTS)
	@$(CC) -lreadline $(SRC) -o $(NAME) $(RLFLAGS) $(RLFLAGS2) 

%.o : %.c $(INCLUDES)
	@$(CC) $(RLFLAGS) -o $@ -c $<
clean:
	@rm -rf $(OBJECTS) $(OBJECTSB) 

fclean: clean
	@rm -rf $(NAME) $(NAME2)

re: fclean all
