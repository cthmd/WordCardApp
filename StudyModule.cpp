#include "StudyModule.h"

StudyModule::StudyModule(WordBook &currentBook){
    wordBook = currentBook; // 设置当前单词书
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    date = (currentTime->tm_year - 120) * 365 + currentTime->tm_yday; // 获取当前日期从2020年1月1日开始计算的天数
}

bool StudyModule::display(WordCard &word, vector<NoteBook*> &noteBookPool){ // 展示单词
    //system("cls");
    cout<<word.getWord()<<endl;
    cout<<word.getPhonetic()<<endl;
    cout<<word.getMeaningsString()<<endl;
    cout<<endl<<endl;
    cout<<"1 太简单 2 还需要复习 3 新单词"<<endl;
    cout<<"9 添加至单词本 ` 返回"<<endl;
    char input;
    cin>>input;
    if(input == '9'){ // 添加至自定义单词表
        if(noteBookPool.size() == 0){ // 当前无单词表
            cout<<"请先创建单词表"<<endl;
        }
        else{ // 选择单词表
            cout << "添加至: ";
            for(int i = 0; i < noteBookPool.size(); i++){
                cout<<i + 1<< " " << noteBookPool[i]->getTitle() << endl;
            }
            cin>>input;
            if(input > '0' && input - '0' <= noteBookPool.size()){
                noteBookPool[input - '0' - 1]->addWord(word);
            }
        }
        cout<<"1 太简单 2 还需要复习 3 新单词"<<endl;
        cin>>input;
    }
    if(input >= '1' && input <= '3'){ // 用户设置难度等级
        word.setStudyStage(input - '0', date);
        learnedList.push_back(word); // 标记为已学
    }
    return input == '`'; // true返回菜单
}

void StudyModule::controller(int round, vector<NoteBook*> &noteBookPool){ // 学习模块控制组件
    studyProgress(); // 更新学习进度
    random_shuffle(unlearnList.begin(), unlearnList.end()); // 乱序
    for(int i = 0; i < round; i++){ // 展示单词
        if(display(unlearnList[i], noteBookPool)){ // 返回菜单
            return;
        }
    }
}

void StudyModule::dataWrite(){ // 写入数据
    string fileName = wordBook.getTitle(); // 读取文件名
    ofstream recordFile("C:\\Users\\cass\\Desktop\\WordBook\\" + fileName + "_record.txt");
    for(auto w:learnedList){ // 写入已学习单词
        w.dataUpdate(recordFile);
    }
    recordFile.close();
}

void StudyModule::dataRead(string filePath){ // 读取数据
    ifstream textFile;
    string line;
    textFile.open(filePath);
    while(getline(textFile, line)){ // 读取单词、优先级、学习日期
        vector<string> result = WordBook::splitLine(line);
        string word = result[0];
        int priority = stoi(result[1]);
        vector<int> studyDate;
        for(int i = 2; i < result.size(); i++){
            studyDate.push_back(stoi(result[i]));
        }
        for(int i = 0; i < unlearnList.size(); i++){ // 在未学习列表中查找文件中的单词
            if(unlearnList[i].getWord() == word){
                learnedList.push_back(unlearnList[i]); // 添加至已学单词
                learnedList.back().setStudyStage(priority, studyDate); // 添加优先级及日期
                unlearnList.erase(unlearnList.begin() + i); // 在未学习列表中去除
                break;
            }
        }
    }
    textFile.close();
}

void StudyModule::studyProgress(){ // 更新学习进度
    unlearnList = wordBook.getList();
    string fileName = wordBook.getTitle();
    dataRead("C:\\Users\\cass\\Desktop\\WordBook\\" + fileName + "_record.txt"); // 读取已学习单词
}
