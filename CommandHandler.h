#ifndef _CommandHandler_h
#define _CommandHandler_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_CHARS 20

typedef void (*Action) (int, char**);

class CommandHandler
{
public:
	void setAction(Action);
	void setCommand(char*);
	void setNextHandler(CommandHandler*);
	Action getAction();
	char* getCommand();
	CommandHandler* getNextHandler();
private:
	CommandHandler* next = nullptr;
	Action action;
	char command[MAX_CHARS];
};

#endif

