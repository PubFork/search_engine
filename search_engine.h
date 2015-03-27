#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "index_list.h"
#include <string>

struct SearchElement {
    char *acWord;
    IndexList *pIndexes;
};

struct TextElement {
    std::string sText;
    TextElement *pNext;
};

class SearchEngine {
    private:
        bool bIsIndexed;
        std::string *pTextArray;
        SearchElement *pIndexTable;
        TextElement *pTextList, *pCurrentText;
        unsigned int uiTextCount, uiWordCount;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(std::string sText);
        bool BuildIndexes();
        unsigned int Search(std::string sText, std::string **pStrings);
};

#endif
