#include <cstring>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdio>
#include <algorithm>
using namespace std;

class WordCard{ // 单词卡
private:
    string word; // 单词
    string phonetic; // 音标
    int priority; // 优先级
    vector<string> meanings; // 中文解释
    vector<int> studyDate; // 学习（复习）日期列表

public:
    WordCard(){}
    WordCard(string line);
    WordCard(const WordCard& obj){ // 复制构造函数
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
    string getMeaningsString(){ // 返回字符串形式的中文解析
        string str;
        for(auto s:meanings){
            str = str + s + " ";
        }
        return str;
    }
    void setStudyStage(int p, int date){ // 设置学习情况
        priority = p;
        if(priority > 3){
            priority = 3;
        }
        studyDate.push_back(date); // 添加学习日期
    }
    void setStudyStage(int p, vector<int> list){ // 设置学习情况
        priority = p;
        if(priority > 3){
            priority = 3;
        }
        studyDate = list; // 重置学习日期为当前日期
    }
    int getPriority() const{
        return priority;
    }
    vector<int> getStudyDate() const{
        return studyDate;
    }
    void dataUpdate(ofstream &file, int option = 1); // 更新单词卡信息
    bool operator<(const WordCard &other) const{ // 大小运算符重载
        for(int i = 0; i < word.size() && i < other.getWord().size(); i++){
            if(tolower(word[i]) != tolower(other.getWord()[i])){ // 按字母顺序比对大小,忽略大小写
                return (tolower(word[i]) < tolower(other.getWord()[i]));
            }
            return word.size() < other.getWord().size();
        }
    }
};

class WordBook{ // 单词书
protected:
    bool creation = false; // 是否创建
    string title; // 单词书标题
    string filePath; // 单词书路径
    vector<WordCard> wordList; // 单词列表
    bool readFile(); // 读取预设单词本文件
public:
    WordBook(){}
    WordBook(string title, string filepath); // 构造函数
    static void printWordList(vector<WordCard> list); // 打印单词列表
    static vector<string> splitLine(string line); // 按空格分割字符串
    bool isCreated() const{ //
        return creation;
    }
    vector<WordCard> getList() const{
        return wordList;
    }
    string getTitle() const{
        return title;
    }
};

class NoteBook:public WordBook{
private:
    vector<WordCard> alphabeticSort(); // 按字母顺序排列
public:
    NoteBook(string title, string filePath):WordBook(title, filePath){} // 构造函数
    void view(); // 查看自定义单词本
    void addWord(WordCard word); // 将单词卡添加至自定义单词本
};



