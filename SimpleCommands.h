#ifdef _SimpleCommands_h
#define _SimpleCommands_h

#define MAX_PARAMS 5

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CommandHandler.h"

class SimpleCommands {
public:
	SimpleCommands();
	void begin(Stream&);
	void addCommand(char*, Action);
	void run();
	void delayWithCommands(int);
private:
	char** explode(char*);
	Stream* serial;
	CommandHandler* first_handler = nullptr;
	CommandHandler* last_handler = nullptr;
	int cmdset_size = 0;
};

#endif
