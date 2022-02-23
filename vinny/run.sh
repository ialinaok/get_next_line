clear
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=19 get_next_line.c get_next_line.h get_next_line_utils.c -o run
valgrind --leak-check=full ./run 