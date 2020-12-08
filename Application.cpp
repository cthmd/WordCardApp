#include "Application.h"

Application::Application():wordBook(){
    //system("cls");
    importSettings();
    while(!mainMenu()){} // 主菜单循环
}

Application::~Application(){
    ofstream settingsFile;
    settingsFile.open("C:\\Users\\cass\\Desktop\\WordBook\\Settings.txt");
    settingsFile<<wordBook.getTitle()<<endl;
    for(auto n:noteBookPool){
        settingsFile<<n->getTitle()<<" ";
    }
    settingsFile<<endl;
    settingsFile<<dailyGoal<<endl; // 每日单词量
    settingsFile<<revisionInterval<<endl; // 复习周期
    for(auto s:studyProgress){
        settingsFile<<s.date;
        settingsFile<<" "<<s.score<<endl;
    }
    settingsFile.close();
    for(auto n:noteBookPool){
        ofstream noteBookFile;
        noteBookFile.open("C:\\Users\\cass\\Desktop\\WordBook\\" + n->getTitle() + ".txt");
        for(auto w:n->getList()){
            w.dataUpdate(noteBookFile, 2);
        }
        noteBookFile.close();
    }
    string fileName = "studyReport";
    ofstream recordFile;
    recordFile.open("C:\\Users\\cass\\Desktop\\WordBook\\" + fileName + ".txt", ios_base::app);
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    recordFile<<wordBook.getTitle()<<" ";
    recordFile<<(1900 + currentTime->tm_year)<<"/";
    recordFile<<(currentTime->tm_mon + 1)<<"/";
    recordFile<<currentTime->tm_mday<<" ";
    recordFile<<revisionScore<<endl;
    recordFile.close();
}

void Application::importSettings(){ // 导入预设设定
    ifstream settingsFile("C:\\Users\\cass\\Desktop\\WordBook\\Settings.txt");
    if(settingsFile){ // 读取配置文件
        string line;
        getline(settingsFile, line);
        wordBook = WordBook(line, wordBookPool[line]);
        getline(settingsFile, line);
        for(auto n:WordBook::splitLine(line)){
            NoteBook *ptr = new NoteBook(n, "C:\\Users\\cass\\Desktop\\WordBook\\" + n + ".txt");
            noteBookPool.push_back(ptr);
        }
        getline(settingsFile, line);
        dailyGoal = stoi(line);
        getline(settingsFile, line);
        revisionInterval = stoi(line);
        while(getline(settingsFile, line)){ // 读取学习报告
            vector<string>result = WordBook::splitLine(line);
            struct StudyProgress s;
            s.date = stoi(result[0]);
            s.score = stoi(result[1]);
            studyProgress.push_back(s);
        }
    }
}

bool Application::mainMenu(){ // 主菜单
    //system("cls");
    cout<<"选项:"<<endl;
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
    cout<<"6 学习报告"<<endl;
    cout<<"7 设置"<<endl;
    cout<<"` 退出"<<endl;
    char userOption;
    cin>>userOption;
    switch(userOption){
        case '1':{ // 单词书选择
            selectionMenu();
            break;
        }
        case '2':{ // 学习模块
            if(!wordBook.isCreated()){
                cout<<"请选择单词书"<<endl;
                return false;
            }
            StudyModule studyModule(wordBook);
            studyModule.controller(dailyGoal, noteBookPool);
            break;
        }
        case '3':{ // 复习模块
            if(!wordBook.isCreated()){
                cout<<"请选择单词书"<<endl;
                return false;
            }
            RevisionModule revisionModule(wordBook);
            revisionModule.controller();
            revisionScore = revisionModule.revisionScore;
            break;
        }
        case '4':{ // 搜索模块
            string input = "";
            while(input != "`"){
                cout << "输入单词: " << endl;
                cin >> input;
                while(input != "`"){
                    WordCard *wptr = search(input, wordBook); // 查询单词
                    if(wptr != NULL){ // 单词展示
                        //system("cls");
                        cout << wptr->getWord() << endl;
                        cout << wptr->getPhonetic() << endl;
                        cout << wptr->getMeaningsString() << endl;
                        cout<<endl<<endl;
                        cout<<"9 添加至单词本 ` 返回"<<endl;
                        char option;
                        cin>>option;
                        if(option == '9'){ // 添加至单词表
                            if(noteBookPool.size() == 0){
                                cout<<"请先创建单词表"<<endl;
                            }
                            else{
                                cout << "添加至: ";
                                for(int i = 0; i < noteBookPool.size(); i++){
                                    cout<<i + 1<< " " << noteBookPool[i]->getTitle() << endl;
                                }
                                cin>>option;
                                if(option > '0' && option - '0' <= noteBookPool.size()){
                                    noteBookPool[option - '0' - 1]->addWord(*wptr);
                                }
                            }
                        }
                        delete wptr;
                        break;
                    }else{
                        cout << "没有找到 ` 返回" << endl;
                        break;
                    }
                }
            }
            break;
        }
        case '5':{ // 自定义单词表模块
            while(!noteBookMenu());
            break;
        }
        case '6':{ // 学习报告
            char input;
            cin>>input;
            while(input != '`'){
                cout<<"复习时间   复习分数"<<endl;
                ifstream textFile;
                string line;
                textFile.open("C:\\Users\\cass\\Desktop\\WordBook\\studyReport.txt");
                while(getline(textFile, line)){ // 读取单词、优先级、学习日期
                    vector<string> result = WordBook::splitLine(line);
                    cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<endl;
                }
                textFile.close();
            }
            break;
        }
        case '7':{ //
            cout<<"更改设置 输入 “1” 或 “2” + “空格” + “数值”"<<endl;
            cout<<"1 设置单词学习量"<<endl;
            cout<<"2 设置复习周期"<<endl;
            cout<<"3 导入单词书"<<endl;
            cout<<"` 返回"<<endl;
            string input;
            cin>>input;
            vector<string> result = WordBook::splitLine(input);
            if(result[0] == "1"){
                try{
                    dailyGoal = stoi(result[1]);
                    cout<<"设置成功"<<endl;
                }
                catch(...){cout<<"设置失败"<<endl;}
            }
            else if(result[0] == "2"){
                try{
                    revisionInterval = stoi(result[1]);
                    cout<<"设置成功"<<endl;
                }
                catch(...){cout<<"设置失败"<<endl;}
            }
            else if(result[0] == "`"){
                break;
            }
            else{
                cout<<"设置失败"<<endl;
                break;
            }
        }
        case '`':{
            return true;
        }
    }
    return false;
}

bool Application::noteBookMenu(){ // 自定义单词表菜单
    //system("cls");
    cout<<"自定义单词表:"<<endl;
    cout<<"1 查看"<<endl;
    cout<<"2 创建"<<endl;
    cout<<"3 删除"<<endl;
    cout<<"4 复习"<<endl;
    cout<<"` 返回"<<endl;
    char userOption;
    cin>>userOption;
    switch(userOption){
        case '`':{
            return true;
        }
        case '1':{ // 查看现有单词表
            if(!checkNoteBookCreation()){
                return false;
            }
            char input;
            cin>>input;
            if(input == '`') break;
            if(input >= '1' && input <= '9'){ // 进入所选单词表
                noteBookPool[input - '0' - 1]->view();
            }
            break;
        }
        case '2':{ // 创建新单词表
            cout<<"创建新单词表"<<endl;
            cout<<"命名:";
            string input;
            cin>>input;
            NoteBook *ptr = new NoteBook(input, "C:\\Users\\cass\\Desktop\\WordBook\\" + input + ".txt");
            noteBookPool.push_back(ptr); // 添加至单词表列表
            break;
        }
        case '3':{ // 删除已有单词表
            if(!checkNoteBookCreation()){
                return false;
            }
            int input;
            cin>>input;
            if(input > 0 && input < noteBookPool.size()){
                cout<<"确认删除"<<noteBookPool[input - 1]->getTitle()<<"? 1 确认 0 返回"<<endl;
            }
            int confirmation;
            cin>>confirmation;
            if(confirmation){ // 从单词表列表中去除
                noteBookPool.erase(noteBookPool.begin() + input - 1);
            }
            break;
        }
    }
    return false;
}

bool Application::checkNoteBookCreation(){
    if(noteBookPool.size() == 0){
        cout<<"无单词表"<<endl;
        return false;
    }
    cout<<"选择单词表: "<<endl;
    for(int i = 0; i < noteBookPool.size(); i++){
        cout<<i + 1<<" "<<noteBookPool[i]->getTitle()<<endl;
    }
    return true;
}

void Application::selectionMenu(){ // 单词书选择菜单
    //system("cls");
    cout<<"选择单词书:"<<endl;
    cout<<"1 TOEFL"<<endl;
    cout<<"2 GRE"<<endl;
    cout<<"3 CET-4"<<endl;
    cout<<"4 CET-6"<<endl;
    cout<<"` 返回"<<endl;
    char userOption;
    cin>>userOption;
    switch(userOption){ // 构造选中的预设单词书
        case '`':{
            return;
        }
        case '1':{
            wordBook = WordBook("TOEFL", wordBookPool["TOEFL"]);
            break;
        }
        case '2':{
            wordBook = WordBook("GRE", wordBookPool["GRE"]);
            break;
        }
        case '3':{
            wordBook = WordBook("CET-4", wordBookPool["CET-4"]);
            break;
        }
        case '4':{
            wordBook = WordBook("CET-6", wordBookPool["CET-6"]);
            break;
        }
    }
}

WordCard* Application::search(string keyWord, WordBook& searchBook){ // 单词查找
    if(searchBook.isCreated()){ // 在当前学习的单词书中查找
        vector<WordCard> tempList = searchBook.getList();
        for(int i = 0; i < tempList.size(); i++){
            if(keyWord == tempList[i].getWord()){ // 查询成功，创建副本
                WordCard* ptr = new WordCard(tempList[i]);
                return ptr;
            }
        }
    }
    if(searchBook.getTitle() == "OALD8"){ // 查询失败
        return nullptr;
    }
    bigDict = WordBook("OALD8", wordBookPool["OALD8"]); // 创建牛津高阶英汉词典
    return search(keyWord, bigDict); // 在牛津高阶英汉词典中查找
}
