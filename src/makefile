all:
	make sam-ael
	make host

sam-ael: sam-ael.c
	gcc -ldl sam-ael.c -o sam-ael

host: host.c
	gcc host.c -o host

obfuscated:
	../tools/obfuscator.sh sam-ael.c
	make all
	mv sam-ael.c.bak sam-ael.c

clean:
	rm sam-ael host
