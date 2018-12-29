#include "tm.h"
using namespace std;

int main(int argc, char** argv){
    if (argc > 2){
        printf("Too many parameters.\n");
        return 1;
    }
    else if (argc < 2){
        printf("A parameter is needed to assign test file.\n");
        return 1;
    }
    string path = string(argv[1]);
    string tmFile = path + "//test.tm";
    string inputFile = path + "//input.txt";

    TM tm;
    tm.readTM(tmFile);

    //open input file
    ifstream input(inputFile, ios::in);
    if(!input){
        cerr << "cannot open input file." << endl;
        exit(-1);
    }
    //open console file
    con_cout = ofstream(path + "//console.txt", ios::out);
    if(!con_cout){
        cerr << "cannot genetare console file." << endl;
        exit(-1);
    }
    //open result file
    res_cout = ofstream(path + "//result.txt", ios::out);
    if(!res_cout){
        cerr << "cannot generate result file." << endl;
        exit(-1);
    }
    string str;
    while (input >> str){
        tm.run(str);
        tm.writeOutput();
    }

    input.close();
    con_cout.close();
    res_cout.close();
    clog << "Done!" << endl;
    return 0;
}