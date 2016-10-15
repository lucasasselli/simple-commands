#include "SimpleCommands.h"

SimpleCommands::SimpleCommands()
{
	//
}

void SimpleCommands::begin(Stream& _serial)
{
	serial = &_serial;
}

void SimpleCommands::addCommand(char* command, Action action)
{
	/*
		Commands are added as elements of linked list; each node of the list is called 'handler'. This class has two pointers to the edges of this list, first_handler and last_handler, and very handler points to the following object.
		When both this pointer are null no command is set.
	*/

	CommandHandler* new_handler = (CommandHandler*) malloc(sizeof(CommandHandler));

	new_handler->setAction(action);
	new_handler->setCommand(command);

	if (last_handler == nullptr || first_handler == nullptr) {
		// If edges are null, doesn't have to set a pointer in last_handler because this is the first.
		first_handler = new_handler;
		last_handler = new_handler;
	}else {
		last_handler->setNextHandler(new_handler);
		last_handler = new_handler;
	}

	cmdset_size++;
}

void SimpleCommands::run()
{
	char buffer[100];
	int i = 0;

	// Reads the serial buffer
	while (serial->available() > 0) {
		buffer[i] = serial->read();
		i++;
	}

	buffer[i] = NULL;

	char** argv = explode(buffer);

	int argc = 0;
	while (strcmp(argv[argc], "") != 0) {
		argc++;
	}

	CommandHandler* pointer = first_handler;

	if (i > 0) {
		for (int j = 0; j < cmdset_size; j++) {
			if (strcmp(argv[0], (const char*)pointer->getCommand()) == 0) {
				pointer->getAction()(argc, argv);
			}
			pointer = pointer->getNextHandler();
		}
	}

	// Exploded memory MUST be freed
	for (int j = 0; j <= argc; j++) {
		free(argv[j]);
	}
	free(argv);
}

void SimpleCommands::delayWithCommands(int sec)
{
	/*
		This function act both as a delay and as a command listener.
		This is particularly useful, for example, when running a low-frequency routine by delaying the next loop with delay(): during this time you can send commands to the device, execute them, and the continue delaying after.
	*/

	for (int i = 0; i < sec; i++) {
		run();
		delay(1000);
	}
}


char** SimpleCommands::explode(char* line)
{
	/*
		Explodes a string into an array of words. NULL is used as last character in every set.
		MAX_CHARS*MAX_PARAMS bytes of memory are allocated and have to be manually freed after each call. This is due to avoid static variables.
	*/

	char** output = (char**) malloc(MAX_PARAMS*sizeof(char*));
	char* token;

	int i = 0;
	token = strtok(line, " ");

	while (token != NULL)
	{
		char* param = (char*) malloc(MAX_CHARS*sizeof(char));
		strcpy(param, token);
		output[i] = param;
        token = strtok(NULL, " ");
		i++;
	}

	char* param = (char*)malloc(MAX_CHARS*sizeof(char));
	strcpy(param, "");
	output[i] = param;

	return output;
}
