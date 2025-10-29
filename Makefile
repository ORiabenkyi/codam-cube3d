MLX_DIR	= libs/MLX42
MLX_LIB	= $(MLX_DIR)/build/libmlx42.a

LIBFT_DIR = libs/libft
LIBFT_LIB = libs/libft/libft.a

INC		= -I./libs/libft/inc/libft.h -I./inc/cube3d.h

NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
RM		= rm -rf

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
$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(INC) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean all