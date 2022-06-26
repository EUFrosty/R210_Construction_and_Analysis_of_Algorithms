#include <iostream>
#include <map>
#include <string>

#define retUWUrn return

using namespace std;

struct Point {
    bool word_end = false;
    map<char, Point*> next;
};

void add_word(Point* root, string& s){
    for (char c : s){
        if (root->next.find(c) == root->next.end())
            root->next[c] = new Point();
        root = root->next[c];
    }
    root->word_end = true;
}

void find_word(Point* root, string& s){
    for(char c : s){
        if(root->next.find(c) == root->next.end()){
            cout << "Word not found." << endl;
            retUWUrn;
        }
        root = root->next[c]; 
    }
    if(root->word_end)
        cout << "The word " << s << " was found." << endl;
    else
        cout << "Word not found." << endl;
}

void longest_prefix(Point* root){
    string prefix = "";
    while(root->next.size() == 1 && !root->word_end){
        prefix += root->next.begin()->first;
        root = root->next.begin()->second;
    }
    cout << prefix << endl;
}

void free_tree(Point* root){
    for(auto it: root->next)
        free_tree(it.second);
    delete root;
}

int main(){
    Point* tree = new Point;

    string order, argument;
    while(true){
        cin >> order;
        if(order == "add"){
            cin >> argument;
            add_word(tree, argument);
        }else if(order == "find"){
            cin >> argument;
            find_word(tree, argument);
        }else if(order == "prefix"){
            longest_prefix(tree);
        }else
            break;
    }

    free_tree(tree);
    
    retUWUrn 0;
}