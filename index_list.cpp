#include "index_list.h"
#define NULL 0

using namespace std;

IndexList::IndexList() {
    pFirstElement = NULL;
    pCurrentElement = NULL;
}

IndexList::~IndexList() {
    IndexElement *pTemp;
    pCurrentElement = pFirstElement;
    while (pCurrentElement != NULL) {
        pTemp = pCurrentElement;
        pCurrentElement = pTemp->pNext;
        delete pTemp;
    }
}

bool IndexList::Add(unsigned int uiIndex) {
    IndexElement *pTemp;
    pCurrentElement = pFirstElement;
    if ((pFirstElement == NULL) || (pFirstElement->uiIndex > uiIndex)) {
        pFirstElement = new IndexElement;
        pTemp = pFirstElement;
    } else {
        while (pCurrentElement != NULL) {
            pTemp = pCurrentElement;
            if (pTemp->uiIndex == uiIndex) {
                return false;
            }
            pCurrentElement = pCurrentElement->pNext;
            if (pCurrentElement != NULL) {
                if (pCurrentElement->uiIndex > uiIndex) {
                    break;
                }
            }
        }
        pTemp->pNext = new IndexElement;
        pTemp = pTemp->pNext;
    }
    pTemp->uiIndex = uiIndex;
    pTemp->pNext = pCurrentElement;
    pCurrentElement = pTemp;
    return true;
}

bool IndexList::GetFirst(unsigned int *uiIndex) {
    if (pFirstElement != NULL) {
        pCurrentElement = pFirstElement;
        *uiIndex = pCurrentElement->uiIndex;
        return true;
    }
    return false;
}

bool IndexList::GetNext(unsigned int *uiIndex) {
    if (pCurrentElement->pNext != NULL) {
        pCurrentElement = pCurrentElement->pNext;
        *uiIndex = pCurrentElement->uiIndex;
        return true;
    }
    return false;
}
