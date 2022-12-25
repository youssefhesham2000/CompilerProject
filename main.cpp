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
#include "Phase2/SetBuilder.h"
#include "Phase2/ParsingTable.h"
#include "Phase2/Parser.h"
#include "Phase2/LeftRecursion.h"
using namespace std;

string lexicalRulesInputFilePath = "D:\\rules.txt";
string CFGRulesPath = "D:\\CFGRules.txt";

//void printSet(SetMap st, string title) {
//    cout << title << endl;
//    for (const auto &x: st) {
//        cout << x.first.symbol << ": ";
//        for (const auto &s: x.second) {
//            cout << s.symbol << ", ";
//        }
//        cout << endl;
//    }
//}
//
//vector<Symbol> getTokens() {
//    RulesParser parser;
//    parser.parseInputFile(lexicalRulesInputFilePath);
//    RegExpGenerator generator = RegExpGenerator(parser.regularDefinitions);
//    map<string, RegExp> parsedRegExp = generator.generateAllExpressions(parser);
//    NFA combinedNfa = NFA::constructCombinedNFA(parsedRegExp);
//    DFANode *dfaNode = SubsetConstructor::construct(combinedNfa, parser);
//    DFA dfa(dfaNode);
//    DFA *minimizedDFA = (new Minimizer())->minimize(&dfa);
//    auto res = minimizedDFA->accept("int x;x=5;if(x>2){x=0;}else{x=1;}");
//    vector<Symbol> ans;
//    for (auto token: res) {
//        if (token.value != "")
//            ans.emplace_back(token.type, SymbolType::terminal);
//    }
//    ans.push_back(endOfParsingSymbol);
//    return ans;
//}
void printRules(unordered_map<Symbol, Production *> rules){
    for (auto rule:rules) {
        cout<< rule.first.symbol<<" = ";
        vector<vector<Symbol>> productions = rule.second->productions;
        for (int i = 0; i < productions.size(); ++i) {
            for (int j = 0; j < productions[i].size(); ++j) {
                cout<< productions[i][j].symbol<<" ";
            }
            if(i !=productions.size()){
                cout<<"|"<<" ";
            }

        }
    cout<<" "<<endl;
    }
}
int main(int argc, char **argv) {
//    for (auto& t: getTokens()) {
//        cout << t.symbol << endl;
//    }

    RulesParser parser;
//    parser.parseInputFile(lexicalRulesInputFilePath);
    parser.parseCFGRules(CFGRulesPath);
    unordered_map<Symbol, Production *> rules;
    unordered_map<std::string, Production *> lhsStringRules;
    vector<std::string> LHS;
    vector<Symbol> nonTerminals;
    for (const auto &rule: parser.CFGRules) {
        Symbol s = Symbol(rule.first, SymbolType::nonTerminal);
        nonTerminals.push_back(s);
        LHS.emplace_back(rule.first);
        lhsStringRules[rule.first] = new Production(Production::parseProduction(rule.second));
        rules[s] = new Production(Production::parseProduction(rule.second));
    }
    LeftRecursion l;
     rules = l.eliminateLeftRecursion(lhsStringRules, LHS);
//    for (const auto &nonTerminal: nonTerminals)
//        getFirstSet(nonTerminal, rules);
//    followSet[Symbol("METHOD_BODY", SymbolType::nonTerminal)].insert(endOfParsingSymbol);
//    initFollowSet(rules);
//
////    printSet(firstSet, "First Set: ");
//    printSet(followSet, "Follow Set: ");
//    ParsingTable p = ParsingTable::generateParsingTable(rules, firstSet, followSet);
//    p.print();

//    vector<Symbol> test;
//    test.emplace_back("id", SymbolType::terminal);
//    test.emplace_back("+", SymbolType::terminal);
//    test.emplace_back("id", SymbolType::terminal);
//    test.emplace_back("*", SymbolType::terminal);
//    test.emplace_back("id", SymbolType::terminal);
//    test.push_back(endOfParsingSymbol);

    //Parser::match(p, getTokens(), Symbol("METHOD_BODY", SymbolType::nonTerminal), followSet);
    printRules(rules);
    cout<<":test"<<endl;
    return 0;

}
