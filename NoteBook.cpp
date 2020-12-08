#include "WordBook.h"

void NoteBook::view(){
    int j = 0;
    char input = 0;
    vector<WordCard> displayList = wordList;
    string order = "c";
    while(input != '`'){
        //system("cls");
        cout<<"选择单词: "<<endl;
        cout<<"[ 前一页 ] 后一页 ` 退出 a 字母顺序 c 时间顺序 r 倒序"<<endl;
        for(int i = 0; i < 10; i++){
            if(j*10+i < displayList.size()){
                cout<<i<<" ";
                cout<<displayList[10*j+i].getWord()<<" "<<displayList[10*j+i].getMeaningsString()<<endl;
            }
        }
        cin>>input;
        if(input == ']'){
            j++;
        }
        if(input == '['){
            j--;
            if(j == 0) j = 0;
        }
        if(input == 'a'){ // 字母顺序
            displayList = alphabeticSort();
            j = 0;
            order = "a";
        }
        if(input == 'c'){ // 时间顺序
            displayList = wordList;
            j = 0;
            order = "c";
        }
        if(input == 'r'){
            reverse(displayList.begin(), displayList.end());
            j = 0;
            order = order + "r";
        }
        if(input >= '0' && input <= '9'){
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
            if(input == '1'){
                for(int i = 0; i < wordList.size(); i++){
                    if(temp.getWord() == wordList[i].getWord()){
                        wordList.erase(wordList.begin() + i);
                        break;
                    }
                }
            }
            if(order == "c"){
                displayList = wordList;
            }
            else{
                displayList = alphabeticSort();
            }
            if(order.size() == 2){
                reverse(displayList.begin(), displayList.end());
            }
        }
    }
}

vector<WordCard> NoteBook::alphabeticSort(){
    vector<WordCard> alphabeticList = wordList;
    sort(alphabeticList.begin(), alphabeticList.end());
    return alphabeticList;
}

void NoteBook::addWord(WordCard word){
    wordList.push_back(word);
}

