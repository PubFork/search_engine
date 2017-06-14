#include "search_engine.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    SearchEngine *searchEngine = new SearchEngine();

    searchEngine->AddText("marcin jest zajebisty");
    searchEngine->AddText("agatka jest fajna");
    searchEngine->AddText("adam to kretyn");

    string text = "jest fajna";

    vector<string> *results = searchEngine->Search(text);
    if ((results != NULL) && results->size()) {
        cout << "Texts containing '" << text << "':" << endl;
        for (vector<string>::iterator i = results->begin(); i != results->end(); i++) {
            cout << *i << endl;
        }
    } else {
        cout << "No results to display!" << endl;
    }
    delete results;

    cout << "Press the enter key to continue ...";
    cin.get();

    delete searchEngine;
    return EXIT_SUCCESS;
}
