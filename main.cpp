#include "main.h"

MyClientClass* client;
std::unordered_map<char*, void*> fptr_map;
std::unordered_map<char*, void*> module_map;

int main(int argc, char** argv){
    //load configurations 
    config_t cfg;
    config_init(&cfg);
    if(! config_read_file(&cfg, "discord.cfg")) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
        config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }
    const char* token;
    if(!config_lookup_string(&cfg, "token", &token)) {
        fprintf(stderr, "No 'token' setting in configuration file.\n");
        return(EXIT_FAILURE);
    }
    
    //initialize bot
    MyClientClass bot(token, SleepyDiscord::USER_CONTROLED_THREADS);
    client = &bot;
    client->run();
}

void* loadModule(char* module_name){
    char path[512] = "modules/";
    strcat(path, module_name);
    strcat(path, ".so");
    void* handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if(handle != NULL)
        module_map[module_name] = handle;
    return handle;
}

int unloadModule(char* module_name) {
    int retval = dlclose(module_map.at(module_name));
    return retval;
}
