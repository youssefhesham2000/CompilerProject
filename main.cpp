#include <string>
#include "Phase1/RulesParser.h"
#include "Phase1/RegExp.h"
#include "Phase1/NFA.h"
#include "Phase1/NFAConvertor.h"
#include "Phase1/DFANode.h"
#include "Phase1/RegExpGenerator.h"
#include "Phase1/SubsetConstructor.h"
#include "Phase1/DFA.h"
#include "Phase1/Minimizer.h"
#include "Phase2/Production.h"
using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    // Use the run configuration "Run on rules.txt"
    //string lexicalRulesInputFilePath = argv[1];

    string lexicalRulesInputFilePath ="D:\\rules.txt";
    string CFGRulesPath = "D:\\CFGRules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    parser.parseCFGRules(CFGRulesPath);
    string RHS = parser.CFGRules.find("STATEMENT")->second;
    Production production =  Production::parseProduction(RHS);
    cout<< " test"<< endl;
//    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
//    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
//    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
//    for (auto entry: parsedRegExp){
//        std::cout << "Construction of: " << entry.first << std::endl;
//        NFA nfa(entry.second, entry.first);
//        //nfa.print();
//    }
//
//    DFANode* dfaNode = SubsetConstructor::construct(combinedNfa);
//    DFA dfa(dfaNode);
//    DFA* minimizedDFA = (new Minimizer())->minimize(&dfa);
//    auto res = minimizedDFA->accept("int n = 3\n"
//                                    +"float f = 56.7;\n"
//                                    +"float f2 = 5.67E1\n"
//                                    +"x x,x 5 n \n"
//                                    +"if (f >50) { f = f2 / 2}\n"
//                                    +"else { f = f2 * 2}\n"
//                                    +"\n"
//                                    +"int x = 70 e b);\n"
//                                    +"\n"
//                                    +"int x = 70e;\n"
//                                    +"int x = 70&y;\n"
//                                    +"\n"
//                                    +"boolean x = false \n"
//                                    +"\n"
//                                    +"boolean x = 0");
//    //    auto res = dfa.accept("int aab , bba , b10 , a; while (bb !=10){bb =bb +1;}");
//    for (auto token: res) {
//        cout << token.type << " " << token.value << endl;
//    }
    for(auto it: parser.keyWords){
        cout<<it<<endl;
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
