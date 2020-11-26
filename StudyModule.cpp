#include <ctime>
#include <algorithm>
#include "StudyModule.h"

StudyModule::StudyModule(WordBook &currentBook){
    wordBook = currentBook;
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    date = (currentTime->tm_year - 120) * 365 + currentTime->tm_yday;
}

bool StudyModule::display(WordCard &word, vector<NoteBook*> &noteBookPool){
    //system("cls");
    cout<<word.getWord()<<endl;
    cout<<word.getPhonetic()<<endl;
    for(auto m:word.getMeanings()){
        cout<<m<<" ";
    }
    cout<<endl<<endl;
    cout<<"1 太简单 2 还需要复习 3 新单词"<<endl;
    cout<<"9 添加至单词本 0 返回"<<endl;
    int input;
    cin>>input;
    if(input == 9){
        if(noteBookPool.size() == 0){
            cout<<"请先创建单词表"<<endl;
        }
        else{
            cout << "添加至: ";
            for(int i = 0; i < noteBookPool.size(); i++){
                cout << i + 1 << " " << noteBookPool[i]->getTitle() << endl;
            }
            cin >> input;
            noteBookPool[input - 1]->addWord(word);
        }
        cout<<"1 太简单 2 还需要复习 3 新单词"<<endl;
        cin>>input;
    }
    if(input >= 1 && input <= 3){
        word.setStudyStage(input, date);
        learnedList.push_back(word);
    }
    return input == 0; // true返回
}

void StudyModule::controller(int round, vector<NoteBook*> &noteBookPool){
    studyProgress();
    random_shuffle(unlearnList.begin(), unlearnList.end());
    for(int i = 0; i < round; i++){
        if(display(unlearnList[i], noteBookPool)){ // 返回菜单
            return;
        }
    }
}

void StudyModule::dataWrite(){
    string fileName = wordBook.getTitle();
    ofstream recordFile("C:\\Users\\cass\\Desktop\\WordBook\\" + fileName + "_record.txt");
    for(auto w:learnedList){
        recordFile<<w.getWord()<<" ";
        recordFile<<w.getPriority()<<" ";
        for(auto d:w.getStudyDate()){
            recordFile<<d<<" ";
        }
        recordFile<<endl;
    }
    recordFile.close();
}

void StudyModule::dataRead(string filePath){
    ifstream textFile;
    string line;
    textFile.open(filePath);
    while(getline(textFile, line)){
        string word;
        stringstream input(line);
        string out;
        int priority = 0;
        vector<int> studyDate;
        for(int i = 0; input>>out; i++){
            if(i == 0){
                word = out;
            }
            else if(i == 1){
                priority = stoi(out);
            }
            else{
                studyDate.push_back(stoi(out));
            }
        }
        int i = 0;
        for(auto w:unlearnList){
            if(w.getWord() == word){
                break;
            }
            i++;
        }
        learnedList.push_back(unlearnList[i]);
        learnedList.back().setStudyStage(priority, studyDate);
        unlearnList.erase(unlearnList.begin() + i);
    }
    textFile.close();
}

void StudyModule::studyProgress(){
    unlearnList = wordBook.getList();
    string fileName = wordBook.getTitle();
    dataRead("C:\\Users\\cass\\Desktop\\WordBook\\" + fileName + "_record.txt");
}
