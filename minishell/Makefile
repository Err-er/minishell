NAME = minishell

HEADER = minishell.h

CC = cc

INCLUDES = minishell.h

INCLUDES2 = parser/parser.h

RLFLAGS = -I//goinfre/zait-sli/.brew/opt/readline/include

RLFLAGS2 = -L//goinfre/zait-sli/.brew/opt/readline/lib

SRC =	minishell.c						\
		minishell_utils.c				\
		minishell_utils1.c 				\
		ft_strtrim.c					\
		ft_strjoin.c					\
		parser/ft_check_arg.c			\
		parser/get_varb.c 				\
		parser/ft_split.c	 			\
		parser/ft_atoi.c	 			\
		parser/ft_split_2.c	 			\
		parser/ft_tokinaizer.c  		\
		parser/ft_check_arg_utils1.c   	\
		parser/ft_check_arg_utils2.c   	\
		parser/ft_check_arg_utils3.c   	\
		parser/ft_check_arg_utils4.c   	\
		parser/ft_check_arg_utils5.c   	\
		parser/ft_check_arg_utils6.c   	\
		parser/ft_check_arg_utils7.c   	\
		parser/ft_check_arg_utils8.c   	\
		parser/ft_tokinaizer_utils.c    \
		parser/ft_utils_here_doc.c	    \
		commends/echo_utils.c   		\
		commends/echo.c 				\
		commends/pip.c					\
		commends/cd.c					\
		commends/cd_utils.c				\
		commends/cd_utils1.c			\
		commends/export.c				\
		commends/export_utils.c			\
		commends/export_utils1.c		\
		commends/export_utils2.c		\
		commends/export_utils3.c		\
		commends/unset.c				\
		commends/env.c 					\
		commends/exit.c 				\
		ft_strdup.c						\
		ft_itoa.c						\
		syntax/check_syntax.c 			\
		syntax/syntax_utils.c 			\
		commends/pip_utils.c			\
		commends/pip_utils1.c			\
		commends/pip_utils3.c			\
		commends/pip_utils4.c			\
		commends/pip_utils2.c			\

OBJECTS = $(SRC:.c=.o)
OBJECTSB = $(SRCB:.c=.o)

all: $(NAME)
	@echo "------------------minishell-----------------\n\n\n"

$(NAME): $(OBJECTS)
	@$(CC) -Wall -Wextra -Werror -lreadline $(SRC) -o $(NAME) $(RLFLAGS) $(RLFLAGS2) -g

%.o : %.c $(INCLUDES) $(INCLUDES2)
	$(CC) -Wall -Wextra -Werror $(RLFLAGS) -o $@ -c $<
clean:
	@rm -rf $(OBJECTS) $(OBJECTSB) 

fclean: clean
	@rm -rf $(NAME) $(NAME2)

re: fclean all
