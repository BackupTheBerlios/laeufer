/***************************************************************************
 comtest.cc Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include "mlp_bus.h"

#define MAX_ARGS 16
mlp_bus bus("/dev/ttyS1");

void
massert(int v)
{
	if (v < 0) {
		cerr << "Aborting on error...\n";
		exit(1);
	}
}

void
print_help()
{
	cout << "Usage:\n\n'q'\t\t\tquit\n"
		"'p'\t\t\tpoll: Try to retreive messages\n"
		"'t<id>:<op>[,<arg>]*\ttransmit: Try to send message\n\n";
}

void
poll()
{
	int count = 0;
	int w;
	fflush(NULL);
	do {
		int id, op, len, e;
		byte buf[128];

		w = bus.messages_waiting();

		massert(w);

		if (w > 0) {
			int i;
			massert(bus.get_message(&id, &op, &(buf[0]), &len));

			fprintf(stderr, "[%02x] -> %02x (", id, op);
			for (i = 0; i < len; i++) {

				fprintf(stderr, "%02x", buf[i]);
				if (i+1 < len)
					fprintf(stderr, ", ");
			}

			fprintf(stderr, ")\n");
			++count;
		}
	} while (w);
	fflush(NULL);

	cout << "Retreived " << count << " messages.\n";
}

void
transmit(char *what)
{
	char *next;
	int id = strtol(what, &next, 0);

	if (next == what) {
		cerr << "Could not parse ID, must be numeric\n";
		return;
	}

	while (*next && !isdigit(*next))
		++next;

	if (!*next) {
		cerr << "Missing operation number\n";
		return;
	}

	what = next;
	int op = strtol(next, &next, 0);

	byte args[MAX_ARGS];
	int argc = 0;

	while (*next) {
		while (*next && !isdigit(*next))
			++next;

		if (*next) {
			if (argc > MAX_ARGS) {
				cerr << "Too many (more than " << MAX_ARGS << ") arguments!\n";
				return;
			}
			args[argc] = strtol(next, &next, 0);
			++argc;
		}
	}

	massert(bus.send(id, op, &(args[0]), argc));

	fflush(NULL);
	fprintf(stderr, "[%02x] <- %02x (", id, op);
	for (int i = 0; i < argc; i++) {
		fprintf(stderr, "%02x", args[i]);
		if (i+1 < argc)
			fprintf(stderr, ", ");
	}
	fprintf(stderr, ")\n");
	fflush(NULL);
}

void
cmd_prompt()
{
	char buf[128];

	do {

		cout << ">>";
		fgets(buf, 128, stdin);

		switch (tolower(buf[0])) {

		case '?': print_help();
			break;

		case 'p': poll();
			break;

		case 't': transmit(buf + 1);
			break;

		case 'q': exit(0);
			break;

		default:
			printf ("Unrecognized command. Try '?' for help\n");
		}
	} while (1);
}

void
init()
{
	int devs_nr, ops_nr, bc, i;
	bool *devs;
	bool **ops;

	bus.get_id_setup(&bc, &devs_nr, &ops_nr);

	devs = (bool *) malloc(sizeof(bool) * devs_nr);
	ops = (bool **) malloc(sizeof(bool *) * devs_nr);

	for (i = 0; i < devs_nr; i++)
		ops[i] = (bool *) malloc(sizeof(bool) * ops_nr);

	massert(bus.init(devs, ops));

	cout << "Successfully opened bus. BCast = " << bc << ", max device = " << devs_nr << ", max op = " << ops_nr << endl;

	for (i = 0; i < devs_nr; i++)
		free(ops[i]);

	free(ops);
	free(devs);
}

int
main(int argc, char **argv)
{
	cout << "<< COMTEST 0.1 >>\n"
	     << "On the command prompt, use '?' for help\n";

	init();

	cmd_prompt();
}
