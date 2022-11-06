// Main function for SOA implementation
#include "../common/progargs.hpp"
#include "../soa/imagesoa.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>

using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(int argc, char *argv[]){
    const std::filesystem::path src = argv[1], dst = argv[2];
    string oper = argv[3];
    if(error_check(argc,src,dst,oper))  return -1;
    vector <string> files;
    get_files(src, files);
        for(int i=0; i < static_cast<int>(files.size()); ++i){
            colors clrs;
            if(oper == "histo")
                main_histo(files[i], src, dst);
            else if(oper == "gauss")
                main_gauss(files[i], src, dst, clrs);
            else if(oper == "copy")
                main_copy(files[i], src, dst, clrs);
            else if(oper == "mono")
                main_mono(files[i], src, dst, clrs);
        }
    return 0;
}

