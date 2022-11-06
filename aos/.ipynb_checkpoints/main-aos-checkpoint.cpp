// Main function for AOS implementation
#include "../common/progargs.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(int argc, char *argv[]){

    const std::filesystem::path src = argv[1];
    const std::filesystem::path dst = argv[2];
    string oper = argv[3];

    vector <string> files;

    for (const auto& dirEntry : recursive_directory_iterator(argv[1]))
        files.push_back(dirEntry.path());

    for(int i=0; i < files.size(); ++i){
        is_bmp_valid(files[i]);
    }

    if(oper == "copy"){
        copy(src, dst);
    }

    else if(oper == "histo"){
        for(int i=0; i < files.size(); ++i){
            histo(files[i], argv[1], argv[2]);
        }
    }
/*
    else if(oper == "mono"){
        for(int i=0; i < files.size(); ++i){
            histo(files[i]);
        }
    }

    else if(oper == "guass"){
        for(int i=0; i < files.size(); ++i){
            guass(files[i]);
        }
    }
*/
    return 1;
}

