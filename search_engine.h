#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

template <typename Type>
struct IndexedElement {
    typedef typename std::vector<Type>::iterator ptr;
    std::vector<ptr> indexes;
    Type value;
};

class SearchEngine {
    public:
        typedef IndexedElement<std::string> indexedElement;
    private:
        bool isIndexed;
        std::vector<indexedElement> indexedWords;
        std::vector<std::string> texts;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(std::string text);
        bool BuildIndexes();
        std::vector<std::string> Search(std::string text);
};

#endif
