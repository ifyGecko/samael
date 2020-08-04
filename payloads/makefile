default:reverse_shell.c bind_shell.c
	gcc -shared -fPIC reverse_shell.c -o reverse_shell.so
	gcc -shared -fPIC bind_shell.c -o bind_shell.so

clean:
	rm -f *.so
