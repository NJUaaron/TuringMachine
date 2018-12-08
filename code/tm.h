#ifndef _TM_H_
#define _TM_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

extern ofstream con_cout;      //console文件输出
extern ofstream res_cout;      //result文件输出

enum dir
{l, r, n};

//转移函数
struct transi{
    //新、旧状态
    string oldState;
    string newState;
    //新、旧符号
    char oldSym;
    char newSym;
    //方向
    dir direction;
};

//图灵机
class TM{
private:
    vector<string> Q;       //状态集
    vector<char> S;         //输入符号集
    vector<char> T;         //纸带符号集
    string q0;              //初始状态
    char B;                 //空格符号
    vector<string> F;       //终结状态集
    vector<transi> delta;   //转移函数集
    //瞬时描述
    struct {
        string tape;
        int step;
        int head;
        string state;
    } ID;

    void readQ(string s);
    void readS(string s);
    void readT(string s);
    void readF(string s);
    void readTran(string s);

    void printID();

  public:
    void readTM(string file);
    void run(string input_str);
    void writeOutput();
};



#endif
