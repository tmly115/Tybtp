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
    while(fgets(buffer, 256, pipe)){
        buffer[strlen(buffer) - 1] = '\0';
        files.push_back(buffer);
    } 
    pclose(pipe);
    return files;
}

std::vector<std::string> directorys_vector(){
    std::vector<std::string> directorys;
    FILE *pipe = popen("ls -p | grep /", "r");         // Lists all the elements in the directory and then only shows the ones with a '/' on the end.
    char buffer[256];
    while(fgets(buffer, 256, pipe)){
        buffer[strlen(buffer) - 1] = '\0';
        directorys.push_back(buffer);
    }
    pclose(pipe);
    return directorys;
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
        pack_file(file, vfsf_file);
    }
    for(std::string directory : directorys_vector()){
        pack_directory(directory, vfsf_file);
    }
    vfsf_file << "ENDDIR" << std::endl;
}

void pack(std::string dir_name){
    std::ofstream vfsf_file;
    vfsf_file.open(dir_name + ".vfsf");
    pack_directory(dir_name, vfsf_file);
    vfsf_file.close();
}