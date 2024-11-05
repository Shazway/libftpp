TEST_NAME	=	tester

CPP_FLAGS	=	-Wall -Wextra -Werror -O2 -g3 -std=c++17

OBJ_PATH	=	libftpp/obj/

LIBFTPP_PATH	= libftpp
LIB_NAME		= libftpp.a

CC			=	g++
SRC_PATH	=	srcs/
INCLUDES	=	-Iincludes -Ilibftpp/includes
LPPFLAGS	=	-L$(LIBFTPP_PATH) -lftpp
SRC_NAME	=	main.cpp

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

# Compile tests
all: $(LIBFTPP_PATH)/$(LIB_NAME) $(TEST_NAME)

# Runs Makefile in libftpp folder
$(LIBFTPP_PATH)/$(LIB_NAME):
	@echo "$(CYAN)=====> Compiling libftpp library <===== $(WHITE)"
	$(MAKE) -C $(LIBFTPP_PATH)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

# Compile tester with lib
$(TEST_NAME): $(OBJ) $(LIBFTPP_PATH)/$(LIB_NAME)
	@echo "$(RED)=====>Compiling tester for libftpp<===== $(WHITE)"
	$(CC) $(INCLUDES) $(LPPFLAGS) $(OBJ) -o $(TEST_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(CC) $(CPP_FLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

clean:
	@echo "$(CYAN)♻  Cleaning obj files ♻ $(WHITE)"
	rm -rf $(OBJ_PATH)
	@echo "$(GREEN)Done !✅ $(EOC)"
	@echo "$(CYAN)♻  Cleaning libftpp library obj files ♻ $(WHITE)"
	$(MAKE) -C $(LIBFTPP_PATH) clean
	@echo "$(GREEN)Done !✅ $(EOC)"

fclean: clean
	@echo "$(CYAN)♻  Cleaning tester executable ♻ $(WHITE)"
	rm -rf $(TEST_NAME)
	@echo "$(GREEN)Done !✅ $(EOC)"
	@echo "$(CYAN)♻  Cleaning libftpp library ♻ $(WHITE)"
	$(MAKE) -C $(LIBFTPP_PATH) fclean
	@echo "$(GREEN)Done !✅ $(EOC)"

re: fclean all

.PHONY: all clean fclean re