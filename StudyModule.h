#include <ctime>
#include <algorithm>
#include "WordBook.h"

class StudyModule{ // 学习模块
protected:
    int date; // 当前日期
    WordBook wordBook; // 当前单词本
    vector<WordCard> learnedList; // 已学习单词列表
    vector<WordCard> unlearnList; // 未学习单词列表

    void studyProgress(); // 更新学习进度
    bool display(WordCard &word, vector<NoteBook*> &noteBookPool); // 单词卡展示
    void dataWrite(); // txt中写入学习进度
    void dataRead(string filePath); // txt中读入学习进度
public:
    StudyModule(){}
    StudyModule(WordBook &currentBook);
    ~StudyModule(){
        dataWrite();
    }
    int controller(int round, vector<NoteBook*> &noteBookPool); // 学习模块控制器
};

class RevisionModule: public StudyModule{ // 复习模块
private:
    vector<WordCard*> revisionList; // 需复习单词列表
    int revisionMenu(); // 复习模块菜单
    bool calculateStage(WordCard &word); // 根据记忆曲线计算需复习的单词
    int mcQuiz(); // 选择题复习
    int spellingQuiz(); // 拼写复习
    void correctAnswer(WordCard *wptr); // 正确答案处理
    void wrongAnswer(WordCard *wptr); // 错误答案处理
public:
    int revisionScore = -1; // 复习分数
    RevisionModule(){}
    RevisionModule(WordBook &currentBook):StudyModule(currentBook){}
    ~RevisionModule();
    void controller(); // 复习模块控制器
};



