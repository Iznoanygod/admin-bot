# admin-bot
Highly modular bot written in C++

# Module Structure
Modules should be written as shared libraries. Modules should use the shared library constructor to add the library symbols to the fptr_map. Modules should also use the shared library destructor to remove library symbols from the fptr_map.
