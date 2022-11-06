#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

struct colors{
    vector<uint8_t> b;
    vector<uint8_t> g;
    vector<uint8_t> r;
};

// main handling for copy function
void main_copy(string file_name, string src, string dst, colors &clrs);

// main handling for gauss function
void main_gauss(string file_name, string src, string dst, colors &clrs);

// main handling for mono function
void main_mono(string file_name, string src, string dst, colors &clrs);