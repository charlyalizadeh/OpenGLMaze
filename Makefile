NAME=maze
SRCS=src/Shader.cpp src/Utils.cpp src/Grid.cpp src/InitOpenGL.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/VertexIndexBuffer.cpp src/glad.cpp src/main.cpp src/MazeGenerator.cpp
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))
INCLUDES=include include/glad
FLAGS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl#-Wall -Wextra -Werror
CC=g++

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o bin/$(NAME) $(FLAGS)

$(OBJS): obj/%.o: src/%.cpp
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -f bin/$(NAME)

fclean: clean
	rm -f obj/*

re: fclean $(NAME)

build:
	mkdir -p ./bin
	mkdir -p ./obj
