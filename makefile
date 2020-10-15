default:
	cd src/ && ./build.sh
	cd payloads/ && make
	cd tools/c2/ && make

clean:
	cd src/ && ./build.sh clean
	cd payloads/ && make clean
	cd tools/c2/ && make clean
