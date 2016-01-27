#include "search_engine.h"
#include <sstream>

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

    for (IndexedElement::pointer i = texts.begin(); i != texts.end(); i++) {
        string word;
        stringstream ss(*i);

        while (ss >> word) {
            unsigned int offset, begin = 0, end = indexedWords.size();
            while (begin != end) {
                offset = (begin + end) >> 1;
                string check = indexedWords[offset].value;
                if (check < word) {
                    begin = offset + 1;
                } else {
                    end = offset;
                }
            }
            if ((begin >= indexedWords.size()) || (indexedWords[begin].value != word)) {
                IndexedElement element;
                element.value = word;
                element.pointers.push_back(i);
                vector<IndexedElement>::iterator position = indexedWords.begin() + begin;
                indexedWords.insert(position, element);
            } else {
                indexedWords[begin].pointers.push_back(i);
            }
        }
    }

    isIndexed = true;
    return true;
}

vector<string>* SearchEngine::Search(string text) {
    string word;
    stringstream ss(text);
    vector<string>* results = new vector<string>();

    if (!indexedWords.size()) {
        return results;
    }

    vector<IndexedElement::pointer> pointers;

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
            IndexedElement* element = &indexedWords[begin];
            for (vector<IndexedElement::pointer>::iterator i = element->pointers.begin(); i != element->pointers.end(); i++) {
                if (!pointers.size()) {
                    pointers.push_back(*i);
                }
                begin = 0; end = pointers.size();
                while (begin != end) {
                    offset = (begin + end) >> 1;
                    IndexedElement::pointer check = pointers[offset];
                    if (check < *i) {
                        begin = offset + 1;
                    } else {
                        end = offset;
                    }
                }
                if ((begin >= pointers.size()) || (pointers[begin] != *i)) {
                    vector<IndexedElement::pointer>::iterator position = pointers.begin() + begin;
                    pointers.insert(position, *i);
                }
            }
        }
    }

    for (vector<IndexedElement::pointer>::iterator i = pointers.begin(); i != pointers.end(); i++) {
        results->push_back(*(*i));
    }

    return results;
}
