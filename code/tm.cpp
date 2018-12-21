#include "tm.h"

ofstream con_cout;
ofstream res_cout;

void TM::readQ(string s){
    int start = 1;
    int end = s.find(",", 1);
    while (end != string::npos){
        Q.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(",", start);
    }
    Q.push_back(s.substr(start, s.size()-start-1));
}

void TM::readS(string s){
    for (int i = 1; i < s.size() - 1; i += 2){
        if (s[i] == ','||s[i] == ';'||s[i] == '*'||s[i] == '_'){
            cerr << "S format fault." << endl;
            exit(-1);
        }
        else
            S.push_back(s[i]);
    }
}

void TM::readT(string s){
    for (int i = 1; i < s.size() - 1; i += 2){
        if (s[i] == ','||s[i] == ';'||s[i] == '*'){
            cerr << "T format fault." << endl;
            exit(-1);
        }
        else
            T.push_back(s[i]);
    }
}

void TM::readF(string s){
    int start = 1;
    int end = s.find(",", 1);
    while (end != string::npos){
        F.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(",", start);
    }
    F.push_back(s.substr(start, s.size()-start-1));
}

void TM::readTran(string s){
    transi node;
    int loc[4];     //location of pause
    for (int i = 1, j = 0; i < s.size(); i++){
        if (j >= 4)
            break;
        if (s[i] == ' ')
        {
            loc[j] = i;
            j++;
        }
    }
    node.oldState = s.substr(0, loc[0]);
    node.oldSym = s[loc[0] + 1];
    node.newSym = s[loc[1] + 1];
    if (s[loc[2] + 1] == 'l')
        node.direction = l;
    else if (s[loc[2] + 1] == 'r')
        node.direction = r;
    else if (s[loc[2] + 1] == '*')
        node.direction = n;
    else{
        cerr<<"transition function format fault." << endl;
        exit(-1);
    }
    node.newState = s.substr(loc[3] + 1, s.size() - loc[3] - 1);

    delta.push_back(node);
}

void TM::printID(){
    int width = 2;      //单个字符所占宽度

    con_cout << "Step  : " << ID.step << endl;
    con_cout << "Index :";
    for (int i = 0; i < ID.tape.size(); i++){
        con_cout << " ";
        con_cout << std::left << setw(width) << i;
    }
    con_cout << endl << "Tape  :";
    for (int i = 0; i < ID.tape.size(); i++){
        con_cout << " ";
        if (ID.tape[i] == '_')
            con_cout << std::left << setw(width) << " ";
        else
            con_cout << std::left << setw(width) << ID.tape[i];
    }
    con_cout << endl << "Head  :";
    for (int i = 0; i < ID.head; i++){
        con_cout << " ";
        con_cout << std::left << setw(width) << " ";
    }
    con_cout << " ^" << endl;
    con_cout << "State : " << ID.state << endl;
    con_cout << "---------------------------------------------" << endl;
}

void TM::readTM(string file){
    ifstream input(file, ios::in);
    if(!input){
        cerr << "cannot open tm file." << endl;
        exit(-1);
    }

    string line;
    while (getline(input, line)){
        if (line.size() == 0)
            continue;
        if (line[0] == ';')
            continue;

        //eliminate notation
        for (int i = 1; i < line.size(); i++){
            if (line[i] == ';')
            {
                line = line.substr(0, i);
            }
        }

        //eliminate pause
        line.erase(0, line.find_first_not_of(" "));
        line.erase(line.find_last_not_of(" ") + 1);

        //translate
        if (line[0] == '#')
        {
            if (line[1] == 'Q')
                readQ(line.substr(5, line.size() - 5));
            else if (line[1] == 'S')
                readS(line.substr(5, line.size() - 5));
            else if (line[1] == 'T')
                readT(line.substr(5, line.size() - 5));
            else if (line[1] == 'q' && line[2] == '0')
                q0 = line.substr(6, line.size() - 6);
            else if (line[1] == 'B')
                B = line[5];
            else if (line[1] == 'F')
                readF(line.substr(5, line.size() - 5));
            else{
                cerr << "unknown description of tm." << endl;
                exit(-1);
            }
        }
        else
            readTran(line);
    }

    input.close();
}

void TM::run(string input_str){
    ID.tape = input_str;
    con_cout << "Input: " << ID.tape << endl;

    //check validity of input
    bool validInput = true;
    for (int i = 0; i < ID.tape.size(); i++){
        bool match = false;
        for (int j = 0; j < S.size(); j++){
            if (ID.tape[i] == S[j]){
                match = true;
                break;
            }
        }
        if (!match){
            validInput = false;
            break;
        }
    }
    if (!validInput){
        con_cout << "==================== ERR ====================" << endl;
        con_cout << "The input " << ID.tape << " is illegal" << endl;
        con_cout << "==================== END ====================" << endl;
        ID.tape = string("Error");
        return;
    }

    //run
    con_cout << "==================== RUN ====================" << endl;
    ID.step = 0;
    ID.state = q0;
    ID.head = 0;
    printID();

    while(1){
        //检查是否是终止状态
        bool isFin = false;
        for (int i = 0; i < F.size(); i++){
            if (ID.state == F[i])
                return;
        }

        //精确的转移函数
        for (int i = 0; i < delta.size(); i++){
            if (ID.state == delta[i].oldState&&ID.tape[ID.head] == delta[i].oldSym){
                ID.step++;
                ID.state = delta[i].newState;
                if (delta[i].newSym != '*')
                    ID.tape[ID.head] = delta[i].newSym;
                if (delta[i].direction == l){
                    if (ID.head > 0)
                        ID.head--;
                    else
                        ID.tape = string("_") + ID.tape;
                }
                else if (delta[i].direction == r){
                    if (ID.head >= ID.tape.size()-1)
                        ID.tape = ID.tape + string("_");
                    ID.head++;
                }
                goto END;
            }
        }
        //包含通配符的转移函数
        for (int i = 0; i < delta.size(); i++){
            if (ID.state == delta[i].oldState&&'*' == delta[i].oldSym){
                ID.step++;
                ID.state = delta[i].newState;
                if (delta[i].newSym != '*')
                    ID.tape[ID.head] = delta[i].newSym;
                if (delta[i].direction == l){
                    if (ID.head > 0)
                        ID.head--;
                    else
                        ID.tape = string("_") + ID.tape;
                }
                else if (delta[i].direction == r){
                    if (ID.head >= ID.tape.size()-1)
                        ID.tape = ID.tape + string("_");
                    ID.head++;
                }
                goto END;
            }
        }
        //cerr << "dead lock." << endl;
        //exit(-1);
        return;
    END:
        printID();
    } 
}

void TM::writeOutput(){
    //eliminate "_"
    string s = ID.tape;
    s.erase(0, s.find_first_not_of("_"));
    s.erase(s.find_last_not_of("_") + 1);

    res_cout << s << endl;
}