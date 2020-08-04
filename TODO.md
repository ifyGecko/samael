1:

	Since the overall scope is a collection of small parts interacting together it is a constant aim to clean up,
	add better comments and improve readability of all code. If naming wording even lack of comments or clarity
	in code is found adjust it in a way that help in your own thought process and submit so we can have the most
	concise details for unstanding.

2:

	Expand the current method to hide strings with brainfuck code so it generates cleaner but more obscure code.
	Such as using all symbols of the brainfuck language instead of just '+' and '>' while also randomly chosing
	syntax to be semtantically the same. Ex: +++++>++ would become ^^^^^(^^
	
3:

	This one is short and simple implement more anti-debugging techniques such as ptrace, 0xEBFE instruction scanner,
	user definted interrupts and any other idea that could be thought of.
	
4:

	Making c2 web control panel would be highly desirable but tedious to do. It should allow a UI that could show data
	about an infected host and allow the user to choose from a list of payloads to send. Even better would be a way to
	automate mass sequences of commands to one or more infected hosts. (Maybe just create an easy to use TUI instead)
	
5:

	It should be realatively easy to integrate torsocks for c2 comm. Hopefully all that would be needed to implement
	and test is statically link libtorsocks to samael and set up the c2 to run as a hidden service with the hostname
	set to this hidden service in the samael source code.
	
6:

	It is a main goal of this project to compile rather different binaries each time you build the project. So support
	for other C compilers (clang & tcc) could give use even more variety that just using gcc. Maybe this could fix how
	if you run the ssdeep test multiple times back to back you can actually get a failure meaning we managed to build
	a binary that is rather similar at the binary level to a previous build only a handful of compilations before it.

7:

	A good bit of research will be desired and probably need to implement encryption of infected host to c2 network
	traffic. Despite even if torsocks is useful and intergrated into samael we will still have traffic that is easily
	analyses at entry and exit nodes.

8:

	Turning samael and its way of infection into a rudamentary packer would be useful. Maybe not the most practical
	way but would definetly be strange to have a virus pack itself multuple times with itself giving a Matryoshka doll
	like effect. Should be simple to use the C preprocessor to only compile parts of the code used to infect a file if
	we would like to use it as a packer. However, just gutting samael and creating seperate tool would be acceptable
	too since we could have a variety of packer techniques in a tools/packer directory.