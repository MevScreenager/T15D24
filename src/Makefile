all: state_sort state_search clear_state

main: state_search

state_sort: state_sort.o binary_files_functions.o
	gcc state_sort.o binary_files_functions.o -o ../build/Quest_1 -Wall -Wextra -Werror -std=c11

state_search: state_search.o binary_files_functions.o
	gcc state_search.o binary_files_functions.o -o ../build/Quest_2 -Wall -Wextra -Werror -std=c11

clear_state: clear_state.o binary_files_functions.o
	gcc clear_state.o binary_files_functions.o -o ../build/Quest_3 -Wall -Wextra -Werror -std=c11

clear_state.o: clear_state.c state_sort.h
	gcc -c clear_state.c -Wall -Wextra -Werror -std=c11

state_search.o: state_search.c state_sort.h
	gcc -c state_search.c -Wall -Wextra -Werror -std=c11

state_sort.o: state_sort.c state_sort.h
	gcc -c state_sort.c -Wall -Wextra -Werror -std=c11

binary_files_functions.o: binary_files_functions.c state_sort.h
	gcc -c binary_files_functions.c -Wall -Wextra -Werror -std=c11

clean:
	rm -rf *.o ../build/Quest_1 ../build/Quest_2 ../build/Quest_3

rebuild: clean all
