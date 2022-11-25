#include <string>
#include "lexicalRulesParser.h"


using namespace std;


int main(int argc, char **argv) {
    //"D:\\rules.txt"
    string lexicalRulesInputFilePath = argv[1];
    parseInputFile(lexicalRulesInputFilePath);

    return 0;

}
