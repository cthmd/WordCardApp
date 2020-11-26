#include "Application.h"

Application::Application():wordBook(){
    //system("cls");
    importSettings();
    while(!mainMenu()){}
}

Application::~Application(){
    ofstream settingsFile;
    settingsFile.open("C:\\Users\\cass\\Desktop\\WordBook\\Settings.txt");
    settingsFile<<wordBook.getTitle()<<endl;
    settingsFile<<dailyGoal<<endl; // 每日单词量
    settingsFile<<revisionInterval<<endl; // 复习周期
    settingsFile.close();
}

void Application::importSettings(){
    ifstream settingsFile("C:\\Users\\cass\\Desktop\\WordBook\\Settings.txt");
    if(settingsFile){
        cout<<"in"<<endl;
        string line;
        getline(settingsFile, line);
        wordBook = WordBook(line, wordBookPool[line]);
        getline(settingsFile, line);
        dailyGoal = stoi(line);
        getline(settingsFile, line);
        revisionInterval = stoi(line);
    }
}

bool Application::mainMenu(){
    //system("cls");
    cout<<"Options:"<<endl;
    cout<<"1 选择单词书"<<endl;
    if(wordBook.isCreated()){
        cout<<"2 单词学习"<<"("<<wordBook.getTitle()<<")"<<endl;
    }
    else{
        cout<<"2 单词学习"<<endl;
    }
    if(wordBook.isCreated()){
        cout<<"3 单词复习"<<"("<<wordBook.getTitle()<<")"<<endl;
    }
    else{
        cout<<"3 单词复习"<<endl;
    }
    cout<<"4 查词"<<endl;
    cout<<"5 单词本"<<endl;
    cout<<"0 退出"<<endl;
    int userOption;
    cin>>userOption;
    switch(userOption){
        case 1:{
            selectionMenu();
            break;
        }
        case 2:{
            if(!wordBook.isCreated()){
                cout<<"请选择单词书"<<endl;
                return false;
            }
            StudyModule studyModule(wordBook);
            studyModule.controller(dailyGoal, noteBookPool);
            break;
        }
        case 3:{
            if(!wordBook.isCreated()){
                cout<<"请选择单词书"<<endl;
                return false;
            }
            RevisionModule revisionModule(wordBook);
            revisionModule.controller();
            break;
        }
        case 4:{
            string input;
            cin>>input;
            WordCard word(input);
            noteBookPool[0]->addWord(word);
            break;
        }
        case 5:{
            while(!noteBookMenu());
            break;
        }
        case 0:{
            return true;
        }
    }
    return false;
}

bool Application::noteBookMenu(){
    //system("cls");
    cout<<"自定义单词表:"<<endl;
    cout<<"1 查看"<<endl;
    cout<<"2 创建"<<endl;
    cout<<"3 删除"<<endl;
    cout<<"0 返回"<<endl;
    int userOption;
    cin>>userOption;
    switch(userOption){
        case 0:{
            return true;
        }
        case 1:{
            if(noteBookPool.size() == 0){
                cout<<"无单词表"<<endl;
                return false;
            }
            cout<<"选择单词表: "<<endl;
            for(int i = 0; i < noteBookPool.size(); i++){
                cout<<i + 1<<" "<<noteBookPool[i]->getTitle()<<endl;
            }
            int input;
            cin>>input;
            if(input == 0) break;
            else{
                noteBookPool[input - 1]->view();
            }
            break;
        }
        case 2:{
            cout<<"创建新单词表"<<endl;
            cout<<"命名:";
            string input;
            cin>>input;
            NoteBook *ptr = new NoteBook(input);
            noteBookPool.push_back(ptr);
            break;
        }
        case 3:{
            if(noteBookPool.size() == 0){
                cout<<"无单词表"<<endl;
                return false;
            }
            cout<<"删除单词表"<<endl;
            for(int i = 0; i < noteBookPool.size(); i++){
                cout<<i + 1<<" "<<noteBookPool[i]->getTitle()<<endl;
            }
            int input;
            cin>>input;
            cout<<"确认删除"<<noteBookPool[input - 1]->getTitle()<<"? 1 确认 0 返回"<<endl;
            int confirmation;
            cin>>confirmation;
            if(confirmation){
                noteBookPool.erase(noteBookPool.begin() + input - 1);
            }
            break;
        }
    }
    return false;
}

void Application::selectionMenu(){
    //system("cls");
    cout<<"选择单词书:"<<endl;
    cout<<"1 TOEFL"<<endl;
    cout<<"2 GRE"<<endl;
    cout<<"3 CET-6"<<endl;
    cout<<"0 Return"<<endl;
    int userOption;
    cin>>userOption;
    switch(userOption){
        case 0:{
            return;
        }
        case 1:{
            wordBook = WordBook("TOEFL", wordBookPool["TOEFL"]);
            break;
        }
        case 2:{
            wordBook = WordBook("GRE", wordBookPool["GRE"]);
            break;
        }
        case 3:{
            break;
        }
    }
}