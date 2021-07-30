This project has had most of its development done on a debian machine. Other
linux distributions have been used and tested but with varying results. If you
have issues with building or testing first make sure at least the following
tools are installed.

Build:

	make gcc gccgo

Test:

	ssdeep radare2

Note:

	Other tools may be required if your distribution does not include them
	by default. An example of this would be bash, netcat, sed, or awk but
	since most common distributions include these by default they are not
	included above.
