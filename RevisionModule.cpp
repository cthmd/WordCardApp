#include "StudyModule.h"
#include <cstdlib>
#include <conio.h>

int RevisionModule::revisionMenu(){ // 复习模块菜单
    system("cls");
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
        cout<<"1 继续复习所有单词 ` 返回"<<endl;
        char c = getch();
        if(c == '1'){
            for(int i = 0; i < learnedList.size(); i++){
                revisionList.push_back(&learnedList[i]);
            }
        }
        else{
            return;        
        }
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
    cout<<"得分: "<<temp<<endl;
}


bool RevisionModule::calculateStage(WordCard &word){ // 根据记忆曲线设计的复习周期
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

int RevisionModule::spellingQuiz(){ // 拼写复习题
    int score = 0;
    int count = 0;
    for(auto wptr:revisionList){ // 遍历复习列表
        system("cls");
        cout<<wptr->getMeaningsString()<<endl;
        string input;
        cout<<"输入单词：";
        cin>>input;
        while(input != wptr->getWord()){ // 错误回答
           cout<<"错误"<<endl;
           cout<<"1 继续尝试 2 显示答案 ` 返回"<<endl;
           cin>>input;
           if(input == "2"){ // 显示答案，记为错误回答
               cout<<"正确答案： "<<wptr->getWord()<<endl;
               cout<<"按任意键继续"<<endl;
               wrongAnswer(wptr);  // 处理错误回答
               break;
           }
           if(input == "`"){
               return score;
           }
           cout<<"输入单词：";
           cin>>input;
        }
        if(input == wptr->getWord()){ // 回答正确
            cout<<"正确"<<endl;
            cout<<"按任意键继续"<<endl;
            correctAnswer(wptr); // 处理正确回答
            score++;
        }
        count++;
        getch();
    }
    return (score * 100/count);
}

int RevisionModule::mcQuiz(){ // 选择题复习
    int score = 0;
    int count = 0;
    for(auto wptr:revisionList){ // 遍历复习列表
        system("cls");
        int answer = (rand() % 4); // 随机在抽取正确答案的数字
        string choice[4];
        choice[answer] = wptr->getMeaningsString(); // 获得正确选项的文字
        for(int i = 0; i < 4; i++){ // 在单词本中随机抽取余下的选项
            if(i != answer){
                do{
                    int pick = rand() % wordBook.getList().size();
                    choice[i] = wordBook.getList()[pick].getMeaningsString();
                }
                while(choice[i] == choice[answer]); // 确保每个选项的独特性
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
        if(input - '0' - 1 == answer){ // 回答正确
            cout<<"正确"<<endl;
            cout<<"按任意键继续"<<endl;
            correctAnswer(wptr);
            score++;
        }
        else{ // 回答错误
            cout<<"错误 正确答案： "<<choice[answer]<<endl;
            cout<<"按任意键继续"<<endl;
            wrongAnswer(wptr);
        }
        count++;
        getch();
    }
    return (score * 100/count);
}

void RevisionModule::correctAnswer(WordCard *wptr){ // 正确答案处理
    if(wptr->getStudyDate().back() != date){ // 将最新日期加入
        wptr->setStudyStage(wptr->getPriority(), date);
    }
}

void RevisionModule::wrongAnswer(WordCard *wptr){ // 错误答案处理
    vector<int> newDate;
    newDate.push_back(date);
    wptr->setStudyStage(wptr->getPriority() + 1, newDate);  // 重置日期，优先级提高
}

RevisionModule::~RevisionModule(){
    dataWrite();
}

