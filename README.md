# ssh-cli
So I don't have to type the hostnames out whenever I want to ssh, I'm making a simple cli to help me quickly navigate ssh hosts.

## Notes
I found this website very helpful: https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
This is my first time using getopt in a C program, so I will compile some notes here.

optstring: a string listing all the arguments. EX "abo" for -a -b and -o.
For options that require arguments, put a colon after them in optstring. EX "ab:o:" now -b and -o require arguments.
extern char *optarg is the address to the argument.

If you want to get rid of the default error messages put a colong as the first character in optstring. EX ":ab:o:"
