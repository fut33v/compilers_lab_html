#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include "cproduction.h"

namespace parser{
    enum stackSymbols {
        HTML,
        WebpageBody,
        Head,
        HeadItems,
        HeadItem,
        Body,
        Content,
        Parameters,
        Parameter1,
        Parameter2,
        Parameter,
        Tag,
        Word,
        BottomMarker,
        oHtml, //<html
        oHead, //<head
        oTitle, //<title e.t.c
        oMeta,
        oLink,
        oBase,
        oBasefont,
        oBody,
        oImg,
        oBr,
        oP,
        oH1,
        oH2,
        oH3,
        cHtml, //</html> and so on
        cHead,
        cTitle,
        cBody,
        cH1,
        cH2,
        cH3,
        cP,
        tAbove, //CLASS_CLOSING_BRACE
        tId, //CLASS_ID
        tEqual, //CLASS_EQUAL
        tInt, //CLASS_INT
        tColor, //CLASS_COLOR
        tString //CLASS_STRING
    };
}

#endif // TOKEN_H
