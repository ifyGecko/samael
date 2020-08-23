default:
	cd src/ && make
	cd payloads/ && make
	cd tools/c2/ && make

clean:
	cd src/ && make clean
	cd payloads/ && make clean
	cd tools/c2/ && make clean
