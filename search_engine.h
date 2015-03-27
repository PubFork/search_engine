#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "index_list.h"
#include <string>

using namespace std;

struct SearchElement {
    char *acWord;
    IndexList *pIndexes;
};

struct TextElement {
    string sText;
    TextElement *pNext;
};

class SearchEngine {
    private:
        bool bIsIndexed;
        string *pTextArray;        
        SearchElement *pIndexTable;
        TextElement *pTextList, *pCurrentText;
        unsigned int uiTextCount, uiWordCount;
    public:
        SearchEngine();
        ~SearchEngine();
        
        bool AddText(string sText);
        bool BuildIndexes();    
        unsigned int Search(string sText, string **pStrings);
};

#endif
