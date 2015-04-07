#include "search_engine.h"
#include <string.h>
#include <sstream>
#include <iostream>

SearchEngine::SearchEngine() {
    isIndexed = false;
}

SearchEngine::~SearchEngine() {
}

bool SearchEngine::AddText(std::string text) {
    if (isIndexed) {
        return false;
    }
    texts.push_back(text);
    return true;
}

bool SearchEngine::BuildIndexes() {
    if (isIndexed) {
        return false;
    }

    for (indexedElement::ptr i = texts.begin(); i != texts.end(); i++) {
        std::string word;
        std::stringstream ss(*i);

        while (ss >> word) {
            bool add = true;
            std::vector<indexedElement>::iterator j;
            for (j = indexedWords.begin(); j != indexedWords.end(); j++) {
                if (j->value == word) {
                    j->indexes.push_back(i);
                    add = false;
                    break;
                }
                if (word < j->value) {
                    break;
                }
            }
            if (add) {
                indexedElement element;
                element.value = word;
                element.indexes.push_back(i);
                indexedWords.insert(j, element);
            }
        }
    }

    isIndexed = true;
    return true;
}

std::vector<std::string> *SearchEngine::Search(std::string text) {
    std::string word;
    std::stringstream ss(text);
    std::vector<std::string> *results = new std::vector<std::string>();

    while (ss >> word) {
        unsigned int begin = 0, end = indexedWords.size() - 1;
        while (begin != end) {
            unsigned int offset = (begin + end) >> 1;
            std::string check = indexedWords[offset].value;
            if (check < word) {
                begin = offset + 1;
            } else {
                end = offset;
            }
        }
        if (indexedWords[begin].value == word) {
            indexedElement *element = &indexedWords[begin];
            for (std::vector<indexedElement::ptr>::iterator i = element->indexes.begin(); i != element->indexes.end(); i++) {
                results->push_back(*(*i));
            }
        }
    }

    return results;
}
