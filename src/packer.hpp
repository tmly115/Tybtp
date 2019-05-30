/*
 *  Thomas Young (c) 2019 . Virtual File System File . 
 *  /src/packer.hpp
 * 
 *  The function's used to plot out a vfsf file from the directory passed.
 *  
 */

#include <iostream>
#include <fstream>

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
    vfsf_file << "DIRECTORY " << dir_name << std::endl;
    
    vfsf_file << "ENDDIR" << std::endl;
}

void pack(std::string dir_name){
    std::ofstream vfsf_file;
    vfsf_file.open(dir_name + ".vfsf");
    pack_file(dir_name, vfsf_file);
    vfsf_file.close();
}
