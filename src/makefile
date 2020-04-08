all:
	make sam-ael

sam-ael: sam-ael.c
	gcc -ldl sam-ael.c -o sam-ael

obfuscated:
	../tools/obfuscator/obfuscator.sh sam-ael.c
	make all
	strip --strip-all sam-ael
	mv sam-ael.c.bak sam-ael.c

clean:
	rm sam-ael
