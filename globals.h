#ifndef _GLOBALS_H_
#define _GLOBALS_H_

void* loadModule(char* module_name);
int unloadModule(char* module_name);

extern std::unordered_map<string, void*> fptr_map;
extern std::unordered_map<string, void*> module_map;
extern MyClientClass* client;

#endif
