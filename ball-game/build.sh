#gcc -o game main.c -lraylib -Llib -Iinclude
gcc -o game main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Llib -Iinclude
