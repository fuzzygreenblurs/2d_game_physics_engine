build:
	g++ --std=c++17 -Wall ./src/*.cpp ./src/Physics/*.cpp \
	-I /opt/homebrew/Cellar/sdl2/2.28.2/include/ \
	-I /opt/homebrew/Cellar/sdl2_gfx/1.0.4/include \
	-L /opt/homebrew/Cellar/sdl2/2.28.2/lib \
	-L /opt/homebrew/Cellar/sdl2_gfx/1.0.4/lib \
	-L /opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib \
	-lSDL2 -lSDL2_image -lSDL2_gfx -lm \
	-o app

run:
	./app

clean:
	rm app
