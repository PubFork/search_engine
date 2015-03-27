#include "search_engine.h"
#include <string.h>

struct WordElement {
    char *acWord;
    IndexList *pIndexes;
    WordElement *pNext;
};

SearchEngine::SearchEngine() {
    uiTextCount = 0;
    uiWordCount = 0;
    pTextList = NULL;
    bIsIndexed = false;
    pCurrentText = NULL;
}

bool SearchEngine::AddText(std::string sText) {
    if (bIsIndexed) {
        return false;
    }
    if (pTextList != NULL) {
        pCurrentText->pNext = new TextElement;
        pCurrentText = pCurrentText->pNext;
    } else {
        pTextList = new TextElement;
        pCurrentText = pTextList;
    }
    pCurrentText->sText = sText;
    pCurrentText->pNext = NULL;
    uiTextCount++;
    return true;
}

bool SearchEngine::BuildIndexes() {
    if (bIsIndexed) {
        return false;
    }

    unsigned int i = 0;
    pTextArray = new std::string[uiTextCount];
    TextElement *pElement = pTextList;
    while (pTextList != NULL) {
        pElement = pTextList;
        pTextArray[i] = pTextList->sText;
        pTextList = pTextList->pNext;
        delete pElement;
        i++;
    }

    WordElement *pFirstWord = NULL;
    for (i = 0; i < uiTextCount; i++) {
        char *acText, *pWord;
        unsigned int uiLength = pTextArray[i].size();
        acText = new char[uiLength+1];
        strcpy(acText, pTextArray[i].c_str());
        pWord = strtok(acText, " ");
        while (pWord != NULL) {
            bool bAdd = true;
            WordElement *pPrevious = NULL;
            WordElement *pCurrent = pFirstWord;
            while (pCurrent != NULL) {
                bool bIsSmaller = false;
                unsigned int k, uiLength;
                uiLength = std::min(strlen(pCurrent->acWord), strlen(pWord));
                for (k = 0; k < uiLength; k++) {
                    if (pCurrent->acWord[k] != pWord[k]) {
                        if (pCurrent->acWord[k] > pWord[k]) {
                            bIsSmaller = true;
                        }
                        break;
                    }
                }
                if (bIsSmaller || ((k == uiLength) && (strlen(pCurrent->acWord) > strlen(pWord)))) {
                    break;
                } else if ((k == uiLength) && (strlen(pCurrent->acWord) == strlen(pWord))) {
                    pCurrent->pIndexes->Add(i);
                    bAdd = false;
                    break;
                }
                pPrevious = pCurrent;
                pCurrent = pCurrent->pNext;
            }
            if (bAdd) {
                WordElement *pAdded;
                if (pPrevious != NULL) {
                    pPrevious->pNext = new WordElement;
                    pAdded = pPrevious->pNext;
                } else {
                    pAdded = new WordElement;
                }
                pAdded->pNext = pCurrent;
                pAdded->pIndexes = new IndexList();
                pAdded->acWord = new char[strlen(pWord)+1];
                strcpy(pAdded->acWord, pWord);
                pAdded->pIndexes->Add(i);
                uiWordCount++;
                if (pPrevious == NULL) {
                    pFirstWord = pAdded;
                }
            }
            pWord = strtok(NULL, " ");
        }
        delete [] acText;
    }

    i = 0;
    pIndexTable = new SearchElement[uiWordCount];
    WordElement *pTemp = pFirstWord;
    while (pTemp != NULL) {
        pIndexTable[i].acWord = pTemp->acWord;
        pIndexTable[i].pIndexes = pTemp->pIndexes;
        WordElement *pDelete = pTemp;
        pTemp = pTemp->pNext;
        delete pDelete;
        i++;
    }

    bIsIndexed = true;
    return true;
}

unsigned int SearchEngine::Search(std::string sText, std::string **pStrings) {
    IndexList *pIndexes = new IndexList();
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
    return uiCounter;
}

SearchEngine::~SearchEngine() {
    TextElement *pTemp;
    while (pTextList != NULL) {
        pTemp = pTextList;
        pTextList = pTemp->pNext;
        delete pTemp;
    }
    if (bIsIndexed) {
        for (unsigned int i = 0; i < uiWordCount; i++) {
            delete [] pIndexTable[i].acWord;
            delete pIndexTable[i].pIndexes;
        }
        delete [] pIndexTable;
        delete [] pTextArray;
    }
}
