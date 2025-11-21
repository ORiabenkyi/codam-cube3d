MLX_DIR	= libs/MLX42
MLX_LIB	= $(MLX_DIR)/build/libmlx42.a

LIBFT_DIR = libs/libft
LIBFT_LIB = libs/libft/libft.a

INC		= -I./libs/libft/inc/libft.h -I./inc/cube3d.h

NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
RM		= rm -rf

CFILES = 	src/cube3d.c \
			src/utils/utils_file.c \
			src/parser/init_game.c \
			src/parser/is_valid_input.c \
			src/utils/err_wrong_command.c \
			src/utils/err_wrong_file.c \
			src/utils/err_wrong_in_file.c \
			src/utils/err_wrong_alocate.c \
			src/utils/err_wrong_texture.c \
			src/utils/err_wrong_color.c \
			src/utils/err_wrong_map.c \
			src/utils/err_wrong_on_map.c \
			src/utils/prints.c \
			src/parser/feel_game.c \
			src/parser/feel_texture.c \
			src/parser/feel_color.c \
			src/parser/feel_map.c \
			src/parser/count_map.c \
			src/engine/engine.c \

OFILES = $(CFILES:.c=.o)

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME) 

# -----------------------
# take from codam MLX42 repo
# -----------------------
$(MLX_LIB):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) || true
	cmake -B $(MLX_DIR)/build $(MLX_DIR)
	cmake --build $(MLX_DIR)/build -j4

# -----------------------
# Create libft part of the project
# -----------------------	
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)	
# -----------------------
# Create main part of the project
# -----------------------
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(INC) $(LIBFT_LIB) -o $(NAME)

clean:
	$(RM) $(OFILES)
	@make clean -C $(LIBFT_DIR)

mlx: $(MLX_LIB)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

full: fclean all