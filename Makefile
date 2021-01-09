
NAME = scop

FILES = main.c initialize.c handle_input.c shader_manager.c loop.c \
		matrix_operation.c math_util.c obj_parser.c 

OBJ = $(addprefix obj/,$(FILES:.c=.o))

LIBS = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm libft/libft.a #linkage


all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $^ -o $@ $(LIBS)

obj/%.o:src/%.c includes/*.h
	$(CC) -g -Wall -Wextra -c $< -o $@ -Iincludes -Ilibft

clean :
	@make clean -C libft
	rm -rf *.o

fclean : clean
	@make fclean -C libft
	rm -rf $(NAME)

re : fclean all

