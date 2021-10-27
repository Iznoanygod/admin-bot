#include "sleepy_discord/sleepy_discord.h"
#include "discord_class.h"
#include "globals.h"
#include <sqlite3.h>

void openDB(SleepyDiscord::Message message, char* arg);

__attribute__((constructor))
void database_constructor(){
    printf("database module loading...\n");

    //printf("SQLite version %s\n", sqlite3_libversion());
    std::string opendb_command = "open_database";
    fptr_map[opendb_command] = (void*)openDB;
    printf("open_database command registered...\n");
}

void openDB(SleepyDiscord::Message message, char* arg){
    std::string contents = message.content;
    char fileName[512];
    printf("%s\n", sqlite3_libversion());
    sscanf(contents.c_str(), "%*s %s", fileName);

    
}

__attribute__((destructor))
void database_destructor(){
    printf("unloading database module...\n");
    std::string opendb_command = "open_database";
    fptr_map.erase(opendb_command);
    printf("open_database command unregistered...\n");
}

