#include "WordBook.h"

class StudyModule{
protected:
    int date;
    WordBook wordBook;
    vector<WordCard> learnedList;
    vector<WordCard> unlearnList;

    void studyProgress(); // 更新学习进度
    bool display(WordCard &word, vector<NoteBook*> &noteBookPool); // 单词卡
    void dataWrite(); // txt中写入学习进度
    void dataRead(string filePath); // txt中读入学习进度
public:
    StudyModule(){}
    StudyModule(WordBook &currentBook);
    ~StudyModule(){
        dataWrite();
    }
    void controller(int round, vector<NoteBook*> &noteBookPool);
};

class RevisionModule: public StudyModule{
private:
    vector<WordCard*> revisionList;

    int revisionMenu();
    bool calculateStage(WordCard word);
    void mcQuiz();
    void spellingQuiz();
    void wrongAnswer(WordCard *wptr);
public:
    RevisionModule(WordBook &currentBook):StudyModule(currentBook){}
    ~RevisionModule(){
        dataWrite();
    }
    void controller();
};



