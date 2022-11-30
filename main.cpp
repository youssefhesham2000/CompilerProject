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


    string s = "a-z";
    cout << s << endl;
    s = RegExp::removeLeadingAndTrailingSpaces(s);
    vector<string> operands = RegExp::getRange(s);
    RegExp r(s);
    cout << r.type<< endl;
    for (const string& s: operands){
        cout << s << endl;
    }

    return 0;

}
