#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class SearchEngine {
    private:
        struct IndexedWord {
            vector<unsigned int> offsets;
            string word;
        };

        bool isLocked;
        vector<IndexedWord> indexedWords;
        vector<string> texts;
    public:
        SearchEngine();
        ~SearchEngine();

        bool AddText(string text);
        bool BuildIndexes();
        vector<string> *Search(string text);
};

#endif
