#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

string justify(vector<string> words, int width, string mode) {
    if (words.empty()) {
        return "";
    }
    if (words.size() == 1) {
        return words[0] + string(width - words[0].length(), ' ');
    }

    int numSpaces = words.size() - 1;
    int totalChars = 0;
    for (string word : words) {
        totalChars += word.length();
    }
    int totalSpaces = width - totalChars;

    int spacesBetweenWords = totalSpaces / numSpaces;
    int extraSpaces = totalSpaces % numSpaces;

    string line;
    if (mode == "flush_left") {
        line = words[0];
        for (int i = 1; i < words.size(); i++) {
            line += ' ' + words[i];
        }
        line += string(width - line.length(), ' ');
    }
    else if (mode == "flush_right") {
        line = string(width - totalChars, ' ') + words[0];
        for (int i = 1; i < words.size(); i++) {
            line += ' ' + words[i];
        }
    }
    else if (mode == "full_justify") {
        line = words[0];
        for (int i = 1; i < words.size(); i++) {
            int numSpacesToAdd = spacesBetweenWords;
            if (extraSpaces > 0) {
                numSpacesToAdd++;
                extraSpaces--;
            }
            line += string(numSpacesToAdd, ' ') + words[i];
        }
        line += string(width - line.length(), ' ');
    }

    return line;
}

int main(int argc, char* argv[]) {
    // check command line arguments
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file> <width> <justification_mode>" << endl;
        return 1;
    }

    // open input file
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    // open output file
    ofstream out(argv[2]);
    if (!out) {
        cerr << "Unable to open output file: " << argv[2] << endl;
        return 1;
    }

    // parse width argument
    int width = atoi(argv[3]);
    if (width <= 0) {
        cerr << "Invalid width: " << argv[3] << endl;
        return 1;
    }

    // parse justification mode argument
    string mode(argv[4]);
    if (mode != "flush_left" && mode != "flush_right" && mode != "full_justify") {
        cerr << "Invalid justification mode: " << argv[4] << endl;
        return 1;
    }

    // read words from input file
    vector<string> words;
    string word;
    while (in >> word) {
        words.push_back(word);
    }

    // justify text
    string justified_text = justify(words, width, mode);

    // write output to file
    out << justified_text;

    // close files
    in.close();
    out.close();

    return 0;
}
