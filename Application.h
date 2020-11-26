#include "StudyModule.h"
#include <map>

class Application{
private:
    WordBook wordBook;
    vector<NoteBook*> noteBookPool;
    map<string, string>wordBookPool = {
            {"TOEFL", "C:\\Users\\cass\\Desktop\\WordBook\\TOEFL.txt"},
            {"GRE", "C:\\Users\\cass\\Desktop\\WordBook\\GRE_8000_Words.txt"}
    };
    int dailyGoal;
    int revisionInterval;
    bool mainMenu();
    void selectionMenu();
    void importSettings();
    bool noteBookMenu();
public:
    Application();
    ~Application();
};


