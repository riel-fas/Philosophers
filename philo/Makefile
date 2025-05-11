# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m # No Color

NAME			=	philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=thread

SRCS			=	philo_main.c \
					philo_plus.c \
					philo_parsing.c \
					philo_action.c \
					philo_routine.c \
					philo_monitor.c

OBJS			=	${SRCS:.c=.o}

HEADER			=	philosophers.h


all	:	banner $(NAME)

banner:
	@echo "$(CYAN) (       ) (   (       )  (       )  (       )     (    (    $(NC)"
	@echo "$(CYAN) )\\ ) ( /( )\\ ))\\ ) ( /(  )\\ ) ( /(  )\\ ) ( /(     )\\ ) )\\ ) $(NC)"
	@echo "$(CYAN)(()/( )\\()|()/(()/( )\\())(()/( )\\())(()/( )\\())(  (()/((()/( $(NC)"
	@echo "$(CYAN) /(_)|(_)\\ /(_))(_)|(_)\\  /(_)|(_)\\  /(_)|(_)\\ )\\  /(_))/(_))$(NC)"
	@echo "$(CYAN)(_))  _((_|_))(_))   ((_)(_))   ((_)(_))  _((_|(_)(_)) (_))  $(NC)"
	@echo "$(CYAN)| _ \\| || |_ _| |   / _ \\/ __| / _ \\| _ \\| || | __| _ \\/ __| $(NC)"
	@echo "$(CYAN)|  _/| __ || || |__| (_) \\__ \\| (_) |  _/| __ | _||   /\\__ \\ $(NC)"
	@echo "$(CYAN)|_|  |_||_|___|____|\\___/|___/ \\___/|_|  |_||_|___|_|_\\|___/ $(NC)"
	@echo ""
	@echo "$(YELLOW)Date: 2025-04-29 10:30:13 (UTC) - User: riel-fas$(NC)"
	@echo ""

$(NAME)	:	$(OBJS)
	@echo "$(GREEN)Linking objects to create $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled!$(NC)"

%.o : %.c	$(HEADER)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean	:
	@echo "$(YELLOW)Removing object files...$(NC)"
	@rm -rf $(OBJS)

fclean	:	clean
	@echo "$(YELLOW)Removing executable...$(NC)"
	@rm -rf $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re banner
