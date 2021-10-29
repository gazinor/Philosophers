# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 23:18:36 by glaurent          #+#    #+#              #
#    Updated: 2021/09/21 08:10:15 by glaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # ============================================================================ #
# #                                   COLORS                                     #
# # ============================================================================ #

CL_BOLD 		= \e[1m
CL_DIM			= \e[2m
CL_UDLINE 		= \e[4m

NO_COLOR 		= \e[0m

BG_TEXT 		= \e[48;2;45;55;72m
BG_BLACK 		= \e[48;2;30;31;33m

FG_WHITE 		= $(NO_COLOR)\e[0;37m
FG_TEXT 		= $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF 				= \e[1K\r$(NO_COLOR)
CRLF			= \n$(LF)

######################################
#              COMMANDS              #
######################################
CC		=	clang -c -o
LINK	=	clang -o
MKDIR	=	mkdir -p
RM		=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME	=	philo

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR	=	srcs/
OBJ_DIR	=	.objs/
PRV_DIR	=	includes/

######################################
#            SOURCE FILES            #
######################################
SRC		=	\
			${addprefix ctx/,					\
				phi_ctx_get.c					\
				phi_ctx_init.c					\
				phi_ctx_print.c					\
			}									\
			${addprefix philo/,					\
				phi_philo_born.c				\
				phi_philo_eat.c					\
				phi_philo_init.c				\
				phi_philo_sleep.c				\
				phi_philo_state_msg.c			\
				phi_philo_think.c				\
				phi_philo_wait.c				\
				phi_routine.c					\
				phi_run.c						\
			}									\
			${addprefix utils/,					\
				phi_atol.c						\
				phi_is_digit.c					\
				phi_is_space.c					\
				phi_lintlen.c					\
				phi_memdel.c					\
				phi_strcmp.c					\
				phi_now.c						\
			}									\
			${addprefix voice/,					\
				phi_voice_get.c					\
			}									\
			${addprefix parsing/,				\
				phi_err_msg.c					\
				phi_format_check.c				\
				phi_limits_check.c				\
			}									\
			main.c

######################################
#            OBJECT FILES            #
######################################
OBJ		=	${SRC:.c=.o}
OBJ		:=	${addprefix ${OBJ_DIR}, ${OBJ}}

DEP		=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CFLAGS	=	-Wall -Wextra -Werror
CFLAGS	+=	-MMD -MP
CFLAGS	+=	-I${PRV_DIR}

LDFLAGS	=	-lpthread

ifeq (${DEBUG}, 1)
	CFLAGS	+=	-g
endif

#######################################
#                RULES                #
#######################################
${NAME}:	${OBJ}
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@${LINK} $@ $^ ${LDFLAGS}
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"

all:	${NAME}

-include ${DEP}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@${MKDIR} ${@D}
	@${CC} $@ ${CFLAGS} $<
	@printf "$(LF)🚧 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

save : fclean
	git add .
	git commit -m "$m"
	git push

clean:
	@${RM} ${OBJ_DIR}
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

fclean:
	@${RM} ${OBJ_DIR} ${NAME}

re:	fclean all

norm:
	@norminette ${SRC_DIR} ${PRV_DIR} | grep 'Error' ; true

.PHONY:	all clean fclean re coffee norm
