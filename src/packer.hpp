/*
 *  Thomas Young (c) 2019 . Virtual File System File . 
 *  /src/packer.hpp
 * 
 *  The function's used to plot out a vfsf file from the directory passed.
 *  
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <unistd.h>

std::vector<std::string> files_vector(){
    std::vector<std::string> files;
    FILE *pipe = popen("ls -p | grep -v /", "r");       // Lists all the elements in the directory and removes those with a '/' on the end (directories).
    char buffer[256];
    while(fgets(buffer, 100, pipe)){
        files.push_back(buffer);
    } 
    pclose(pipe);
    return files;
}

void pack_file(std::string file_name, std::ofstream &vfsf_file){
    std::ifstream file;
    std::string line;
    file.open(file_name);
    vfsf_file << "FILE " + file_name << std::endl;
    while(getline(file, line)){
        vfsf_file << line << std::endl;    
    }
    vfsf_file << "ENDFILE" << std::endl;
    file.close();
}

void pack_directory(std::string dir_name, std::ofstream &vfsf_file){
    if(chdir(dir_name.c_str()) != 0){
        std::cout << "Directory does not exist or insufficent permisions?!\nRun as Sudo if directory is present" << std::endl;
        exit(1);
    }
    vfsf_file << "DIRECTORY " << dir_name << std::endl;
    for(std::string file : files_vector()){
        std::cout << file << std::endl;
    }
    vfsf_file << "ENDDIR" << std::endl;
}

void pack(std::string dir_name){
    std::ofstream vfsf_file;
    vfsf_file.open(dir_name + ".vfsf");
    pack_directory(dir_name, vfsf_file);
    vfsf_file.close();
}