#include "CommandHandler.h"

void CommandHandler::setAction(Action _action)
{
	action = _action;
}

void CommandHandler::setCommand(char* _command)
{
	strcpy(command, _command);
}

CommandHandler * CommandHandler::getNextHandler()
{
	return next;
}

Action CommandHandler::getAction()
{
	return action;
}

char* CommandHandler::getCommand()
{
	return command;
}

void CommandHandler::setNextHandler(CommandHandler* _next)
{
	next = _next;
}
