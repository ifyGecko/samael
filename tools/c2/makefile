c2: c2.go
	gccgo c2.go -o c2
	cd ../../payloads/ && make obfuscated

clean:
	rm c2
	cd ../../payloads/ && rm *.so
