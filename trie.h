#include <iostream>
#include <vector>
using namespace std;

template <class T1, class T2>

class TrieNode
{
public:
    T1 data;
    TrieNode<T1, T2> *children[26];
    bool isTerminal;

    TrieNode(T1 data)
    {
        this->data = data;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
        isTerminal = false;
    }
};

template <class T1, class T2>

class Trie
{
public:
    TrieNode<T1, T2> *root;

    Trie()
    {
        root = new TrieNode<T1, T2>('\0');
    }

    void insertUtil(TrieNode<T1, T2> *root, T2 word)
    {
        if (word.length() == 0)
        {
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'a';
        if (index < 0 || index >= 26)
        {
            throw out_of_range("Invalid character in word");
        }
        TrieNode<T1, T2> *child;

        if (root->children[index] != nullptr)
        {
            child = root->children[index];
        }
        else
        {
            child = new TrieNode<T1, T2>(word[0]);
            root->children[index] = child;
        }

        insertUtil(child, word.substr(1));
    }

    void insert(T2 word)
    {
        try
        {
            insertUtil(root, word);
        }
        catch (const out_of_range e)
        {
            cout << "Unexpected error:" << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "Insertion Error :" << e.what() << endl;
        }
    }

    bool findUtil(TrieNode<T1, T2> *root, T2 word)
    {
        if (word.length() == 0)
        {
            return root->isTerminal;
        }

        int index = word[0] - 'a';
        if (index < 0 || index >= 26)
        {
            throw out_of_range("Invalid character in word");
        }
        TrieNode<T1, T2> *child;

        if (root->children[index] != nullptr)
        {
            child = root->children[index];
        }
        else
        {
            return false;
        }

        return findUtil(child, word.substr(1));
    }

    bool find(T2 word)
    {
        try
        {
            return findUtil(root, word);
        }
        catch (const out_of_range e)
        {
            cout << "Invalid charater in word..!!" << endl;
            return false;
        }
        catch (const exception &e)
        {
            cout << "Unexpected error..." << e.what() << endl;
            return false;
        }
    }

    void clearUtil(TrieNode<T1, T2> *root, T2 word)
    {
        if (word.length() == 0 && root->isTerminal == true)
        {
            root->isTerminal = false;
            return;
        }

        int index = word[0] - 'a';
        TrieNode<T1, T2> *child;

        if (root->children[index] != nullptr)
        {
            child = root->children[index];
        }
        else
        {
            root->isTerminal = false;
            return;
        }

        clearUtil(child, word.substr(1));
    }

    void clear(T2 word)
    {
        try
        {
            clearUtil(root, word);
        }
        catch (const out_of_range e)
        {
            cout << "Invalid charater in word..!!" << endl;
        }
        catch (const exception &e)
        {
            cout << "Unexpected error...!!" << e.what() << endl;
        }
    }

    void solve(TrieNode<T1, T2> *root, T2 currPrefix, vector<T2> &ans)
    {
        if (root == nullptr)
            return;

        if (root->isTerminal)
        {
            ans.push_back(currPrefix);
        }
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i] != nullptr)
                solve(root->children[i], currPrefix + root->children[i]->data, ans);
        }
    }

    int countWordsStartingWith(T2 word)
    {
        vector<T2> ans;
        solve(root, "", ans);
        int cnt = 0;
        for (auto &str : ans)
        {
            if (str.find(word) == 0)
            {
                cnt++;
            }
        }
        return cnt;
    }

    void collectWords(TrieNode<T1, T2> *currentNode, T2 currentPrefix, vector<T2> &words)
    {
        if (currentNode->isTerminal)
        {
            words.push_back(currentPrefix);
        }
        for (int i = 0; i < 26; i++)
        {
            if (currentNode->children[i] != nullptr)
            {
                collectWords(currentNode->children[i], currentPrefix + currentNode->children[i]->data, words);
            }
        }
    }

    vector<T2> getAllWords()
    {
        vector<T2> words;
        collectWords(root, "", words);
        return words;
    }

    void displayAllWords()
    {
        vector<T2> words = getAllWords();
        for (const T2 &word : words)
        {
            cout << word << endl;
        }
    }

    void suggestHelper(TrieNode<T1, T2> *currentNode, T2 prefix, vector<T2> &suggestions)
    {
        if (currentNode->isTerminal)
        {
            suggestions.push_back(prefix);
        }
        for (int i = 0; i < 26; i++)
        {
            if (currentNode->children[i] != nullptr)
            {
                suggestHelper(currentNode->children[i], prefix + currentNode->children[i]->data, suggestions);
            }
        }
    }

    vector<T2> suggest(T2 prefix)
    {
        TrieNode<T1, T2> *currentNode = root;
        for (T1 ch : prefix)
        {
            int index = ch - 'a';
            if (currentNode->children[index] == nullptr)
            {
                return {};
            }
            currentNode = currentNode->children[index];
        }
        vector<T2> suggestions;
        suggestHelper(currentNode, prefix, suggestions);
        return suggestions;
    }
};
