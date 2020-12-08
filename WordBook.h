#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

class WordCard{
private:
    string word;
    string phonetic;
    int priority;
    vector<string> meanings;
    vector<int> studyDate;

public:
    WordCard(){}
    WordCard(string line);
    WordCard(const WordCard& obj){
        word = obj.getWord();
        phonetic = obj.getPhonetic();
        priority = obj.getPriority();
        meanings = obj.getMeanings();
        studyDate = obj.getStudyDate();
    }
    string getWord() const{
        return word;
    }
    string getPhonetic() const{
        return phonetic;
    }
    vector<string> getMeanings() const{
        return meanings;
    }
    string getMeaningsString(){
        string str;
        for(auto s:meanings){
            str = str + s + " ";
        }
        return str;
    }
    void setStudyStage(int p, int date){
        priority = p;
        if(priority > 3){
            priority = 3;
        }
        studyDate.push_back(date);
    }
    void setStudyStage(int p, vector<int> list){
        priority = p;
        if(priority > 3){
            priority = 3;
        }
        studyDate = list;
    }
    int getPriority() const{
        return priority;
    }
    vector<int> getStudyDate() const{
        return studyDate;
    }
    void dataUpdate(ofstream &file, int option = 1);
    bool operator<(const WordCard &other) const{
        return word.compare(other.getWord()) < 0;
    }
};

class WordBook{
protected:
    bool creation = false;
    string title;
    string filePath;
    vector<WordCard> wordList;
    void readFile();
public:
    WordBook(){}
    WordBook(string title, string filepath);
    static void printWordList(vector<WordCard> list);
    static vector<string> splitLine(string line);
    bool isCreated(){
        return creation;
    }
    vector<WordCard> getList(){
        return wordList;
    }
    string getTitle(){
        return title;
    }
};

class NoteBook:public WordBook{
private:
    vector<WordCard> alphabeticSort();
public:
    NoteBook(string title, string filePath):WordBook(title, filePath){}
    void view();
    void addWord(WordCard word);
};



