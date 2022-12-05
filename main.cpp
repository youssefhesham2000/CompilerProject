#include <string>
#include "RulesParser.h"
#include "RegExp.h"
#include "NFA.h"
#include "NFAConvertor.h"
#include "DFANode.h"
using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    // Use the run configuration "Run on rules.txt"
    //string lexicalRulesInputFilePath = argv[1];

    string lexicalRulesInputFilePath ="D:\\College\\4th year - 1st semester\\Compilers\\CompilerProject\\rules.txt";
    //RulesParser parser;
    //parser.parseInputFile(lexicalRulesInputFilePath);
    RegExp test = RegExp::parseRegExp(" (A)*");
    vector<std::string> t = test.toString();
        for (auto &it2 : t) {
            cout << it2 << '\n';
        }
        NFA nfa = NFA(test, "testType");
        NFAConvertor r;
        DFANode te = r.convert(nfa.startNode);
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
