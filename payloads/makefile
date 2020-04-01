all:
	make reverse_shell
	make bind_shell

reverse_shell: reverse_shell.c
	gcc -shared -fPIC reverse_shell.c -o reverse_shell.so

bind_shell: bind_shell.c
	gcc -shared -fPIC bind_shell.c -o bind_shell.so

clean: rm reverse_shell.so bind_shell.so
