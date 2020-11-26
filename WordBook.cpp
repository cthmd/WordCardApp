#include "WordBook.h"
#include <ctype.h>

WordCard::WordCard(string line){
    stringstream input(line);
    string out;
    int i = 0;
    while(input>>out){
        if(i == 0) word = out;
        if(i == 1){
            if(!isalpha(out[0])){
                phonetic = out;
            }
            else{
                phonetic = "-";
                meanings.push_back(out);
            }
        }
        if(i > 1) meanings.push_back(out);
        i++;
    }
}

WordBook::WordBook(string title, string filePath){
    creation = true;
    this->title = title;
    this->filePath = filePath;
    readFile();
}

void WordBook::readFile(){
    ifstream textFile;
    string line;
    textFile.open(filePath);
    while(getline(textFile, line)){
        WordCard word(line);
        wordList.push_back(word);
    }
    textFile.close();
}

void WordBook::printWordList(vector<WordCard> list){
    for(auto v:list){
        cout<<v.getWord()<<endl;
    }
}

