all: uls clean

uls: libmx.a obj 
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic obj/*.o libmx/libmx.a -o uls -I inc

libmx.a: libmx/src/*.c libmx/inc/*.h
	@make -C libmx

obj: src/*.c inc/*.h
	@mkdir -p obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c src/*.c -I inc
	@mv *.o obj

clean:
	@rm -rf obj

uninstall: clean
	@rm -f uls
	@make -C libmx uninstall

reinstall: uninstall all

