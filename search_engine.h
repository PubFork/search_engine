#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

struct IndexedElement {
    typedef vector<string>::iterator pointer;
    vector<pointer> pointers;
    string value;
};

class SearchEngine {
    private:
        bool isIndexed;
        vector<IndexedElement> indexedWords;
        vector<string> texts;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(string text);
        bool BuildIndexes();
        vector<string> *Search(string text);
};

#endif
