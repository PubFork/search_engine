#include "search_engine.h"
#include <sstream>
#include <iostream>

using std::stringstream;

SearchEngine::SearchEngine() : isIndexed(false) {
}

SearchEngine::~SearchEngine() {
}

bool SearchEngine::AddText(string text) {
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

    for (indexedElement::pointer i = texts.begin(); i != texts.end(); i++) {
        string word;
        stringstream ss(*i);

        while (ss >> word) {
            bool add = true;
            vector<indexedElement>::iterator j;
            for (j = indexedWords.begin(); j != indexedWords.end(); j++) {
                if (j->value == word) {
                    j->pointers.push_back(i);
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
                element.pointers.push_back(i);
                indexedWords.insert(j, element);
            }
        }
    }

    isIndexed = true;
    return true;
}

vector<string> *SearchEngine::Search(string text) {
    string word;
    stringstream ss(text);
    vector<string> *results = new vector<string>();

    if (!indexedWords.size()) {
        return results;
    }

    vector<indexedElement::pointer> pointers;

    while (ss >> word) {
        unsigned int offset, begin = 0, end = indexedWords.size() - 1;
        while (begin != end) {
            offset = (begin + end) >> 1;
            string check = indexedWords[offset].value;
            if (check < word) {
                begin = offset + 1;
            } else {
                end = offset;
            }
        }
        if (indexedWords[begin].value == word) {
            indexedElement *element = &indexedWords[begin];
            for (vector<indexedElement::pointer>::iterator i = element->pointers.begin(); i != element->pointers.end(); i++) {
                if (!pointers.size()) {
                    pointers.push_back(*i);
                }
                begin = 0; end = pointers.size();
                while (begin != end) {
                    offset = (begin + end) >> 1;
                    indexedElement::pointer check = pointers[offset];
                    if (check < *i) {
                        begin = offset + 1;
                    } else {
                        end = offset;
                    }
                }
                if (pointers[begin] != *i) {
                    vector<indexedElement::pointer>::iterator position = pointers.begin() + begin;
                    pointers.insert(position, *i);
                }
            }
        }
    }

    for (vector<indexedElement::pointer>::iterator i = pointers.begin(); i != pointers.end(); i++) {
        results->push_back(*(*i));
    }

    return results;
}
