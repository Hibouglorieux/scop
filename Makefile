
NAME = openglstuff

FILES = main.c handle_input.c shaderManager.c loop.c matrix_operation.c math_util.c obj_parser.c 

OBJ = $(addprefix obj/,$(FILES:.c=.o))

LIBS = -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm libft/libft.a #linkage


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

obj/%.o:%.c includes/*.h
	$(CC) -g -Wall -Wextra -c $< -o $@ -Iincludes -Ilibft

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

