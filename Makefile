# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 11:02:31 by xortega           #+#    #+#              #
#    Updated: 2024/04/10 10:29:52 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
OBJ_DIR		:=	obj/
SRC_PATH	:=	src/
LIBFT_PATH	:=	libft
RLINE_PATH	:=	readline
LIBFT		:=	libft.a
RLINE		:=	readline.a
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -I./includes
#  -Wno-error=unused-command-line-argument
RLINE_FLAGS	:= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
RLINE		:= -I/Users/$(USER)/.brew/opt/readline/include/

# SRCS #
BUILT-IN 	:= env_mx export_mx unset_mx
ENVP	 	:= envp envp_utils envp_arg
EXPAND	 	:= expand
HISTORY 	:=
MAIN 		:= main
PARSING 	:=
PIPING 		:= parse_commands execute_commands
SIGNALS 	:=

PLAIN_SRCS =	$(addsuffix .c, $(addprefix built-in/,	$(BUILT-IN)))		\
				$(addsuffix .c, $(addprefix envp/,		$(ENVP)))			\
				$(addsuffix .c, $(addprefix expand/,		$(EXPAND)))			\
				$(addsuffix .c, $(addprefix history/,	$(HISTORY)))		\
				$(addsuffix .c, $(addprefix main/,		$(MAIN)))			\
				$(addsuffix .c, $(addprefix parsing/,	$(PARSING)))		\
				$(addsuffix .c, $(addprefix piping/,	$(PIPING)))			\
				$(addsuffix .c, $(addprefix signals/,	$(SIGNALS)))

SRCS := $(addprefix $(SRC_PATH), $(PLAIN_SRCS))
OBJS := $(addprefix $(OBJ_DIR), $(PLAIN_SRCS:.c=.o))


# ASCII COLORS #
BLACK=\033[0;30m
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAG=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
PAPYRUS=\033[38;5;223m
END=\033[0m


all: $(NAME)

define ASCII
$(WHITE)
                                                ██████       
                                              ██    ██      
                                          ████░░░░██        
                                      ████    ██████                 :::   :::   ::::::::::: ::::    ::: :::::::::::      
                                    ██░░░░        ██               :+:+: :+:+:      :+:     :+:+:   :+:     :+:           
                                ██████████░░░░    ██             +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+            
                              ██░░        ████░░  ██            +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+             
$(GREEN)                        ████  ████$(WHITE)░░          ██░░██           +#+       +#+     +#+     +#+  +#+#+#     +#+              
$(GREEN)                      ██    ██    ██$(WHITE)░░░░        ██            #+#       #+#     #+#     #+#   #+#+#     #+#               
$(GREEN)                      ██  ██████  ██$(WHITE)████░░      ██           ###       ### ########### ###    #### ###########            
$(GREEN)                        ████$(RED)▒▒$(GREEN)████$(RED)▒▒▒▒▒▒$(WHITE)██░░░░░░██$(RED)                        ::::::::  :::    ::: :::::::::: :::        :::  
                      ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████████                  :+:    :+: :+:    :+: :+:        :+:        :+:   
              ████████▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██               +:+        +:+    +:+ +:+        +:+        +:+    
          ████▒▒▒▒▒▒▒▒██▒▒████████▒▒▒▒██▒▒██████████▒▒▒▒██            +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+     
        ██▒▒▒▒▒▒██████▒▒██▒▒▒▒▒▒▒▒▒▒██  ██▒▒██    ████▒▒██                  +#+ +#+    +#+ +#+        +#+        +#+      
        ██▒▒▒▒▒▒██████▒▒██▒▒▒▒▒▒▒▒▒▒██  ██▒▒██    ████▒▒██          #+#    #+# #+#    #+# #+#        #+#        #+#       
      ██▒▒▒▒██▒▒██  ██▒▒████████████      ██▒▒██    ██▒▒██          ########  ###    ### ########## ########## ########## 
      ██▒▒▒▒████    ██▒▒██                ██▒▒██    ████    
        ████          ██                  ████              

endef                                                                                                                                                                                                                                                                                          
export ASCII

$(NAME): $(OBJS) $(LIBFT)
	@sleep 0.2;
	@$(CC) $(CFLAGS) $(RLINE_FLAGS) $(RLINE) $(OBJS) $(LIBFT) -o $(NAME)
#@printf "$(RED)"
	@echo "$$ASCII"
	@printf "\033[0;32;3mMINISHELL ✅\n\n"

$(OBJ_DIR)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(READLINE) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@mv $(LIBFT_PATH)/$(LIBFT) ./

clean:
	@rm -fr $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

ascii:
	@echo "$$ASCII"

fclean:
	@rm -fr $(OBJ_DIR)
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@make fclean -C $(LIBFT_PATH)
	
re: fclean all

.PHONY: all clean fclean re