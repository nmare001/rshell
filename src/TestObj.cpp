#include "TestObj.h"

TestObj::TestObj(const char* path) {
    this->path = path;
    flag = 'e';
}
TestObj::TestObj(string Spath) {
    flag = 'z';
    if(parse(Spath)) {
        flag = 'e';
    }
    //cout << flag << endl;
    path = Spath.c_str();
}

bool TestObj::run() {
    if(this->exists()){
        cout << "(True)" << endl;
        return true;
    }
    else cout << "(False)" << endl;
    return true;
}

bool TestObj::parse(string &com) {
    stringstream tran (com);
    char d,c;
    if (tran >> d) {
        if(d == '-') {
            if(tran >> c){
                flag = c;
                if(tran >> com) {
                    return false;
                }
            }
        }
        else {
            return true;
        }
    }
    
    return true;
}

bool TestObj::exists() {
    // if (FILE *file = fopen(filePath).c_str(), "r")) {
    //     fclose(file);
    //     return true;
    // } else {
    //     return false;
    // }
    //having a little trouble initializing buf
    
    struct stat buf;
    stat(path, &buf);
    //buf->stat();
    if (flag == 'e') {
        //cout << "parse" << endl;
        if (S_ISREG(buf.st_mode)) {
            //cout << "True";
            return true;
        }
        else if (S_ISDIR(buf.st_mode)) {
            //cout << "True";
            return true;
        }
    }
    else if (flag == 'f') {
        if (S_ISREG(buf.st_mode)) {
            //cout << "True";
            return true;
        }
    }
    else if (flag == 'd') {
        if (S_ISDIR(buf.st_mode)) {
            //cout << "True";
            return true;
        }
    }
    //cout << "False";
    return false;
}