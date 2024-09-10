# all:
# 	gcc main.c -Wall -Werror -Wextra -pedantic -o main -lSDL2
all:
	gcc src/*.c -Wall -Werror -Wextra -pedantic -o main.exe -lmingw32 -lSDL2main -lSDL2