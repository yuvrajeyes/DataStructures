#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* children[26];
    int prefixCount = 0;
    int wordCount = 0;
    int childrenCount = 0;

    bool containsKey(char ch) {
        return (children[ch - 'a'] != NULL);
    }

    Node* get(char ch) {
        return children[ch - 'a'];
    }

    void put(char ch, Node* node) {
        children[ch - 'a'] = node;
    }

    bool isEmpty() {
        for (auto &it: children)
            if (it!=NULL)
                return false;
        return true;
    }

    void updateChildrenCount() {
        int cnt = 0;
        for (auto &it: children)
            if (it!=NULL)
                cnt++;
        childrenCount = cnt;
    }
};


class TrieNode {
    private:
    Node* root;

    public:
    TrieNode() {
        root = new Node();
    }

    // Method to insert a word into the Trie
    void insert(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (!current->containsKey(ch)) {
                current->put(ch, new Node());
                current->childrenCount++;
            }
            current = current->get(ch);
            current->prefixCount++;
        }
        current->wordCount++;
    }

    void insert(vector<string> const& words) {
        for (const auto &word: words) insert(word);
    }

    // Method to search for a word in the Trie
    bool search(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (!current->containsKey(ch))
                return false;
            current = current->get(ch);
        }
        return current->wordCount > 0;
    }

    bool startsWith(const string& word) {
        Node* current = root;
        for (char ch: word) {
            if (!current->containsKey(ch))
                return false;
            current = current->get(ch);
        }
        return true;
    }

    int wordCount(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (!current->containsKey(ch))
                return 0;
            current = current->get(ch);
        }
        return current->wordCount;
    }

    int prefixCount(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (!current->containsKey(ch))
                return 0;
            current = current->get(ch);
        }
        return current->prefixCount;
    }

    int childrenCount() {
        return root->childrenCount;
    }

    Node* remove(Node* node, string key, int depth, int &numWords) {
        // If tree is empty
        if (!node)
            return NULL;
    
        // If last character of key is being processed
        if (depth == key.size()) {
            // This node is no more end of word after removal of given key
            numWords = node->wordCount;
            if (numWords>0) {
                node->wordCount = 0;
                node->prefixCount -= numWords;
            }
            // If given is not prefix of any other word
            if (node->isEmpty()) {
                delete (node);
                node = NULL;
            }
            return node;
        }
    
        // If not last character, recur for the child
        node->children[key[depth] - 'a'] = remove(node->children[key[depth] - 'a'], key, depth + 1, numWords);
        node->prefixCount -= numWords;
        node->updateChildrenCount();
    
        // If node does not have any child (its only child got deleted), and it is not end of another word.
        if (node->isEmpty() && node->wordCount == 0) {
            delete (node);
            node = NULL;
        }
        return node;
    }

    void erase(const string& word) {
        int numWords = 0;
        remove(root, word, 0, numWords);
    }

    void erase(vector<string>const& words) {
        for (const auto &word: words) erase(word);
    }
};

int main() {
    TrieNode trie;
    trie.insert({"a", "ab", "appl", "apple", "applf", "appld", "bp", "cppl", "cpple"});
    
    cout << (trie.childrenCount()) << endl;   
    trie.erase("bp");
    cout << (trie.childrenCount()) << endl; 
    trie.erase("cppl");
    cout << (trie.prefixCount("c")) << endl; 
    cout << (trie.prefixCount("cp")) << endl; 
    cout << (trie.prefixCount("cpp")) << endl; 
    cout << (trie.prefixCount("cppl")) << endl;
    trie.erase("cpple");
    cout << (trie.childrenCount()) << endl; 
    cout << (trie.prefixCount("c")) << endl; 
    cout << (trie.prefixCount("cp")) << endl; 
    cout << (trie.prefixCount("cpp")) << endl; 
    cout << (trie.prefixCount("cppl")) << endl;
    cout<<endl<<endl;

    trie.erase({"a", "ab", "appl", "apple", "applf", "appld"});
    cout << (trie.childrenCount()) << endl; 
    cout << (trie.prefixCount("a")) << endl; 
    cout << (trie.prefixCount("ap")) << endl; 
    cout << (trie.prefixCount("app")) << endl; 
    cout << (trie.prefixCount("appl")) << endl;

    return 0;
}
