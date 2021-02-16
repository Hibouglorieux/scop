
NAME = scop

FILES = main.c initialize.c handle_input.c shader_manager.c loop.c \
		matrix.c matrix_operation.c math_util.c \
		obj_parser.c obj_parser2.c

OBJ = $(addprefix obj/,$(FILES:.c=.o))

LIBS = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm libft/libft.a #linkage

COMPILE_FLAGS = -Wall -Wextra -Werror -g


all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $^ -o $@ $(LIBS)

obj/%.o:src/%.c includes/*.h
	$(CC) $(COMPILE_FLAGS) -c $< -o $@ -Iincludes -Ilibft

clean :
	@make clean -C libft
	rm -rf obj/*.o

fclean : clean
	@make fclean -C libft
	rm -rf $(NAME)

re : fclean all

