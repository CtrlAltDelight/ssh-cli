# ssh-cli
So I don't have to type the hostnames out whenever I want to ssh, I'm making a simple cli to help me quickly navigate ssh hosts.

## Instructions
Clone this repository, change hostnames.txt to be whichever hostnames you want to use. (hostname0 is default)
Use "make" and the executable will be created.
Run the executable to use the default hostname (hostname0), or specify a hostname with -n NUM (AKA --host_name NUM)

## Notes
I found this website very helpful: https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
This is my first time using getopt in a C program, so I will compile some notes here.

optstring: a string listing all the arguments. EX "abo" for -a -b and -o.
For options that require arguments, put a colon after them in optstring. EX "ab:o:" now -b and -o require arguments.
extern char *optarg is the address to the argument.

If you want to get rid of the default error messages put a colong as the first character in optstring. EX ":ab:o:"
