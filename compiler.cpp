#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"

using namespace std;

bool has_file_extension(const string &file_name, const string &file_type);
string create_timestamp();
Lexer lex;

int main() {
    ifstream input_file;
    ofstream output_file;
    string input_file_name, input_file_path = "tests/";
    string output_file_name, output_file_path = "results/";
    
    cout << "Input the file name: ";
    cin >> input_file_name;
    
    cout << "Verifying the file name..." << endl;
    if (!has_file_extension(input_file_name, "txt")) {
        cout << "File does not have the txt extension." << endl;
        exit(-1);
    }
    
    cout << "Opening the file..." << endl;
    input_file_path.append(input_file_name);
    input_file.open(input_file_path);
    if (!input_file.is_open()) {
        cout << "There was an error opening the file." << endl;
        exit(-1);
    }
    
    cout << "Creating the results file..." << endl;
    output_file_name = create_timestamp();
    output_file_name.append(".txt");
    output_file_path.append(output_file_name);
    output_file.open(output_file_path);
    if (!output_file.is_open()) {
        cout << "There was an error creating and opening the results file." << endl;
        exit(-1);
    }

    // Temporary code to test the tokenize() function.
    lex.tokenize(input_file);
    
    // Temporary code to test reading and writing files.
    cout << "Writing to the results file..." << endl;
    string line;
    while (getline(input_file, line)) {
        output_file << line;
    }
    output_file.close();
    input_file.close();
    
    cout << "Results file: " << output_file_name << endl;

    // Printing out results
    lex.results(output_file);

    // Temporary code to test is_identifier FSM.
    cout << "DEBUG IS_IDENTIFIER()" << endl;
    cout << lex.is_identifier("As514127_") << endl;
    cout << lex.is_identifier("v812_1ajhs") << endl;
    cout << lex.is_identifier("5shAn31_") << endl;
    cout << lex.is_identifier("A&sna2") << endl;

    // Temporary code to test is_integer FSM.
    cout << "DEBUG IS_INTEGER()" << endl;
    cout << lex.is_integer("199278172") << endl;
    cout << lex.is_integer("012381221") << endl;
    cout << lex.is_integer("612cnas12") << endl;
    cout << lex.is_integer("667810%05") << endl;

    // Temporary code to test is_real FSM.
    cout << "DEBUG IS_REAL()" << endl;
    cout << lex.is_real("199278172.128212") << endl;
    cout << lex.is_real("528581231.058212") << endl;
    cout << lex.is_real("012381221.128621") << endl;
    cout << lex.is_real("018636623.024812") << endl;
    
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
    strftime(time_cstr, 500, "%H-%M-%S-%F", time_info);
    
    string file_name;
    file_name.append(time_cstr);
    
    return file_name;
}

