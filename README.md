# samael
PoC Linux Malware

Disclaimer:

	The author is not responsible for any illegal use of this software or damage it could bring. It is only
	provided as a proof of concept. Use at your own risk...

Features:

	* prepending ELF virus
	* remote code execution via downloaded shared object payloads
	* reverse/bind shell payloads
	* random junk code insertion
	* optimization levels applied randomly per function
	* minimal command & control server
	
TODO:

	1) clean up, better comments and improve readability of the code
	2) obfuscate strings
	3) implement anti-debugging (ptrace, 0xCC & 0xEBFE instruction scanner, impossible disassembly, etc)
	4) c2 web control panel
	5) error handling
