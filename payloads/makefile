all:
	make reverse_shell
	make bind_shell

debug: reverse_shell.c bind_shell.c
	gcc -ggdb3 -Og -Wall -shared -fPIC reverse_shell.c -o reverse_shell.so
	gcc -ggdb3 -Og -Wall -shared -fPIC bind_shell.c -o bind_shell.so

reverse_shell: reverse_shell.c
	gcc -shared -fPIC reverse_shell.c -o reverse_shell.so

bind_shell: bind_shell.c
	gcc -shared -fPIC bind_shell.c -o bind_shell.so

obfuscated:
	../tools/obfuscator/obfuscator.sh reverse_shell.c
	../tools/obfuscator/obfuscator.sh bind_shell.c
	make all
	strip --strip-all reverse_shell.so
	strip --strip-all bind_shell.so
	mv reverse_shell.c.bak reverse_shell.c
	mv bind_shell.c.bak bind_shell.c

clean:
	rm -f *.so
