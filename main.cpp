#include "main.h"

std::unordered_map<char*, void*> fptr_map;
std::unordered_map<char*, void*> module_map;

int main(int argc, char** argv){
    //load configurations 
    
    
    return 0;
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
