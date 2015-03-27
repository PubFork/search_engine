#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

template <typename Type>
struct IndexedElement {
    typedef typename std::vector<Type>::iterator index;
    std::vector<index> indexes;
    Type value;
};

class SearchEngine {
    private:
        bool isIndexed;
        std::vector<IndexedElement<std::string> > indexedWords;
        std::vector<std::string> texts;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(std::string text);
        bool BuildIndexes();
        std::vector<std::string> Search(std::string text);
};

#endif
