#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool IsDigit(char c){
    return c >= '0' && c <= '9';
}

int FindProcessingTime(const string &s){
    string num; int x = s.find_first_of("0123456789");
    while (IsDigit(s[x])) num.push_back(s[x++]);
    return stoi(num);
}

int FindPasswordLength(){
    for(int i = 1; i <= 20; ++i){
        string s(i, 'A');
        cout << s << endl;
        string line; getline(cin, line);
        if (line == "ACCESS GRANTED") return -1;
        if (FindProcessingTime(line) != 5) return i;
    }
    return 0;
}

int main(){
    string all_chars = "";
    for(int i = 0; i < 26; i++){
        all_chars.push_back('a' + i);
        all_chars.push_back('A' + i);
    }
    for(int i = 0; i <= 9; i++){
        all_chars.push_back('0' + i);
    }

    int password_length = FindPasswordLength();
    if (password_length == -1){ return 0; }
    string password(password_length, 'A');
    for(int i = 0, processing_time = 14; i < password_length; ++i, processing_time += 9)
        for(char c : all_chars){
            password[i] = c; cout << password << endl;
            string line; getline(cin, line);
            if (line == "ACCESS GRANTED") return 0;
            if (FindProcessingTime(line) != processing_time) break;
        }
}