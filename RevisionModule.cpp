#include "StudyModule.h"
#include <cstdlib>

int RevisionModule::revisionMenu(){ // 复习模块菜单
    //system("cls");
    cout<<"选择复习方式:"<<endl;
    cout<<"1 看词选意"<<endl;
    cout<<"2 单词拼写"<<endl;
    cout<<"` 返回"<<endl;
    char input;
    cin>>input;
    return input;
}

void RevisionModule::controller(){ // 主控制器
    studyProgress(); // 更新学习进度
    char input = revisionMenu();
    for(int i = 0; i < learnedList.size(); i++){
        if(calculateStage(learnedList[i])){ // 计算当前单词今日是否需复习
            revisionList.push_back(&learnedList[i]);
        }
    }
    if(revisionList.size() == 0){ // 没有复习的单词
        cout<<"无复习内容"<<endl;
        return;
    }
    if(input == '`'){
        return;
    }
    int temp = 0;
    if(input == '1'){
        temp = mcQuiz(); // 选择复习题
    }
    if(input == '2'){
        temp = spellingQuiz(); // 拼写复习题
    }
    if(revisionScore > 0){ // 计算此次复习的分数
        revisionScore = (revisionScore + temp) * 0.5;
    }
    else{
        revisionScore = temp;
    }
    cout<<"得分: "<<temp<<"/"<<revisionList.size()<<endl;
}


bool RevisionModule::calculateStage(WordCard &word){ // 0 无需复习
    return true;
    if(word.getPriority() == 0){
        return false;
    }
    if(word.getPriority() == 1){
        if(*(word.getStudyDate().end()) - date == 15){
            return true;
        }
    }
    if(word.getPriority() == 2){
        int stage = word.getStudyDate().size();
        if(stage == 1){
            return date - *(word.getStudyDate().end()) == 1;
        }
        if(stage == 2){
            return date - *(word.getStudyDate().end()) == 4;
        }
        if(stage == 3){
            return date - *(word.getStudyDate().end()) == 15;
        }
    }
    if(word.getPriority() == 3){
        int stage = word.getStudyDate().size();
        if(stage == 1){
            return date - *(word.getStudyDate().end()) == 1;
        }
        if(stage == 2){
            return date - *(word.getStudyDate().end()) == 2;
        }
        if(stage == 3){
            return date - *(word.getStudyDate().end()) == 4;
        }
        if(stage == 4){
            return date - *(word.getStudyDate().end()) == 7;
        }
        if(stage == 5){
            return date - *(word.getStudyDate().end()) == 15;
        }
    }
    return false;
}

int RevisionModule::spellingQuiz(){
    int score = revisionList.size();
    for(auto wptr:revisionList){
        //system("cls");
        for(auto m:wptr->getWord()){
            cout<<m<<" ";
        }
        cout<<endl;
        string input;
        cout<<"输入单词：";
        cin>>input;
        while(input != wptr->getWord()){
           cout<<"错误"<<endl;
           cout<<"1 继续尝试 2 显示答案 ` 返回"<<endl;
           cin>>input;
           if(input == "2"){ // 答错升级，日期重开
               cout<<"正确答案： "<<wptr->getWord()<<endl;
               wrongAnswer(wptr);
               score--;
               break;
           }
           if(input == "`"){
               return score;
           }
           cout<<"输入单词：";
           cin>>input;
        }
        if(input == wptr->getWord()){
            cout<<"正确"<<endl;
            correctAnswer(wptr);
        }
    }
    return score;
}

int RevisionModule::mcQuiz(){
    int score = revisionList.size();
    for(auto wptr:revisionList){
        //system("cls");
        int answer = (rand() % 4);
        string choice[4];
        choice[answer] = wptr->getMeaningsString();
        for(int i = 0; i < 4; i++){
            if(i != answer){
                do{
                    int pick = rand() % wordBook.getList().size();
                    choice[i] = wordBook.getList()[pick].getMeaningsString();
                }
                while(choice[i] == choice[answer]);
            }
        }
        cout<<"选择正确解释 ` 返回"<<endl;
        cout<<wptr->getWord()<<endl;
        for(int i = 0; i < 4; i++){
            cout<<i + 1<<" "<<choice[i]<<endl;
        }
        char input;
        cin>>input;
        if(input == '`'){
            return score;
        }
        if(input - '0' - 1 == answer){
            cout<<"正确"<<endl;
            correctAnswer(wptr);
        }
        else{
            cout<<"错误 正确答案： "<<choice[answer]<<endl;
            wrongAnswer(wptr);
            score--;
        }
    }
    return score;
}

void RevisionModule::correctAnswer(WordCard *wptr){
    if(wptr->getStudyDate().back() != date){
        wptr->setStudyStage(wptr->getPriority(), date);
    }
}

void RevisionModule::wrongAnswer(WordCard *wptr){
    vector<int> newDate;
    newDate.push_back(date);
    wptr->setStudyStage(wptr->getPriority() + 1, newDate);
}

RevisionModule::~RevisionModule(){
    dataWrite();
}

