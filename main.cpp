#include "search_engine.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    SearchEngine *pSearchEngine = new SearchEngine();
    pSearchEngine->AddText("agatka jest fajna");
    pSearchEngine->AddText("adam to kretyn");
    pSearchEngine->AddText("marcin jest zajebisty");
    pSearchEngine->BuildIndexes();
    string *pResults;
    unsigned int uiResults = pSearchEngine->Search("jest", &pResults);
    if (uiResults) {
        cout << "Texts containing '" << "jest" << "':" << endl;
        for (unsigned int i = 0; i < uiResults; i++) {
            cout << pResults[i] << endl;
        }
        delete [] pResults;
    } else {
        cout << "No results to display!" << endl;
    }

    cout << "Press the enter key to continue ...";
    cin.get();

    delete pSearchEngine;
    return EXIT_SUCCESS;
}
