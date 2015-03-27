#ifndef INDEX_LIST_H
#define INDEX_LIST_H

struct IndexElement {
    IndexElement *pNext;
    unsigned int uiIndex;
};

class IndexList {
    private:
        IndexElement *pFirstElement;
        IndexElement *pCurrentElement;
    public:
        IndexList();
        ~IndexList();
        
        bool Add(unsigned int uiIndex);
        bool GetFirst(unsigned int *uiIndex);
        bool GetNext(unsigned int *uiIndex);
};

#endif
