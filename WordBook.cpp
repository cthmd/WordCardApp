#include "WordBook.h"
#include <ctype.h>

WordCard::WordCard(string line){ // 构造函数
    stringstream input(line);
    string out;
    int i = 0;
    while(input>>out){ // 读取文件中的一行
        if(i == 0) word = out;
        if(i == 1){
            if(!isalpha(out[0])){ // 判断是否有音标
                phonetic = out;
            }
            else{
                phonetic = "-";
                meanings.push_back(out); // 获取中文解析
            }
        }
        if(i > 1) meanings.push_back(out); // 获取中文解析
        i++;
    }
}

void WordCard::dataUpdate(ofstream &file, int option){ // 更新文档中的单词卡信息
    if(option == 1){ // 用于复习模块写入已学习单词
        file<<word<<" ";
        file<<priority<<" ";
        for(auto d:studyDate){
            file<<d<<" ";
        }
    }
    if(option == 2){ // 用于更新自定义单词表
        file<<word<<" ";
        file<<phonetic<<" ";
        file<<getMeaningsString()<<" ";
    }
    file<<endl;
}

WordBook::WordBook(string title, string filePath){ // 单词本构造函数
    this->title = title;
    this->filePath = filePath;
    creation = readFile();
}

bool WordBook::readFile(){ // 读取本地文件
    ifstream textFile;
    string line;
    textFile.open(filePath);
    if(!textFile.is_open()){ // 检查文件是否被正确打开
        return false;
    }
    if(textFile){
        while(getline(textFile, line)){
            WordCard word(line); // 将文档信息用于创建单词卡
            wordList.push_back(word); // 加入单词书的单词列表
        }
        textFile.close();
    }
    return true;
}

void WordBook::printWordList(vector<WordCard> list){ // 测试用
    for(auto v:list){
        cout<<v.getWord()<<endl;
    }
}

vector<string> WordBook::splitLine(string line){ // 根据空格分割字符串
    stringstream input(line);
    string out;
    vector<string> result;
    while(input>>out){
        result.push_back(out);
    }
    return result;
}

