NAME = cub3d
INCLUDES = includes/cub3d.h
SRCS	=	events/keys.c \
			events/move.c \
			events/rotate.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			bitmap/make_bmp.c \
			parser/map_validator.c \
			parser/map.c \
			parser/parser_utils.c \
			parser/parser_utils1.c \
			parser/parser_utils2.c \
			parser/parser.c \
			raycast/floor.c \
			raycast/image.c \
			raycast/raycast.c \
			raycast/raycast_utils.c \
			raycast/sprite.c \
			raycast/textures.c \
			raycast/wall.c \
			./errors.c \
			./init_and_free.c \
			./main.c \

FLAGS	=	-Wall -Wextra -Werror
FRAMEWORK	=	-L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
LIBFT	=	 -L./libft -lft
OBJS	= $(SRCS:.c=.o)
all:	$(NAME)
$(NAME):	$(OBJS)
			make bonus -C ./libft
			make -C./minilibx_opengl_20191021
			gcc $(FLAGS) $(SRCS) $(LIBFT) $(FRAMEWORK) -o $(NAME)

clean:	
		make clean -C ./libft
		make clean -C./minilibx_opengl_20191021
		rm -rf $(OBJS)

fclean:	clean
		make fclean -C./libft
		rm -rf $(NAME)

re:		fclean$(NAME)

.PHONY:		all clean fclean re