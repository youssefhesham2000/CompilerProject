#include <string>
#include "RulesParser.h"
#include "RegExp.h"
#include "NFA.h"
#include "NFAConvertor.h"
#include "DFANode.h"
#include "RegExpGenerator.h"
#include "SubsetConstructor.h"
#include "DFA.h"

using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    // Use the run configuration "Run on rules.txt"
    //string lexicalRulesInputFilePath = argv[1];

    string lexicalRulesInputFilePath ="D:\\College\\4th year - 1st semester\\Compilers\\CompilerProject\\rules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
    for (auto entry: parsedRegExp){
        std::cout << "Construction of: " << entry.first << std::endl;
        NFA nfa(entry.second, entry.first);
        //nfa.print();
    }

    DFANode* dfaNode = SubsetConstructor::construct(combinedNfa);
    DFA dfa(dfaNode);
    auto res = dfa.accept("10 bb10101");
    for (auto token: res) {
        cout << token.type << " " << token.value << endl;
    }

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
