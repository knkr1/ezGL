current_dir := $(shell cd)

hello:
	gcc $(current_dir)/src/glad.c main.c -I$(current_dir)/include -L$(current_dir)/lib -lglfw3 -lglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32 -mwindows -o $(current_dir)/build/main.exe
	./build/main.exe
