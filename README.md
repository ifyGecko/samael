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
	* int3, breakpoint, scanner
	
TODO:

	1) clean up, better comments and improve readability of the code
	2) obfuscate strings
	3) implement more anti-debugging (ptrace, 0xEBFE instruction scanner, etc)
	4) c2 web control panel
	5) integrate torsocks for c2 comm
	6) support other C compilers (clang & tcc)
