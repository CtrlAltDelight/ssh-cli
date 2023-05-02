#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <argp.h>

// TODO: finish implementing argp
// Adapted from https://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html
const char *argp_program_version = "sshcli 1.1";
const char *argp_program_bug_address = "<git+git@ctrlaltdelight.org>";
static char doc[] = "sshcli -- Connects to your favorite ssh connections quickly.";

static struct argp_option options[] = {
	{"host_idx", 'n', "value", 0, "Select which line to use from the file."},
	{ 0 }
};

static char args_doc[] = "";
struct arguments {
	//char *args[2];                /* arg1 & arg2 */
	int host_idx;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
	/* Get the input argument from argp_parse, which we
	   know is a pointer to our arguments structure. */
	struct arguments *arguments = state->input;

	switch (key) {
		case 'n':
			arguments->host_idx = atoi(arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	/* Keeping a copy while working locally
	switch (key) {
		case 'n':
			arguments->host_idx = 1;
			break;
		case 'v':
			arguments->verbose = 1;
			break;
		case 'o':
			arguments->output_file = arg;
			break;

		case ARGP_KEY_ARG:
			if (state->arg_num >= 2)
			// Too many arguments.
			argp_usage (state);

			arguments->args[state->arg_num] = arg;

			break;

		case ARGP_KEY_END:
			if (state->arg_num < 2)
			// Not enough arguments.
			argp_usage (state);
			break;

		default:
			return ARGP_ERR_UNKNOWN;
    }
	*/

	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

// implementing argp end



#define MAX_LINE_SIZE 300

/*
static void _print_help() {
	printf("usage: sshcli [-h] [-n [HOST_NUM]]\n");
	printf("Note: if not HOST_NUM specified, HOST_NUM is 0\n");
	printf("\n");
	printf("optional arguments:\n");
	printf("-n [HOST_NUM], --host_num [HOST_NUM]     the line number in hostnames_file.txt for the desired hostname\n");
	printf("-h, --help     show this help message and exit\n");
	printf("\n");
}
*/

int main(int argc, char* argv[]) {
	struct arguments arguments;

	// Default values for arguments.
	arguments.host_idx = -1;
	
	// Parse the arguments.
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// Get options
	// TODO: Add a way to edit hostnames_file on the command line.

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
	for(int i = 0; fgets(hostname, sizeof hostname, hostnames_file) != NULL && i < arguments.host_idx; i++);
	char ssh_command[MAX_LINE_SIZE];
	strcpy(ssh_command, "ssh ");
	strcat(ssh_command, hostname);
	fputs(ssh_command, stdout);
	system(ssh_command);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
