Tests:

	   *SSDEEP - computes fuzzy hash of samael validating high uniqueness between compiled samples.
	   Passing 'obfuscated' to the test script is necessary for a potential pass.
	   ex: tests/ssdeep obfuscated

	   *Reverse_shell - runs samael and delivers a reverse_shell payload then opens a netcat
	   listener to validate shell connection. Passing 'obfuscated' to the test script is optional.
	   ex: tests/reverse_shell.sh

	   *Bind_shell - runs samael and delivers a bind_shell payload then opens a netcat
	   connection to validate shell functionality. Passing 'obfuscated' to the test script is optional.
	   ex: tests/bind_shell.sh obfuscated

	   *Run_all - runs the above test scripts together. Passing 'obfuscated' is optional but
	   SSDEEP will fail since samael will always compute to the same hash
	   ex: ./run_all.sh

Notes:
	   Due to inconsistencies between different linux distros you may need to sleep for 60
	   seconds if you plan to run any of the test scripts, except ssdeep, back to back.
	   ex: ./run_all.sh; sleep 60; ./run_all.sh