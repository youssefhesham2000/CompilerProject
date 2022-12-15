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
    auto res = minimizedDFA->accept(string("int n = 3\n")
                                    + "float f = 56.7;\n"
                                    + "float f2 = 5.67E1\n"
                                    + "x x,x 5 n \n"
                                    + "if (f >50) { f = f2 / 2}\n"
                                    + "else { f = f2 * 2}\n"
                                    + "int x = 70 e b);\n"
                                    + "int x = 70e;\n"
                                    + "int x = 70&y;\n"
                                    + "boolean x = false \n"
                                    + "boolean x = 0\n"
                                    );
    for (auto token: res) {
        if (token.type != "")
            cout << token.type << " " << token.value << endl;
    }

    return 0;

}
