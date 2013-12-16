#include <iostream>
#include "scanner/ctokensflow.h"
#include "scanner/ctoken.h"
#include "scanner/ccode.h"
#include "scanner/cscanner.h"
#include "cllparser.h"
#include "parser.h"

int main(){
    scanner::cTokensFlow tokensFlow;
    scanner::cScanner scanner("test.html", &tokensFlow);
    scanner.startScanning();
    parser::cLLParser parser (&tokensFlow, "table");
    //parser.showTable();
    parser.startParsing();
    return 0;
}
