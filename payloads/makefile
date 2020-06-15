all:
	make reverse_shell
	make bind_shell

obfuscated:
	../tools/obfuscator/obfuscator.sh reverse_shell.c
	../tools/obfuscator/obfuscator.sh bind_shell.c
	make all
	strip --strip-all reverse_shell.so
	strip --strip-all bind_shell.so
	mv reverse_shell.c.bak reverse_shell.c
	mv bind_shell.c.bak bind_shell.c

reverse_shell: reverse_shell.c
	gcc -shared -fPIC reverse_shell.c -o reverse_shell.so

bind_shell: bind_shell.c
	gcc -shared -fPIC bind_shell.c -o bind_shell.so

clean:
	rm -f *.so
