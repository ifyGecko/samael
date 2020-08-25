default: samael.c
	../tools/obfuscator/obfuscator.sh samael.c
	../tools/obfuscator/obfuscator.sh samael.h
	../tools/hide-strings/hide-strings.sh samael.c
	../tools/hide-strings/hide-strings.sh samael.h
	gcc samael.c -o samael
	../tools/anti-debug/anti-debug.sh
	make clean
	gcc samael.c -o samael
	strip --strip-all samael
	mv samael.c.bak samael.c
	mv samael.h.bak samael.h
	cp /bin/ls ./test

clean:
	rm -f samael test
