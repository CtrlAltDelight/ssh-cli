#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>

#define MAX_LINE_SIZE 300

static void _print_help() {
	printf("usage: sshcli [-h] [-n [HOST_NUM]]\n");
	printf("Note: if not HOST_NUM specified, HOST_NUM is 0\n");
	printf("\n");
	printf("optional arguments:\n");
	printf("-n [HOST_NUM], --host_num [HOST_NUM]     the line number in hostnames_file.txt for the desired hostname\n");
	printf("-h, --help     show this help message and exit\n");
	printf("\n");
}

int main(int argc, char* argv[]) {

	int host_idx = -1; // should change when option is given TODO: make this into a required argument or find better method of getting the hostname.

	// Get options
	// TODO: Add a way to edit hostnames_file on the command line.
	int c;
	while(1) {
		int option_index = 0;
		static struct option long_opts[] = {
			{ .name = "host_num", .has_arg = required_argument, .flag = NULL, .val = 'n' },
			{ .name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h' }
		};

		c = getopt_long(argc, argv, "hn:", long_opts, &option_index);
		//printf("c == %d\n", c);

		if(c == -1) {
			break;
		}
		switch(c) {
			case 0:
				printf("long option %s", long_opts[option_index].name);
				if(optarg) {
					printf(" with arg %s", optarg);
				}
				printf("\n");
				break;
			case 1:
				printf("regular argument '%s'\n", optarg);
				break;
			case 'n':
				printf("option n with value '%s'\n", optarg ? optarg : NULL);
				host_idx = atoi(optarg); // The +1 skips past the = sign
				break;
			case 'h':
				_print_help();
				return EXIT_SUCCESS;
			default:
				printf("?? getopt returnded character code 0%o ??\n", c);
		}
	}

	// get hostnames.txt
	char hostnames_filepath[200];
	char* homedir = getenv("HOME");
	fputs(homedir, stdout);
	if(homedir == NULL) {
		printf("Cannot get home directory path.\n");
		return EXIT_FAILURE;
	}
	strcpy(hostnames_filepath, homedir);
	strcat(hostnames_filepath, "/.config/sshcli/hostnames.txt");
	FILE* hostnames_file = fopen(hostnames_filepath, "r");
	if(hostnames_file == NULL) {
		printf("Cannot get home directory path.\n");
		return EXIT_FAILURE;
	}
	fputs(hostnames_filepath, stdout);

	// get hostname
	char hostname[MAX_LINE_SIZE];
	for(int i = 0; fgets(hostname, sizeof hostname, hostnames_file) != NULL && i < host_idx; i++);
	char ssh_command[MAX_LINE_SIZE];
	strcpy(ssh_command, "ssh ");
	strcat(ssh_command, hostname);
	fputs(ssh_command, stdout);
	system(ssh_command);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
