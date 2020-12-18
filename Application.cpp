#include "Application.h"

Application::Application():wordBook(){
    system("cls");
    importSettings();
    while(!mainMenu()){} // 主菜单循环
}

Application::~Application(){
    ofstream settingsFile;
    settingsFile.open(".\\recordfiles\\usersettings\\Settings.txt");
    if(wordBook.isCreated()){
        settingsFile<<wordBook.getTitle()<<endl; 
    }
    else{
        settingsFile<<0<<endl; 
    }
    if(noteBookPool.size() != 0){
        for(auto n:noteBookPool){ // 写入已创建的自定义单词本
            settingsFile<<n->getTitle()<<" ";
        } 
    }
    else{
        settingsFile<<0; 
    }
    settingsFile<<endl;
    settingsFile<<dailyGoal<<endl; // 每日单词量
    settingsFile<<revisionInterval<<endl; // 复习周期
    for(auto b:wordBookPool){ // 写入已加载单词书
        settingsFile<<b.first<<" ";
        settingsFile<<b.second<<endl;
    }
    settingsFile.close();
    for(auto n:noteBookPool){ // 写入自定义单词本修改
        ofstream noteBookFile;
        noteBookFile.open(".\\recordfiles\\usersettings\\" + n->getTitle() + ".txt");
        for(auto w:n->getList()){
            w.dataUpdate(noteBookFile, 2);
        }
        noteBookFile.close();
    }
    string fileName = "studyReport"; // 写入学习报告
    ofstream recordFile;
    recordFile.open(".\\recordfiles\\usersettings\\" + fileName + ".txt", ios_base::app);
    if(revisionScore >= 0){
	    time_t now = time(0);
	    tm* currentTime = localtime(&now);
	    recordFile<<wordBook.getTitle()<<" ";
	    recordFile<<(1900 + currentTime->tm_year)<<"/";
	    recordFile<<(currentTime->tm_mon + 1)<<"/";
	    recordFile<<currentTime->tm_mday<<" ";
	    recordFile<<revisionScore<<endl;
	    recordFile.close();	
    }
}

void Application::importSettings(){ // 导入预设设定
    ifstream settingsFile(".\\recordfiles\\usersettings\\Settings.txt");
    if(settingsFile){ // 读取配置文件
        string line;
        string title;
        getline(settingsFile, title); // 读取单词书
        getline(settingsFile, line); // 读取自定义单词本
        if(line != "0"){
            for(auto n:WordBook::splitLine(line)){
                NoteBook *ptr = new NoteBook(n, ".\\recordfiles\\usersettings\\" + n + ".txt");
                noteBookPool.push_back(ptr);
            }
        }
        getline(settingsFile, line);
        dailyGoal = stoi(line);
        getline(settingsFile, line);
        revisionInterval = stoi(line);
        while(getline(settingsFile, line)){ // 读取学习报告
            vector<string>result = WordBook::splitLine(line);
            wordBookPool[result[0]] = result[1];
        }
        if(title != "0"){
            wordBook = WordBook(title, wordBookPool[title]);
        }
    }
}

bool Application::mainMenu(){ // 主菜单
    system("cls");
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
            int round;
            if(pauseRemain == 0){
                round = dailyGoal;
            }
            else{
                round = pauseRemain;
            }
            pauseRemain = studyModule.controller(round, noteBookPool);
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
                cout << "输入单词:（` 返回） " << endl;
                cin >> input;
                while(input != "`"){

                    WordCard *wptr = search(input, wordBook); // 查询单词
                    if(wptr != NULL){ // 单词展示
                        system("cls");
                        cout << wptr->getWord() << endl;
                        cout << wptr->getPhonetic() << endl;
                        cout << wptr->getMeaningsString() << endl;
                        cout<<endl<<endl;
                        cout<<"0 添加至单词本 ` 返回"<<endl;
                        char option;
                        cin>>option;
                        if(option == '0'){ // 添加至单词本
                            if(noteBookPool.size() == 0){
                                cout<<"请先创建单词本"<<endl;
                            }
                            else{
                                cout << "添加至: "<<endl;
                                for(int i = 0; i < noteBookPool.size(); i++){ // 展示已有单词本列表
                                    cout<<i + 1<< " " << noteBookPool[i]->getTitle() << endl;
                                }
                                cin>>option;
                                if(option > '0' && option - '0' <= noteBookPool.size()){
                                    noteBookPool[option - '0' - 1]->addWord(*wptr);
                                    cout<<"添加成功！"<<endl;
                                }
                            }
                        }
                        delete wptr; // 删除副本
                        break;
                    }else{
                        cout << "没有找到 ` 返回" << endl;
                        break;
                    }
                }
            }
            break;
        }
        case '5':{ // 自定义单词本模块
            while(!noteBookMenu());
            break;
        }
        case '6':{ // 学习报告
            char input = 0;
            while(input != '`'){
                cout<<"单词书   复习时间   复习分数"<<endl;
                ifstream textFile;
                string line;
                textFile.open(".\\settingfiles\\usersettings\\studyReport.txt");
                while(getline(textFile, line)){ // 读取单词、优先级、学习日期
                    vector<string> result = WordBook::splitLine(line);
                    cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<endl;
                }
                textFile.close();
                cin>>input;
            }
            break;
        }
        case '7':{ // 设置菜单
            cout<<"更改设置"<<endl;
            cout<<"1 设置单词学习量"<<endl;
            cout<<"2 导入单词书"<<endl;
            cout<<"` 返回"<<endl;
            string input;
            cin>>input;
            if(input == "1"){
                cout<<"设置单词学习量：";
                cin>>input;
                try{
                    dailyGoal = stoi(input);
                    cout<<"设置成功"<<endl;
                }
                catch(...){cout<<"设置失败"<<endl;}
            }
            else if(input == "2"){
                cout<<"输入名称:"<<endl;
                string title;
                cin>>title;
                cout<<"输入路径:"<<endl;
                cin>>input;
                WordBook test(title, input);
                if(test.isCreated()){ // 查看文件是否被正确创建
                    wordBookPool[title] = input;
                    cout<<"设置成功"<<endl;
                }
                else{
                    cout<<"设置失败"<<endl;
                }
            }
            else if(input == "`"){
                break;
            }
            else{
                cout<<"设置失败"<<endl;
                break;
            }
            break;
        }
        case '`':{
            return true;
        }
    }
    return false;
}

bool Application::noteBookMenu(){ // 自定义单词本菜单
    system("cls");
    cout<<"自定义单词本:"<<endl;
    cout<<"1 查看"<<endl;
    cout<<"2 创建"<<endl;
    cout<<"3 删除"<<endl;
    cout<<"` 返回"<<endl;
    char userOption;
    cin>>userOption;
    switch(userOption){
        case '`':{
            return true;
        }
        case '1':{ // 查看现有单词本
            if(!checkNoteBookCreation()){
                return false;
            }
            char input;
            cin>>input;
            if(input == '`') break;
            if(input >= '1' && input <= noteBookPool.size() + '0'){ // 进入所选单词本
                noteBookPool[input - '0' - 1]->view();
            }
            break;
        }
        case '2':{ // 创建新单词本
            cout<<"创建新单词本"<<endl;
            cout<<"命名:";
            string input;
            cin>>input;
            NoteBook *ptr = new NoteBook(input, ".\\settingfiles\\usersettings\\" + input + ".txt");
            noteBookPool.push_back(ptr); // 添加至单词本列表
            break;
        }
        case '3':{ // 删除已有单词本
            if(!checkNoteBookCreation()){
                return false;
            }
            string input;
            cin>>input;
            int selection;
            try{
                selection = stoi(input);
            }catch(...){
                cout<<"请输入正确选项"<<endl;
                return false;
            }
            if(selection > 0 && selection <= noteBookPool.size()){
                    cout << "确认删除" << noteBookPool[selection - 1]->getTitle() << "? 1 确认 ` 返回" << endl;
                }
                char confirmation;
                cin >> confirmation;
                if(confirmation == '1'){ // 从单词本列表中去除
                    noteBookPool.erase(noteBookPool.begin() + selection - 1);
                }
            break;
        }
    }
    return false;
}

bool Application::checkNoteBookCreation(){ // 检查单词本是否已创建
    if(noteBookPool.size() == 0){
        cout<<"无单词本"<<endl;
        return false;
    }
    cout<<"选择单词本: "<<endl;
    for(int i = 0; i < noteBookPool.size(); i++){
        cout<<i + 1<<" "<<noteBookPool[i]->getTitle()<<endl;
    }
    return true;
}

void Application::selectionMenu(){ // 单词书选择菜单
    cout<<"选择单词书:"<<endl;
    string *temp = new string[wordBookPool.size()];
    int i = 0;
    for(auto b:wordBookPool){ // 打印列表
        if(b.first != "OALD8"){
            cout<<i + 1<<" ";
            cout<<b.first<<endl;
            temp[i] = (b.first);
            i++;  
        }
    }
    cout<<"` 返回"<<endl;
    string input;
    cin>>input;
    int userOption;
    try{
        userOption = stoi(input);
        if(userOption >= 0 && userOption < wordBookPool.size() + 1){ // 创建单词书
            wordBook = WordBook(temp[userOption-1], wordBookPool[temp[userOption-1]]);
        }
        else{
            cout<<"无此单词书"<<endl;
        }
    }catch(...){}
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
