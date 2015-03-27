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

    for (std::vector<std::string>::iterator i = texts.begin(); i != texts.end(); i++) {
        std::string word;
        std::stringstream ss(*i);

        while (ss >> word) {
            bool add = true;
            std::vector<IndexedElement<std::string> >::iterator j;
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
                IndexedElement<std::string> element;
                element.value = word;
                element.indexes.push_back(i);
                indexedWords.insert(j, element);
            }
        }
    }

    isIndexed = true;
    return true;
}

std::vector<std::string> SearchEngine::Search(std::string text) {
    std::string word;
    std::stringstream ss(text);

    while (ss >> word) {
    }

    /*IndexList *pIndexes = new IndexList();
    char *acText, *pWord;
    acText = new char[sText.size()+1];
    strcpy(acText, sText.c_str());
    pWord = strtok(acText, " ");
    unsigned int uiCounter = 0;
    while (pWord != NULL) {
        unsigned int uiStart = 0;
        unsigned int uiEnd = uiWordCount-1;
        while (uiEnd != uiStart) {
            bool bIsSmaller = false;
            unsigned int k, uiLength, uiCheck = (uiStart+uiEnd)/2;
            uiLength = std::min(strlen(pWord), strlen(pIndexTable[uiCheck].acWord));
            for (k = 0; k < uiLength; k++) {
                if (pIndexTable[uiCheck].acWord[k] != pWord[k]) {
                    if (pIndexTable[uiCheck].acWord[k] < pWord[k]) {
                        bIsSmaller = true;
                    }
                    break;
                }
            }
            if ((k == uiLength) && (strlen(pIndexTable[uiCheck].acWord) < strlen(pWord))) {
                bIsSmaller = true;
            }
            if (bIsSmaller) {
                uiStart = uiCheck+1;
            } else {
                uiEnd = uiCheck;
            }
        }
        if (!strcmp(pWord, pIndexTable[uiStart].acWord)) {
            unsigned int uiIndex;
            if (pIndexTable[uiStart].pIndexes->GetFirst(&uiIndex)) {
                if (pIndexes->Add(uiIndex)) {
                    uiCounter++;
                }
                while (pIndexTable[uiStart].pIndexes->GetNext(&uiIndex)) {
                    if (pIndexes->Add(uiIndex)) {
                        uiCounter++;
                    }
                }
            }
        }
        pWord = strtok(NULL, " ");
    }
    delete [] acText;

    std::string *pResults = NULL;
    if (uiCounter > 0) {
        unsigned int uiIndex, i = 1;
        pResults = new std::string[uiCounter];
        if (pIndexes->GetFirst(&uiIndex)) {
            pResults[0] = pTextArray[uiIndex];
            while (pIndexes->GetNext(&uiIndex)) {
                pResults[i] = pTextArray[uiIndex];
                i++;
            }
        }
    }
    *pStrings = pResults;

    delete pIndexes;
    return uiCounter;*/
    std::vector<std::string> results;
    return results;
}
