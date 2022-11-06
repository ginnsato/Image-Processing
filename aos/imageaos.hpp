#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>


struct color{
    uint8_t b,g,r;
};

using namespace std;

// main handling for copy function
void main_copy(string file_name, string src, string dst, vector <color> &colors);

// main handling for gauss function
void main_gauss(string file_name, string src, string dst, vector <color> &colors);

// main handling for mono function
void main_mono(string file_name, string src, string dst, vector <color> &colors);





