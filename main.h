#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdlib>
#include <cstdio>
#include <string>
#include <dlfcn.h>
#include <libconfig.h>
#include <unordered_map>

#include "sleepy_discord/sleepy_discord.h"
#include "discord_class.h"

void* loadModule(char* module_name);
int unloadModule(char* module_name);

#endif
