#include "command.h"

#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

void Command::setInput() {
    command.clear(); // Empties command vector of previous commands
    std::cout << "> ";             // Input field
    std::getline(std::cin, input); // Take in input from entire line
    std::stringstream untokenizedInput(input); // Convert the input to a stringstream to tokenize input
    std::string token; // Temp variable that will store the individual tokens of the input

    while (untokenizedInput >>token) { // While loop that pushes each token to the end of the list

        std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               return std::tolower(c);
                           }); // Transforms the token to lowercase

        command.push_back(token); // Appends a the lowercased token to the end of the list
                                  // tokens for the command parser to read.
        }
}

vector<string> Command::getInput() { return command; }