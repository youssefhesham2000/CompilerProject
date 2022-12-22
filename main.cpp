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

string lexicalRulesInputFilePath ="D:\\rules.txt";
string CFGRulesPath = "D:\\CFGRules.txt";

vector<Token> getTokens() {
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
    DFANode* dfaNode = SubsetConstructor::construct(combinedNfa, parser);
    DFA dfa(dfaNode);
    DFA* minimizedDFA = (new Minimizer())->minimize(&dfa);
    auto res = minimizedDFA->accept(string("int n = 3\n")
                                    +"float f = 56.7;\n"
                                    +"float f2 = 5.67E1\n"
                                    +"x x,x 5 n \n"
                                    +"if (f >50) { f = f2 / 2}\n"
                                    +"else { f = f2 * 2}\n"
                                    +"\n"
                                    +"int x = 70 e b);\n"
                                    +"\n"
                                    +"int x = 70e;\n"
                                    +"int x = 70&y;\n"
                                    +"\n"
                                    +"boolean x = false \n"
                                    +"\n"
                                    +"boolean x = 0");
    vector<Token> ans;
    for (auto token: res) {
        if (token.value != "")
            ans.push_back(token);
    }
    return ans;
}

int main(int argc, char **argv) {
    for (auto& t: getTokens()) {
        cout << t.type << "\t" << t.value << endl;
    }

    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    parser.parseCFGRules(CFGRulesPath);
    string RHS = parser.CFGRules.find("STATEMENT")->second;
    Production production =  Production::parseProduction(RHS);

    return 0;

}
