#include "SimpleCommandsLib.h"

SimpleCommands command;

void setup() {

    Serial.begin(9600);

    command.begin(Serial);

    // creates a new command called "echo" wich calls the function "onEcho"
    command.addCommand("echo", onEcho);

}

void loop() {
    // the method "run" scans the serial buffer for new commands
    command.run();
    delay(200);
}

void onEcho(int argc, char *argv[]) {
    Serial.print("This command has ");
    Serial.print(argc);
    Serial.println(" arguments: ");

    for(int i=0; i<argc; i++){
        Serial.println(argv[i]);
    }

}
