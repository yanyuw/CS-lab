// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <ctype.h>
#include <lexicon.h>

using namespace std;

void findladders(string begin, string end, Lexicon& wordlist){

    queue<stack<string>> que;
    stack<string> fstack;
    set<string> wordset; //已经在ladder中的单词
    wordset.insert(begin);
    fstack.push(begin);
    que.push(fstack);

    bool found = false;
    while(!que.empty() && !found){
        stack<string> nowstack = que.front();
        que.pop();
        string top = nowstack.top();
        int len = top.length();
        for(int i = 0; i < len; i++){
            for(char j = 'a'; j <= 'z'; j++){
                string tmp = top;
                tmp[i] = j;
                if(!wordset.count(tmp) && wordlist.contains(tmp)){
                    wordset.insert(tmp);
                    if(tmp == end){
                        cout << "A ladder from " << end << " back to " << begin << ":" << endl;
                        cout << end << " ";
                        while(!nowstack.empty()){
                            cout << nowstack.top() << " ";
                            nowstack.pop();
                        }
                        cout << endl << endl;
                        found = true;
                    }
                    else{
                        stack<string> newstack;
                        newstack = nowstack;
                        newstack.push(tmp);
                        que.push(newstack);
                    }
                }
            }
        }
    }
    if(!found){
        cout << "No word ladder found from " << end << " back to " << begin << "." << endl;
    }
}
string stringtolower(string str){
    for(int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
int main() {
    string dict, w1, w2;
    queue<string> que, visited;

    cout << "Welcome to CS 106B Word Ladder." << "\n"
         << "Please give me two English words, and I will change the" << "\n"
         << "first into the second by changing one letter at a time." << "\n" << "\n";

    cout << "Dictionary file name?";
    cin >> dict;
//    ifstream infile;
//    infile.open(dict);
//    while(!infile){
//        cout << "Unable to open that file.  Try again." << endl;
//        cout << "Dictionary file name?";
//        cin >> dict;
//        infile.open(dict);
//    }
//    string str;
//    set<string>wordlist;
//    while(getline(infile,str)){
//        wordlist.insert(str);
//    }
//    //读取字典并存为数组
    Lexicon wordlist(dict);
    string temp;
    getline(std::cin,temp);
    while(1){
        cout << "Word #1 (or Enter to quit):";
        getline(std::cin,w1);
        if(w1 == ""){
            break;
        }
        cout << "Word #2 (or Enter to quit):";
        getline(std::cin,w2);
        if(w2 == ""){
            break;
        }else if(!(wordlist.contains(w2) && wordlist.contains(w1))){
            cout << "The two words must be found in the dictionary." << "\n";
        }
        else if(w1.length() != w2.length()){
            cout << "The two words must be the same length." << "\n";
        }else if(w1 == w2){
            cout << "The two words must be different." << "\n";
        }
        else{
            w1 = stringtolower(w1);
            w2 = stringtolower(w2);
            findladders(w1,w2,wordlist);
        }
    }


    cout << "Have a nice day." << endl;
    return 0;
}
