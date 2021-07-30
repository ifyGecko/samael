Tests:

	   *SSDEEP - computes fuzzy hash of samael validating high uniqueness between compiled samples.

	   *Reverse_shell - runs samael and delivers a reverse_shell payload then opens a netcat
	   listener to validate shell connection.

	   *Bind_shell - runs samael and delivers a bind_shell payload then opens a netcat
	   connection to validate shell functionality.

	   *Anti-debug - runs samael in r2, if samael detects any extra 0xCC's it will not infect and exit.
	   This leaves samael in the current directory by not allowing it to delete itself indicating
	   debugger presence detected.

	   *Run_all - runs the above test scripts together.

Notes:
	   Due to inconsistencies between different linux distros you may need to sleep for 60
	   seconds if you plan to run run_all.sh or any of the shell test scripts back to back.
	   ex: ./run_all.sh; sleep 60; ./run_all.sh
