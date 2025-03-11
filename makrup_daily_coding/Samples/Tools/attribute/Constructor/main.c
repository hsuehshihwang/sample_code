#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

#define FUNC_TITLE2(x) \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(x)/2), FUNC_BAR, x, (int)(strlen(FUNC_BAR)-strlen(x)/2-strlen(x)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

// Define a structure to represent a command
typedef struct {
    const char* name;
    void (*function)(void);
} Command;

Command **commandTable=NULL; 
int commandSize=0; 

// Define some example command functions
void command1() {
    printf("Executing command 1\n");
}

void command2() {
    printf("Executing command 2\n");
}

// Macro to define a command and register it in the command table
#define REGISTER_COMMAND(name, func) \
    static void __attribute__((constructor)) register_##name() { \
        static Command cmd = {#name, func}; \
        addCommand(&cmd); \
    }

// Define a function to add a command to the command table
void addCommand(Command* cmd) {
    // Add code here to add the command to a global command table
    // For demonstration, we will just print the command name
    printf("Registered command: %s\n", cmd->name);
	if(!commandSize){
		commandTable=malloc(sizeof(Command*)*(commandSize+1)); 
		if(commandTable!=NULL){
			commandTable[commandSize]=cmd; 
			commandSize++; 
		}
	}else{
		Command **ppTmp=commandTable; 
		commandTable=realloc(commandTable, sizeof(Command*)*(commandSize+1)); 
		if(commandTable==NULL){
			commandTable=ppTmp; 
		}else{
			commandTable[commandSize++]=cmd; 
		}
	}
}

// List all available commands
void listCommands() {
	FUNC_TITLE; 
    printf("Available commands: %d\n", commandSize);
    // Add code here to iterate over the global command table and print each command
	Command **ppTmp=commandTable; 
	while(*ppTmp){
		printf("command: %s\n", (*ppTmp)->name); 
		ppTmp++; 
	}
}

// Function to execute a command by name
void executeCommand(const char* name) {
    // Add code here to find and execute the command by name
	for(int i=0; i<commandSize; i++){
		if(!strcmp(commandTable[i]->name, name)){
			commandTable[i]->function(); 
			return; 
		}
	}
	printf("command(\"%s\") not found!!\n", name); 
}

// Register commands using the macro
REGISTER_COMMAND(command1, command1)
REGISTER_COMMAND(command2, command2)

int main() {
	dbge(); 
    // List all available commands
    listCommands();
    
	FUNC_TITLE2("executeCommands"); 
    // Execute some commands
    executeCommand("command1");
    executeCommand("command2");
    executeCommand("unknown_command");
    
    exit(EXIT_SUCCESS);
}
