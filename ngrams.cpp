// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
#include <stack>
#include <filelib.h>
#include "map.h"
#include "vector.h"
#include "simpio.h"
#include "cstdlib"
#include "stdlib.h"
#include<time.h>
#define random(x) (rand()%x)

using namespace std;

map<vector<string>,vector<string>> wordmap;

void makemap(ifstream &infile,int n){

    vector<string> window;
    vector<string> fwindow;
    string nextword;

    for(int i = 1; i < n; i++){
        infile >> nextword;
        fwindow.push_back(nextword);
    }
    window = fwindow;

    while(1){
        infile >> nextword;
        if(!infile){
            break;
        }
        vector<string> tmp = wordmap[window];
        tmp.push_back(nextword);
        wordmap[window] = tmp;

        window.erase(window.begin());
        window.push_back(nextword);

        for(int i = 0; i < fwindow.size(); i++){
            tmp = wordmap[window];
            tmp.push_back(fwindow[i]);
            wordmap[window] = tmp;

            window.erase(window.begin());
            window.push_back(fwindow[i]);
        }
    }
}

void produce(int num){
    map<vector<string>,vector<string>>::iterator it;
    vector<vector<string>> keys;
    for(it = wordmap.begin(); it != wordmap.end(); it++){
        keys.push_back(it -> first);
    }
    srand((int)time(0));
    int randomint = random(keys.size());
    vector<string> key = keys[randomint];
    int ksize = key.size();

    cout << "...";
    for(int i = 0; i < ksize; i++){
        cout << key[i] << " ";
    }

    for(int i = 0; i < num - ksize; i++){
        randomint = random(wordmap[key].size());
        string nextword = wordmap[key][randomint];
        cout << nextword << " ";
        key.erase(key.begin());
        key.push_back(nextword);
    }
    cout << "..." << endl;
}
int main() {
    // TODO: Finish the program!
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << "\n"
         << "This program makes random text based on a document." << "\n"
         << "Give me an input file and an 'N' value for groups " << "\n"
         << "of words, and I'll create random text for you." << "\n";

    cout << "Input file name?";
    string filename;
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    while(!infile){
        cout << "Unable to open that file.  Try again." << endl;
        cout << "Input file name?";
        cin >> filename;
        infile.open(filename);
    }
    cout << "Value of N?";
    int N;
    cin >> N;
    while(N < 2){
        cout << "N must be 2 or greater." << endl;
        cout << "Value of N?";
        cin >> N;
    }

    makemap(infile, N);
    while(1){
        cout << "# of random words to generate (0 to quit)? ";
        int wordsnum;
        cin >> wordsnum;
        while(wordsnum < N){
            if(wordsnum == 0){
                cout << "Exiting.";
                return 0;
            }
            cout << "Must be at least " << N << " words." << endl;
            cout << "# of random words to generate (0 to quit)? ";
            cin >> wordsnum;
        }
        produce(wordsnum);
    }
}
