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

	This one is short and simple implement more anti-debugging techniques such as 0xEBFE instruction scanner,
	user defined interrupts and any other idea that could be thought of.
	
4:

	Improve C2 and give it a useful CLI for managing old and new connecting hosts.
	
5:

	It is a main goal of this project to compile rather different binaries each time you build the project. So support
	for other C compilers (clang & tcc) could give use even more variety that just using gcc. Maybe this could fix how
	if you run the ssdeep test multiple times back to back you can actually get a failure meaning we managed to build
	a binary that is rather similar at the binary level to a previous build only a handful of compilations before it.

6:

	A bit of research will probably be needed to implement encryption of infected host to c2 network traffic.

7:

	Turning samael and its way of infection into a rudamentary packer would be useful. Maybe not the most practical
	way but would definetly be strange to have a virus pack itself multuple times with itself giving a Matryoshka doll
	like effect. Should be simple to use the C preprocessor to only compile parts of the code used to infect a file if
	we would like to use it as a packer. However, just gutting samael and creating seperate tool would be acceptable
	too since we could have a variety of packer techniques in a tools/packer directory.
