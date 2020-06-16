all:
	make samael

samael: samael.c
	gcc -ldl samael.c -o samael
	cp /bin/ls ./test

debug: samael.c
	gcc -ggdb3 -Og -Wall -ldl samael.c -o samael
	cp /bin/ls ./test

obfuscated:
	../tools/obfuscator/obfuscator.sh samael.c
	make all
	strip --strip-all samael
	mv samael.c.bak samael.c

clean:
	rm -f samael test
