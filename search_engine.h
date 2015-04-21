#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

template <typename Type>
struct IndexedElement {
    typedef typename vector<Type>::iterator pointer;
    vector<pointer> pointers;
    Type value;
};

class SearchEngine {
    public:
        typedef IndexedElement<string> indexedElement;
    private:
        bool isIndexed;
        vector<indexedElement> indexedWords;
        vector<string> texts;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(string text);
        bool BuildIndexes();
        vector<string> *Search(string text);
};

#endif
