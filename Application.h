#include "StudyModule.h"
#include <map>

class Application{ // 主程序
private:
    int dailyGoal; // 每日单词学习量
    int revisionInterval; // 复习周期
    int revisionScore; // 复习成绩
    WordBook wordBook; // 当前使用的单词书
    WordBook bigDict; // 大词典
    vector<NoteBook*> noteBookPool; // 自定义单词表列表
    map<string, string>wordBookPool = { // 预设单词书列表
            {"OALD8", "C:\\Users\\cass\\Desktop\\WordBook\\OALD8.txt"},
            {"TOEFL", "C:\\Users\\cass\\Desktop\\WordBook\\TOEFL.txt"},
            {"GRE", "C:\\Users\\cass\\Desktop\\WordBook\\GRE_8000_Words.txt"},
            {"CET-4", "C:\\Users\\cass\\Desktop\\WordBook\\CET4_edited.txt"},
            {"CET-6", "C:\\Users\\cass\\Desktop\\WordBook\\CET6_edited.txt"}
    };
    struct StudyProgress{ // 学习情况
        int date;
        int score;
    };
    vector<StudyProgress> studyProgress;
    bool mainMenu(); // 主菜单
    void selectionMenu(); // 单词书选择菜单
    void importSettings(); // 导入设置
    bool noteBookMenu(); // 自定义单词表菜单
    bool checkNoteBookCreation();
    WordCard* search(string keyWord, WordBook& searchBook); // 单词搜索

public:
    Application();
    ~Application();
};


