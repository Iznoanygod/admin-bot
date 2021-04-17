#include <cstdlib>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "sleepy_discord/sleepy_discord.h"
#include "discord_class.h"
#include "globals.h"

void ping(SleepyDiscord::Message message, char* arg);

__attribute__((constructor))
void constructor(){
    printf("ping module loading...\n");
    std::string ping_command = "ping";
    fptr_map[ping_command] = (void*)ping;
    printf("ping command registered...\n");
}

void ping(SleepyDiscord::Message message, char* arg){
    client->sendMessage(message.channelID, "Pong");
}

__attribute__((destructor))
void destructor(){
    printf("unloading ping module...\n");
    std::string ping_command = "ping";
    fptr_map.erase(ping_command);
    printf("ping command unregistered...\n");
}
