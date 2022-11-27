#include <string>
#include "RulesParser.h"


using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    //string lexicalRulesInputFilePath = argv[1];
    string lexicalRulesInputFilePath ="D:\\rules.txt";
    RulesParser parser;
    parser.parseInputFile(lexicalRulesInputFilePath);

    return 0;

}
