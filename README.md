# samael
PoC Linux Malware

Disclaimer:

	The author is not responsible for any illegal use of this software or damage it could bring. It is only
	provided as a proof of concept. Use at your own risk...

Features:

	* prepending ELF virus
	* remote code execution via downloaded shared object payloads
	* reverse/bind shell payloads
	
TODO:

	1) clean up, comment and improve readability of the code
 	2) error handling
	3) implement anti-debugging (ptrace, int3 & jmp2self instruction scanner, etc)
	4) upgrade obfuscator
	
