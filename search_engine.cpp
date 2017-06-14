#include "search_engine.h"
#include <sstream>

using std::stringstream;

struct ScoredResult {
    unsigned int offset;
    unsigned int score;
};

SearchEngine::SearchEngine() : isLocked(false) {
}

SearchEngine::~SearchEngine() {
}

bool SearchEngine::AddText(string text) {
    isLocked = true;

    texts.push_back(text);

    string word;
    stringstream ss(text);

    while (ss >> word) {
        unsigned int offset, begin = 0, end = indexedWords.size();
        while (begin != end) {
            offset = (begin + end) >> 1;
            string check = indexedWords[offset].word;
            if (check < word) {
                begin = offset + 1;
            } else {
                end = offset;
            }
        }
        if ((begin >= indexedWords.size()) || (indexedWords[begin].word != word)) {
            IndexedWord indexed;
            indexed.word = word;
            indexed.offsets.push_back(texts.size() - 1);
            vector<IndexedWord>::iterator position = indexedWords.begin() + begin;
            indexedWords.insert(position, indexed);
        } else {
            indexedWords[begin].offsets.push_back(texts.size() - 1);
        }
    }

    isLocked = false;

    return true;
}

vector<string> *SearchEngine::Search(string text) {
    if (isLocked || !indexedWords.size()) {
        return NULL;
    }

    string word;
    stringstream ss(text);
    vector<ScoredResult> scored;
    vector<string> *results = new vector<string>();

    while (ss >> word) {
        unsigned int offset, begin = 0, end = indexedWords.size() - 1;
        while (begin != end) {
            offset = (begin + end) >> 1;
            string check = indexedWords[offset].word;
            if (check < word) {
                begin = offset + 1;
            } else {
                end = offset;
            }
        }
        if (indexedWords[begin].word == word) {
            IndexedWord *indexed = &indexedWords[begin];
            for (vector<unsigned int>::iterator i = indexed->offsets.begin(); i != indexed->offsets.end(); i++) {
                if (!scored.size()) {
                    ScoredResult result = {*i, 0};
                    scored.push_back(result);
                    continue;
                }
                begin = 0; end = scored.size();
                while (begin != end) {
                    offset = (begin + end) >> 1;
                    unsigned int check = scored[offset].offset;
                    if (check < *i) {
                        begin = offset + 1;
                    } else {
                        end = offset;
                    }
                }
                if ((begin >= scored.size()) || (scored[begin].offset != *i)) {
                    vector<ScoredResult>::iterator position = scored.begin() + begin;
                    ScoredResult result = {*i, 0};
                    scored.insert(position, result);
                } else if ((begin < scored.size()) && (scored[begin].offset == *i)) {
                    scored[begin].score++;
                }
            }
        }
    }

    unsigned int count = scored.size();
    while (count > 1) {
        for (unsigned int i = count - 1; i >= 1; i--) {
            if (scored[i].score > scored[i-1].score) {
                ScoredResult swap = {scored[i].offset, scored[i].score};
                scored[i].offset = scored[i-1].offset;
                scored[i].score = scored[i-1].score;
                scored[i-1].offset = swap.offset;
                scored[i-1].score = swap.score;
            }
        }
        count--;
    }

    for (vector<ScoredResult>::iterator i = scored.begin(); i != scored.end(); i++) {
        results->push_back(texts[(*i).offset]);
    }

    isLocked = false;

    return results;
}
