#include "StudyModule.h"
#include <map>

class Application{ // 主程序
private:
    int dailyGoal = 20; // 每日单词学习量
    int revisionInterval = 1; // 复习周期
    int pauseRemain = 0; // 暂停时剩下的数量
    int revisionScore = -1; // 复习成绩
    WordBook wordBook; // 当前使用的单词书
    WordBook bigDict; // 大词典
    vector<NoteBook*> noteBookPool; // 自定义单词本列表
    map<string, string>wordBookPool = { // 预设单词书列表
            {"OALD8", ".\\recordfiles\\wordbook\\OALD8.txt"},
            {"TOEFL", ".\\recordfiles\\wordbook\\TOEFL.txt"},
            {"GRE", ".\\recordfiles\\wordbook\\GRE_8000_Words.txt"},
            {"CET-4", ".\\recordfiles\\wordbook\\CET4_edited.txt"},
            {"CET-6", ".\\recordfiles\\wordbook\\CET6_edited.txt"}
    };
    struct StudyProgress{ // 学习情况
        int date;
        int score;
    };
    vector<StudyProgress> studyProgress;
    bool mainMenu(); // 主菜单
    void selectionMenu(); // 单词书选择菜单
    void importSettings(); // 导入设置
    bool noteBookMenu(); // 自定义单词本菜单
    bool checkNoteBookCreation(); // 检查单词本是否已创建
    WordCard* search(string keyWord, WordBook& searchBook); // 单词搜索

public:
    Application();
    ~Application();
};


