SHELL = /bin/sh

C_D = $(shell pwd)

CFLAGS := ${CFLAGS}

CC     ?= gcc
LD     ?= gcc

INC_FLAGS := -Ilibs/libft/incs
LIBS := -Llibs/libft -lft 

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
else
	NPROC := $(shell sysctl -n hw.ncpu)
endif

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory

NAME ?= woody_woodpacker

BUILD_DIR ?= ./build
SRC_DIRS ?= ./srcs

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := ./incs
#INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

LIB    := libs/libft/libft.a

CFLAGS += -Wall -Wextra -Werror
#CFLAGS += -O2 -march=native
CFLAGS += -g3 -fsanitize=address

all: simple
	@$(MAKE) -j$(NPROC) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

$(LIB):
	@$(MAKE) -C libs/libft
	@echo Libft done

simple:
	@$(CC) ./srcs/prog.cc -o simple

docker:
	docker build -t arch .
	docker run -it --name archwoody -v $(C_D):/woody arch

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C libs/libft clean
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C libs/libft fclean
	@echo Fclean done

prune:
	docker system prune -a --volumes

re: fclean
	@$(MAKE) -j$(NPROC) $(NAME)

.PHONY: all clean fclean re
