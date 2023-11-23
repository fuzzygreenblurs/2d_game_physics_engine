## why do we use header files?

- headers provide declarations for things that are compiled elsewhere
- adding function definitions to a file that you include elsewhere will copy those functions there
- when the individual files are then linked together, redefinition errors are raised
- this is because we essentially have multiple function definitions

- function declarations are useful for telling the compiler that the function exists
	- just not necessarily in this file

## compilation advantages

- if you change something, it has to be recompiled
- if you dont, it doesnt need to be recompiled
	- example: you only change the body of a function
		- why should every other file calling the function need to be recompiled?

## how does the compiler find the defintion of the function after it sees the declaration?

- the linker finds the defintion because you tell it where it is. this is done either thru:
	- passing the object file in the command line
	- or by telling it the name of the library

