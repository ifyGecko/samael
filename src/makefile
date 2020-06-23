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
	cp ../tools/anti-debug/anti-debug.h ../tools/anti-debug/anti-debug.h.bak
	../tools/obfuscator/obfuscator.sh ../tools/anti-debug/anti-debug.h
	echo '#include "../tools/anti-debug/anti-debug.h"' >> samael.c
	make all
	../tools/anti-debug/anti-debug.sh
	make clean; make all
	strip --strip-all samael
	mv samael.c.bak samael.c
	mv ../tools/anti-debug/anti-debug.h.bak ../tools/anti-debug/anti-debug.h

clean:
	rm -f samael test
