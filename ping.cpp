#include <cstdlib>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "sleepy_discord/sleepy_discord.h"
#include "discord_class.h"
#include "globals.h"
#include <time.h>

void ping(SleepyDiscord::Message message, char* arg);

__attribute__((constructor))
void ping_constructor(){
    printf("ping module loading...\n");
    std::string ping_command = "ping";
    fptr_map[ping_command] = (void*)ping;
    printf("ping command registered...\n");
}

void ping(SleepyDiscord::Message message, char* arg){
    SleepyDiscord::Message pong_message = client->sendMessage(message.channelID, ".");
    std::string time_0 = message.timestamp;
    std::string time_1 = pong_message.timestamp;
    long double _time_0, _time_1;
    printf("%s\n%s\n", time_0.c_str(), time_1.c_str());
    sscanf(time_0.c_str(), "%*d-%*d-%*dT%*d:%*d:%Lf+%*d:%*d", &_time_0);
    sscanf(time_1.c_str(), "%*d-%*d-%*dT%*d:%*d:%Lf+%*d:%*d", &_time_1);
    char buff[1024];
    sprintf(buff, "Pong! It took %Lfs for that response!", _time_1 - _time_0);
    client->editMessage(message.channelID, pong_message.ID, buff);
}

__attribute__((destructor))
void ping_destructor(){
    printf("unloading ping module...\n");
    std::string ping_command = "ping";
    fptr_map.erase(ping_command);
    printf("ping command unregistered...\n");
}
