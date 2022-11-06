#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
<<<<<<< HEAD

#include "../common/progargs.hpp"
=======
#include <chrono>
#include "progargs.hpp"
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6

using namespace std;

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
<<<<<<< HEAD

void get_dimensions(string name, int &start, int &width, int &height, int &padding){
    unsigned char header[54];               // define header
    FILE *fp = fopen(name.c_str(), "rb");   // open file

    fread(header, sizeof(header), 1, fp);   // read header
    fclose(fp);

    // calculate the following values
    start = header[10] + (header[11] << 8) + (header[12] << 16) + (header[13] << 24);
    width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
    padding = ((4 - (width * 3) % 4) % 4);

}

int is_bmp_valid(string name){

    unsigned char header[54];
    FILE *fp = fopen(name.c_str(), "rb");                       // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array
    fclose(fp);                                                 // done using file here

    int num_planes = header[26] + (header[27] << 8);            // read number of planes
    int size_point = header[28]; + (header[29] << 8);            // read size of each point
    int compression = header[30]; + (header[31] << 8) + (header[32] << 16) + (header[33] << 24);

    if(header[0] != 'B' || header[1] != 'M'|| num_planes != 1 || size_point != 24 || compression != 0){
        return 0;           // bmp file is not valid, return 0
    }
    return 1;               // bmp file is valid 
=======

int print_error(){
    cout << "\t" << "./build/image-aos in_path out_path oper\n";
    cout << "\t\t" << "operation: copy, histo, mono, gauss\n";
    return 1;
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6
}


int error_check(int argc, string src, string dst, string oper){
    if(argc != 4){
        cout << "Wrong format:\n";
        return print_error();
    }
    if(oper != "copy" && oper != "histo" && oper != "mono" && oper != "gauss"){
        cout << "Unexpected operation: " << oper << endl;
        return print_error();
    }
    cout << "Input path: " << src << endl;
    cout << "Output path: " << dst << endl;
    if(!filesystem::exists(src)){
        cout << "Cannot open directory: [" << src << "]\n";
        return print_error();
    }
    if(!filesystem::exists(dst)){
        cout << "Output directory [" << dst << "] does not exist\n";
        return print_error();
    }
    return 0;
}

<<<<<<< HEAD
void write_array(ofstream &hst, int arr[256]){
    for(int i = 0; i < 256; i++)
        hst << arr[i] << endl;
}


// 24 lines without any blank lines
void histo(string name, string src, string dst){
    int r_vals[256], g_vals[256], b_vals[256], start, width, height, padding;
    unsigned char c[3];
    for(int r=0; r < 256; r++)
        r_vals[r] = g_vals[r] = b_vals[r] = 0;
    get_dimensions(name, start, width, height, padding);
    FILE *fp = fopen(name.c_str(), "rb");
    fseek(fp, start, 0);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(c, sizeof(c), 1, fp);         // read color's rgb values
            b_vals[c[0]]++;                     // iterate value 
            g_vals[c[1]]++;                     
            r_vals[c[2]]++; 
            fseek(fp,3,SEEK_CUR);               // move fp
=======

void get_files(string src, vector <string> &files){
    for (const auto& dirEntry : recursive_directory_iterator(src)){
        if(is_bmp_valid(dirEntry.path()))
            files.push_back(dirEntry.path());
        else cout << "Invalid BMP File: " << dirEntry.path() << endl;
    }
}


void get_dimensions(string name, int &start, int &width, int &height){
    unsigned char header[54];               
    FILE *fp = fopen(name.c_str(), "rb");  
    fread(header, sizeof(header), 1, fp);   
    fclose(fp);
    start = header[10]+ (header[11] << 8) + (header[12] << 16) + (header[13] << 24);
    width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
}


int is_bmp_valid(string name){
    unsigned char header[54];
    FILE *fp = fopen(name.c_str(), "rb");                       
    fread(header, sizeof(header), 1, fp);
    fclose(fp);                                                 
    int num_planes = header[26] + (header[27] << 8);           
    int size_point = header[28] + (header[29] << 8);            
    int compression = header[30] + (header[31] << 8) + (header[32] << 16) + (header[33] << 24);
    if(header[0] != 'B' || header[1] != 'M'|| num_planes != 1 || size_point != 24 || compression != 0)
        return 0;
    return 1;               
}


int histo_write(ofstream &hst, int (&arr)[256]){
    auto write_start = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 256; i++)
        hst << arr[i] << endl;
    auto write_stop = chrono::high_resolution_clock::now(); 
    auto write_t = duration_cast<chrono::microseconds>(write_stop - write_start);
    return static_cast<int>(write_t.count());
}


int histo_read(string file_name, vector <unsigned char> &color_bytes){
    int start, width, height, padding;
    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;
    int size_arr = height*(3*(width)+padding);
    color_bytes.resize(size_arr); 
    auto load_start = chrono::high_resolution_clock::now(); 
    FILE *fp = fopen(file_name.c_str(), "rb");
    fseek(fp, start, SEEK_SET);
    fread(static_cast<void*>(&color_bytes[0]), 1, size_arr, fp);
    fclose(fp);
    auto load_stop = chrono::high_resolution_clock::now(); 
    auto load_t = duration_cast<chrono::microseconds>(load_stop - load_start);
    return static_cast<int>(load_t.count());
}


int histo(string file_name, string src, string dst, vector <unsigned char> &color_bytes){
    int r_vals[256], g_vals[256], b_vals[256], start, width, height, padding ;
    for(int r=0; r < 256; r++)
        r_vals[r] = g_vals[r] = b_vals[r] = 0;
    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            b_vals[color_bytes[y*((3*width)+padding) + 3*x]]++;   
            g_vals[color_bytes[y*((3*width)+padding) + 3*x + 1]]++;
            r_vals[color_bytes[y*((3*width)+padding) + 3*x + 2]]++;
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6
        }
    }
<<<<<<< HEAD
    fclose(fp);

    ofstream hst(dst + "/" + name.substr(src.size()+1,name.size()-src.size()-4)+"hst");                     // create ofstream called hst

    write_array(hst, r_vals);
    write_array(hst, g_vals);
    write_array(hst, b_vals);   

    hst.close();

}


/*
int main(){
    histo("images/balloon.bmp", "images", "test_out");

    
    vector <string> files;


    for (const auto& dirEntry : recursive_directory_iterator("images"))
        files.push_back(dirEntry.path());

    for(int i=0; i < files.size(); ++i){
        cout << files[i] << endl;
    }
    return 0;
    
} 
*/


=======
    ofstream hst(dst + "/" + file_name.substr(src.size()+1,file_name.size()-src.size()-4)+"hst"); 
    int write_t = histo_write(hst, r_vals);
    write_t += histo_write(hst, g_vals);
    write_t += histo_write(hst, b_vals);  
    hst.close();
    return write_t;
}


void main_histo(string file_name, string src, string dst){
    vector <unsigned char> color_bytes;
    int read_t = histo_read(file_name, color_bytes);
    auto oper_start = chrono::high_resolution_clock::now();
    int  write_t = histo(file_name, src, dst, color_bytes);
    auto oper_stop = chrono::high_resolution_clock::now();
    auto oper = duration_cast<chrono::microseconds>(oper_stop - oper_start);
    int oper_and_write_t = static_cast<int>(oper.count());
    int oper_t = oper_and_write_t - write_t;
    int total_t = oper_and_write_t + read_t;
    cout << "File: " << src << "/" << file_name << "(time: " << total_t << ")\n";
    cout << "\tLoad Time: " << read_t << endl;
    cout << "\tHisto Time: " << oper_t << endl;
    cout << "\tStore Time: " << write_t << endl;
}
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6
