# samael
PoC Linux Malware

Disclaimer:

	The author is not responsible for any illegal use of this software or damage it could bring.
	It is only provided as a proof of concept. Use at your own risk...

Purpose:

	Getting root in a boot2root challenge is a lot of fun but shouldn't there still more to learn.
	
	This projects aims to be a utility for managing and maintaining control of a compromised host
	root account in a simple yet educational manner.

Features:

	* prepending ELF virus
	* remote code execution via downloaded shared object payloads
	* reverse/bind shell payloads
	* random junk code insertion
	* optimization levels applied randomly per function
	* minimal command & control server
	* int3, breakpoint, scanner