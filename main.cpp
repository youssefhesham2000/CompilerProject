#include <string>
#include "RulesParser.h"
#include "RegExp.h"


using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    //string lexicalRulesInputFilePath = argv[1];
    string lexicalRulesInputFilePath ="D:\\rules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);


    string s = "letter (letter|digit)*";
    vector<string> operands = RegExp::getTopLevelConcatenation(s);
    for (const string& s: operands){
        cout << s << endl;
    }

    return 0;

}
