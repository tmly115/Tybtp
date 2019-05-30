/*
 *  Thomas Young (c) 2019 . Virtual File System File . 
 *  /src/builder.hpp
 * 
 *  Function's used to take a .vfsf file and re-create the files on disk.
 * 
*/

#include <iostream>
#include <fstream>
#include <unistd.h>        // Used for the 'chdir()' function.
#include <sys/stat.h>      // Used for the 'mkdir()' function.

void build_file(std::string file_name, std::ifstream &vfsf_file){
    std::string line;
    std::ofstream new_file;
    new_file.open(file_name);
    std::cout << file_name << std::endl;
    getline(vfsf_file, line);
    while(line != "ENDFILE"){
        new_file << line << std::endl;
        getline(vfsf_file, line);
    }
    new_file.close();
}

void build_directory(std::string dir_name, std::ifstream &vfsf_file){
    std::string line, file_name, subdir_name;
    std::cout << dir_name << std::endl;
    mkdir(dir_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);        // 'S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH' gives the directory default permisions.
    chdir(dir_name.c_str());
    getline(vfsf_file, line);
    while(line != "ENDDIR"){
        if(line.substr(0, 4) == "FILE"){
            file_name = line.substr(5, line.length() - 5);                 // Assumes the files name is 5 char's into the string.
            build_file(file_name, vfsf_file);
        } else if(line.substr(0, 9) == "DIRECTORY"){
            subdir_name = line.substr(10, line.length() - 10);             // Assumes directories name is 10 char's into the string.
            build_directory(subdir_name, vfsf_file);
        }
        getline(vfsf_file, line);
    }
    chdir("..");
}

void unpack(std::string vfsf_file_name){
    std::ifstream vfsf_file;
    std::string line, file_name, dir_name;
    vfsf_file.open(vfsf_file_name);
    while(getline(vfsf_file, line)){
        if(line.substr(0, 4) == "FILE"){
            file_name = line.substr(5, line.length() - 5);                 // Assumes the files name is 5 char's into the string.
            build_file(file_name, vfsf_file);
        } else if(line.substr(0, 9) == "DIRECTORY"){
            dir_name = line.substr(10, line.length() - 10);                // Assumes directories name is 10 char's into the string.
            build_directory(dir_name, vfsf_file);
        }
    }
    vfsf_file.close();
}