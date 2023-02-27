#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"

using namespace std;

bool has_file_extension(const string &file_name, const string &file_type);
string create_timestamp();

int main() {
    Lexer lexer;
    ifstream input_file;
    ofstream output_file;
    string input_file_name, input_file_path = "tests/";
    string output_file_name, output_file_path = "results/";

    cout << "Input the source file name: ";
    cin >> input_file_name;
    
    cout << "Verifying the source file name..." << endl;
    if (!has_file_extension(input_file_name, "txt")) {
        throw runtime_error("ERROR: Source file must have a .txt extension.\n");
    }
    
    cout << "Opening the source file..." << endl;
    input_file_path.append(input_file_name);
    input_file.open(input_file_path);
    if (!input_file.is_open()) {
        throw runtime_error("ERROR: Source file could not be opened.\n");
    }

    cout << "Tokenizing the source file..." << endl;
    lexer.tokenize(input_file);
    
    cout << "Opening the results file..." << endl;
    output_file_name = create_timestamp() + ".txt";
    output_file_path.append(output_file_name);
    output_file.open(output_file_path);
    if (!output_file.is_open()) {
        throw runtime_error("ERROR: Results file colud not be opened.\n");
    }
    
    cout << "Writing to the results file..." << endl;
    lexer.results(output_file);
    
    cout << "Results file: " << output_file_name << endl;
    output_file.close();
    input_file.close();
    
    return 0;
}

bool has_file_extension(const string &file_name, const string &file_type) {
    size_t extension_index = file_name.find_last_of(".");
    string extension = file_name.substr(extension_index + 1);
    
    if (extension_index == string::npos) {
        return false;
    }
    
    if (extension != file_type) {
        return false;
    }
    
    return true;
}

string create_timestamp() {
    time_t raw_time;
    struct tm* time_info;
    char time_cstr[500];

    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(time_cstr, 500, "%m-%d-%Y_%H-%M-%S", time_info);
    
    string file_name;
    file_name.append(time_cstr);
    
    return file_name;
}

