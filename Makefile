# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 11:02:31 by xortega           #+#    #+#              #
#    Updated: 2024/05/22 17:04:09 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
OBJ_DIR		:=	obj/
SRC_PATH	:=	src/
LIBFT_PATH	:=	libft
RLINE_PATH	:=	readline
LIBFT		:=	libft.a
#READLINE	:=	/usr/lib/x86_64-linux-gnu/libreadline.so
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes
RLINE_FLAGS	:= -I/usr/include/readline -lreadline #-L/Users/$(USER)/.brew/opt/readline/lib/

# SRCS #
BUILT-IN 	:= env_mx export_mx unset_mx cd_mx pwd_mx echo_mx
ENVP	 	:= envp envp_utils envp_arg
EXPAND	 	:= expand
HISTORY 	:=
MAIN		:= #main
PARSING 	:= parsing token cleaning
PIPING 		:= #parse_commands execute_commands path built-in change_envp
SIGNALS 	:=
UTILS		:= free error strings



PLAIN_SRCS =	$(addsuffix .c, $(addprefix built-in/,	$(BUILT-IN)))		\
				$(addsuffix .c, $(addprefix envp/,		$(ENVP)))			\
				$(addsuffix .c, $(addprefix expand/,	$(EXPAND)))			\
				$(addsuffix .c, $(addprefix history/,	$(HISTORY)))		\
				$(addsuffix .c, $(addprefix main/,		$(MAIN)))			\
				$(addsuffix .c, $(addprefix parsing/,	$(PARSING)))		\
				$(addsuffix .c, $(addprefix piping/,	$(PIPING)))			\
				$(addsuffix .c, $(addprefix signals/,	$(SIGNALS)))		\
				$(addsuffix .c, $(addprefix utils/,		$(UTILS)))

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
	@$(CC) $(CFLAGS) $(RLINE) $(OBJS) $(LIBFT) $(RLINE_FLAGS) -o $(NAME)
#@printf "$(RED)"
	@echo "$$ASCII"
	@printf "\033[0;32;3mMINISHELL ✅\n\n"

ifeq ($(USER), $(filter $(USER), xortega))
	@osascript -e "set Volume 4"
	@say --voice="Diego" Hola amigos de Gutube, en este video de Jutube, aprenderemos a hacer la minishell, yo no la descargo que ya la tengo .
endif

$(OBJ_DIR)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(RLINE_FLAGS) $(INCLUDES) -c $< -o $@

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