#include "mathParser.h"

int main()
{
    MathParser* mathparser = new MathParser();
    mathparser->parseString("(2+2)*2+5-2/6*(42+9)");

    return 0;
}