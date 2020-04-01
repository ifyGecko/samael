all:
	make sam-ael
	make host
	make reverse_shell
	make bind_shell

sam-ael: sam-ael.c
	gcc -ldl sam-ael.c -o sam-ael

host: host.c
	gcc host.c -o host

reverse_shell: reverse_shell.c
	gcc -shared -fPIC reverse_shell.c -o reverse_shell.so

bind_shell: bind_shell.c
	gcc -shared -fPIC bind_shell.c -o bind_shell.so

clean:
	rm sam-ael host reverse_shell.so bind_shell.so
