#include <string>
#include "RulesParser.h"
#include "RegExp.h"
#include "NFA.h"
#include "NFAConvertor.h"
#include "DFANode.h"
#include "RegExpGenerator.h"
#include "SubsetConstructor.h"
#include "DFA.h"
#include "Minimizer.h"

using namespace std;


int main(int argc, char **argv) {

    string lexicalRulesInputFilePath ="D:\\College\\4th year - 1st semester\\Compilers\\CompilerProject\\rules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);
    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
    DFANode* dfaNode = SubsetConstructor::construct(combinedNfa, parser);
    DFA dfa(dfaNode);
    DFA* minimizedDFA = (new Minimizer())->minimize(&dfa);
    auto res = minimizedDFA->accept("int aab , bba , b10 , a; while (bb !=10){bb =bb +1;} if hello&");
    for (auto token: res) {
        if (token.type != "")
            cout << token.type << " " << token.value << endl;
    }

    return 0;

}
