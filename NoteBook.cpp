#include "WordBook.h"

void NoteBook::view(){ // 查看自定义单词本
    int j = 0;
    char input = 0;
    vector<WordCard> displayList = wordList;
    string order = "c"; // 记录排序方式
    while(input != '`'){
        system("cls");
        cout<<"选择单词: "<<endl;
        cout<<"[ 前一页 ] 后一页 ` 退出 a 字母顺序 c 时间顺序 r 倒序"<<endl;
        for(int i = 0; i < 10; i++){ // 每页展示十个单词
            if(j*10+i < displayList.size()){
                cout<<i<<" ";
                cout<<displayList[10*j+i].getWord()<<" "<<displayList[10*j+i].getMeaningsString()<<endl;
            }
        }
        cin>>input;
        if(input == ']'){ // 后一页
            j++;
            if(j * 10 > displayList.size()){
                j = displayList.size() / 10;
            }
        }
        if(input == '['){ // 前一页
            j--;
            if(j < 0){ // 第一页
                j = 0;
            }
        }
        if(input == 'a'){ // 字母顺序
            displayList = alphabeticSort(); // 字母顺序排序
            j = 0;
            order = "a";
        }
        if(input == 'c'){ // 时间顺序
            displayList = wordList;
            j = 0;
            order = "c";
        }
        if(input == 'r'){ // 逆序
            reverse(displayList.begin(), displayList.end());
            j = 0;
            order = order + "r";
        }
        if(input >= '0' && input <= '9'){ // 选择单词
            //systme('cls');
            WordCard temp = displayList[10*j+input-'0'];
            cout<<temp.getWord()<<endl;
            cout<<temp.getPhonetic()<<endl;
            cout<<temp.getMeaningsString()<<endl;
            cout<<endl<<endl;
            cout<<"1 删除 `返回"<<endl;
            cin>>input;
            if(input == '`'){
                input = 0;
                continue;
            }
            if(input == '1'){ // 删除当前单词
                for(int i = 0; i < wordList.size(); i++){
                    if(temp.getWord() == wordList[i].getWord()){
                        wordList.erase(wordList.begin() + i);
                        break;
                    }
                }
            }
            if(order == "c"){ // 展示时间顺序
                displayList = wordList;
            }
            else{ // 展示字母顺序
                displayList = alphabeticSort();
            }
            if(order.size() == 2){ // 逆序
                reverse(displayList.begin(), displayList.end());
            }
        }
    }
}

vector<WordCard> NoteBook::alphabeticSort(){ // 字母顺序排序
    vector<WordCard> alphabeticList = wordList;
    sort(alphabeticList.begin(), alphabeticList.end());
    return alphabeticList;
}

void NoteBook::addWord(WordCard word){ // 向当前单词本添加单词
    for(auto w:wordList){
        if(word.getWord() == w.getWord()){ // 查找是否已存在
            return;
        }
    }
    wordList.push_back(word);
}

