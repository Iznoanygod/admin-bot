#include "main.h"

extern AdminClientClass* client;
extern std::unordered_map<std::string, void*> fptr_map;
extern std::unordered_map<std::string, void*> module_map;

int exists(const char *fname) {
    FILE *file;
    if ((file = fopen(fname, "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char** argv){
    //load configurations 
    config_t cfg;
    config_init(&cfg);
    if (!exists("discord.cfg")) {
        printf("config file does not exist\ncreating empty file\n");
        system("touch discord.cfg && echo \"token = \\\" \\\"\" >> discord.cfg");
        return 0;
    }
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
    AdminClientClass bot(token, SleepyDiscord::USER_CONTROLED_THREADS);
    client = &bot;
    client->run();
}

