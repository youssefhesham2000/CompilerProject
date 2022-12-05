#include <string>
#include "RulesParser.h"
#include "RegExp.h"
#include "NFA.h"
#include "NFAConvertor.h"
#include "DFANode.h"
#include "RegExpGenerator.h"
using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    // Use the run configuration "Run on rules.txt"
    //string lexicalRulesInputFilePath = argv[1];

    string lexicalRulesInputFilePath ="D:\\rules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
    RegExp temp = parsedRegExp["id"];
    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
    cout<<"test"<<endl;


    //    for (auto &it : parser.keyWords) {
//        RegExp::parseKeyWord(it);
//        //cout << it << '\n';
//    }

//    vector<std::string>res=  test.toString();
//    for (auto &it : res) {
//        cout << it << endl;
//    }
//    string s = "a-z";
//    cout << s << endl;
//    s = RegExp::removeLeadingAndTrailingSpaces(s);
//    vector<string> operands = RegExp::getRange(s);
//    RegExp r = RegExp::parseRegExp(s);
//    cout << r.type<< endl;
//    for (const string& s: operands){
//        cout << s << endl;
//    }

    return 0;

}
