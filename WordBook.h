#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class WordCard{
private:
    string word;
    string phonetic;
    vector<string> meanings;
    int priority;
    vector<int> studyDate;

public:
    WordCard(){}
    WordCard(string line);
    string getWord(){
        return word;
    }
    string getPhonetic(){
        return phonetic;
    }
    vector<string> getMeanings(){
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
    int getPriority(){
        return priority;
    }
    vector<int> getStudyDate(){
        return studyDate;
    }
};

class WordBook{
protected:
    bool creation;
    string title;
    string filePath;
    vector<WordCard> wordList;
    void readFile();
public:
    WordBook(){
        creation = false;
    }
    WordBook(string title, string filepath);
    static void printWordList(vector<WordCard> list);
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
    void sort();
public:
    NoteBook(string title):WordBook(){
        this->title = title;
    }
    void view();
    void addWord(WordCard word);
};



