#include <cstdlib>
#include <cstdio>
#include <string>
#include <dlfcn.h>
#include <unordered_map>

#include "sleepy_discord/sleepy_discord.h"
#include "discord_class.h"

void* loadModule(char* module_name);
int unloadModule(char* module_name);

std::unordered_map<std::string, void*> fptr_map;
std::unordered_map<std::string, void*> module_map;
AdminClientClass* client;

void AdminClientClass::onMessage(SleepyDiscord::Message message) {
    if(message.startsWith("!loadModule")){
        std::string contents = message.content;
        std::string module_name = contents.substr(contents.find(" ")+1);
        if(module_map.count(module_name)){
            sendMessage(message.channelID, "Module already loaded");
            return;
        }
        void* handle = loadModule((char*)module_name.c_str());
        if(handle == NULL){
            sendMessage(message.channelID, "Module failed to load");
            char* error = dlerror();
            printf("%s\n", error);
            return;
        }
        module_map[module_name] = handle;
        sendMessage(message.channelID, "Module loaded");
        return;
    }
    if(message.startsWith("!unloadModule")){
        std::string contents = message.content;
        std::string module_name = contents.substr(contents.find(" ")+1);
        if(!module_map.count(module_name)){
            sendMessage(message.channelID, "Module not loaded");
            return;
        }
        int ret = unloadModule((char*)module_name.c_str());
        if(ret){
            sendMessage(message.channelID, "Module failed to unload");
            return;
        }
        module_map.erase(module_name);
        sendMessage(message.channelID, "Module unloaded");
        return;
    }
    if(message.startsWith("!")){
        std::string contents = message.content;
        std::string command = contents.substr(1, contents.find(" ")-1);
        std::string args = contents.substr(contents.find(" ")+1);
        if(!fptr_map.count(command)){
            sendMessage(message.channelID, command + ": Command not found");
            return;
        }
        void (*fptr)(SleepyDiscord::Message, char*) = (void (*)(SleepyDiscord::Message, char*)) fptr_map.at(command);
        char* arg = (char*)malloc(sizeof(char) * contents.size()+1);
        strcpy(arg, (char*)contents.c_str());
        fptr(message, arg);
        free(arg);
    }
}

void* loadModule(char* module_name){
        char path[512] = "modules/";
        strcat(path, module_name);
        strcat(path, ".so");
        void* handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
        std::string m_name = module_name;
        if(handle != NULL)
            module_map[m_name] = handle;
        return handle;
}

int unloadModule(char* module_name) {
        std::string m_name = module_name;
        int retval = dlclose(module_map.at(m_name));
        return retval;
}

