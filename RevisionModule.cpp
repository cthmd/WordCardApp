#include "StudyModule.h"
#include <cstdlib>

int RevisionModule::revisionMenu(){
    //system("cls");
    cout<<"选择复习方式:"<<endl;
    cout<<"1 看词选意"<<endl;
    cout<<"2 单词拼写"<<endl;
    cout<<"0 返回"<<endl;
    int input;
    cin>>input;
    return input;
}

void RevisionModule::controller(){
    int input = revisionMenu();
    for(int i = 0; i < learnedList.size(); i++){
        if(calculateStage(learnedList[i])){
            revisionList.push_back(&learnedList[i]);
            cout<<(revisionList.back())<<endl;
        }
    }
    if(revisionList.size() == 0){
        cout<<"无复习内容"<<endl;
        return;
    }
    if(input == 0){
        return;
    }
    else if(input == 1){
       mcQuiz();
    }
    else if(input == 2){
        spellingQuiz();
    }
}


bool RevisionModule::calculateStage(WordCard word){ // 0 无需复习
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

void RevisionModule::spellingQuiz(){
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
           cout<<"1 继续尝试 2 显示答案 0 返回"<<endl;
           cin>>input;
           if(stoi(input) == 2){ // 答错升级，日期重开
               wrongAnswer(wptr);
               break;
           }
           if(stoi(input) == 0){
               return;
           }
           cout<<"输入单词：";
           cin>>input;
        }
        cout<<"正确答案： "<<wptr->getWord()<<endl;
    }
}

void RevisionModule::mcQuiz(){
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
        cout<<"选择正确解释 0 返回"<<endl;
        cout<<wptr->getWord()<<endl;
        for(int i = 0; i < 4; i++){
            cout<<i + 1<<" "<<choice[i]<<endl;
        }
        int input;
        cin>>input;
        if(input == 0){
            return;
        }
        if(input - 1 == answer){
            cout<<"正确"<<endl;
        }
        else{
            cout<<"错误 正确答案： "<<choice[answer]<<endl;
            wrongAnswer(wptr);
        }
    }
}

void RevisionModule::wrongAnswer(WordCard *wptr){ // 还无法更新
    vector<int> newDate;
    newDate.push_back(date);
    wptr->setStudyStage(wptr->getPriority() + 1, newDate);
}


