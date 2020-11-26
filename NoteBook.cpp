#include "WordBook.h"

void NoteBook::view(){
    /*HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int k = 1; k < 255; k++){
        SetConsoleTextAttribute(hConsole, k);
        cout << k << " I want to be nice today!" << endl;
    }*/
    int j = 0;
    char input = 0;
    while(input != 'n'){
        for(int i = 0; i < 10; i++){
            if(j*10+i < wordList.size()){
                cout<<wordList[10*j+i].getWord()<<" "<<wordList[10*j+i].getMeaningsString()<<endl;
            }
        }
        j++;
        cin>>input;
    }
}

void NoteBook::addWord(WordCard word){
    wordList.push_back(word);
}

