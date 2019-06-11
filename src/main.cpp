/*
 *  Thomas Young (c) 2019 . Virtual File System File . 
 *  /src/main.cpp
 * 
 *  This is the main file for the vfsf app, it parses the commands given on execution and subsequently
 *  performs those tasks.
 *   
*/

#include <iostream>
#include <cstring>

#include "builder.hpp"
#include "packer.hpp"

void program_info();

int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "pack") == 0){
            if(argc > 2){
                pack(argv[2]);
            } else {
                std::cout << "Creates a .vfsf file from the directory specified." << std::endl;
            }
        } else if(strcmp(argv[1], "unpack") == 0){
            if(argc > 2){
                unpack(argv[2]);
            } else {
                std::cout << "Unpacks a .vfsf file and re-creates the directory and it's sub-directory's at the shell's current path." << std::endl;
            }
        } else {
            std::cout << "Command not recognised!\nSimply execute vfsf again with no arguments to see a list of correct commands." << std::endl;
        }
    } else {
        program_info();
    }
    return 0;
}

void program_info(){
    std::cout << "App that can condence filesystems into a .vfsf file and back to a full filesystem.\n" << std::endl;
    std::cout << "Command:\t\tDescription:" << std::endl;
    std::cout << "pack <directory>\tCreates a .vfsf file from the directory specified." << std::endl;
    std::cout << "unpack <file>\t\tUnpacks a .vfsf file and re-creates the directory and it's sub-directory's at the shell's current path." << std::endl;
}