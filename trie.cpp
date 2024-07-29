#include <iostream>
#include <vector>
#include "trie.h"
using namespace std;

int main()
{
    Trie<char, string> trie;

    vector<string> dictionary = {"hello", "hey", "help", "hii", "helium"};
    for (const string &word : dictionary)
    {
        trie.insert(word);
    }

    vector<string> wordsToCheck = {"hello", "hi", "helium", "helpful"};
    for (const string &word : wordsToCheck)
    {
        if (trie.find(word))
        {
            cout << word << " is in the dictionary." << endl;
        }
        else
        {
            cout << word << " is NOT in the dictionary." << endl;
        }
    }

    cout << "\nAll words in the Trie:" << endl;
    trie.displayAllWords();

    string prefix = "he";
    int count = trie.countWordsStartingWith(prefix);
    cout << "\nNumber of words starting with '" << prefix << "': " << count << endl;

    prefix = "he";
    vector<string> suggestions = trie.suggest(prefix);
    cout << "\nSuggestions for prefix '" << prefix << "':" << endl;
    for (const string &suggestion : suggestions)
    {
        cout << suggestion << endl;
    }

    string wordToClear = "hello";
    trie.clear(wordToClear);
    cout << "\nAfter clearing the word '" << wordToClear << "':" << endl;
    trie.displayAllWords();

    return 0;
}
