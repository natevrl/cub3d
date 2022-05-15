SRCS =	src/main.c \
		libs/get_next_line/get_next_line.c\
		libs/get_next_line/get_next_line_utils.c\
		src/initialisations.c \
		src/kill.c \
		src/map_parsing.c \
		src/map_error.c \
		src/map_put_tiles.c \
		src/draw_map.c \
		src/moove_detection.c \
		src/utils.c \
		src/error.c \
		src/player_moove.c \
		src/raycasting.c \
		src/init_textures.c \
		src/projections.c



OBJS		= $(SRCS:.c=.o)
LIBFT		= libs/libft/libft.a
#MINILIBX	= minilibx-linux/obj/*.o
MINILIBX2	= -L ./libs/minilibx-linux/


CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
NAME		= cub3D

all : $(NAME)

# Pour MacOS
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

#Pour Linux
%.o: %.c
	$(CC) ${CFLAGS} -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	make -C libs/libft/
	$(CC) $(OBJS) -I ./game -o $(NAME) ${LIBFT} ${MINILIBX2} -lmlx -lXext -lX11 -lm
	#$(CC) $(OBJS) -Imlx_linux -o $(NAME) ${MINILIBX} ${LIBFT} ${MINILIBX2} -lXext -lX11 -lmlx -lm -lz 


clean : 
	rm -f $(OBJS)
	make fclean -C libs/libft/

fclean : clean
	rm -f $(NAME)

re : fclean all
