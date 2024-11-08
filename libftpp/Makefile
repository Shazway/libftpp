LIB_NAME	=	libftpp.a

CPP_FLAGS	=	-Wall -Wextra -Werror -O2 -g3 -std=c++17

OBJ_PATH	=	obj/

CC			=	g++
AR			=	ar rcs
SRC_PATH	=	srcs/
INCLUDES	=	-Iincludes
SRC_NAME	=	data_buffer.cpp

OBJ_NAME	=	$(SRC_NAME:.cpp=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

#----------colors---------#
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
EOC			=	\033[0;0m

all: $(LIB_NAME)

# Compile lib
$(LIB_NAME): $(OBJ)
	@echo "$(RED)=====>Building libftpp<===== $(WHITE)"
	$(AR) $(LIB_NAME) $(OBJ)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(CC) $(CPP_FLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

clean:
	@echo "$(CYAN)♻  Cleaning LIB obj files ♻ $(WHITE)"
	rm -rf $(OBJ_PATH)
	@echo "$(GREEN)Done !✅ $(EOC)"

fclean: clean
	@echo "$(CYAN)♻  Cleaning LIB .a file ♻ $(WHITE)"
	rm -rf $(LIB_NAME)
	@echo "$(GREEN)Done !✅ $(EOC)"

re: fclean all

.PHONY: all clean fclean re
