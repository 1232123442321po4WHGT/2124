#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

char decrypt (char& curr_key, int rotate);
void stringDecrypt (string& line, int rotate);

int main(){
    ifstream enc("encrypted.txt");

    if (!enc){
        cerr << "failed to open encrypted.txt";
        exit(1);
    }
    
    string line;
    string ind;
    int rotate;
    vector<string> lines;
    
    enc >> rotate;

    while (getline(enc, line)){
        lines.push_back(line);
    }

    for (size_t i = lines.size(); i > 0; --i){
        string curr = lines[i-1];
        stringDecrypt(curr, rotate);
        cout << curr << endl;
    }
    enc.close();
}

char decrypt(char& curr_key, int rotate){
    curr_key -= rotate;

    if (curr_key < 'a'){
        curr_key += 26;
    } else{}
    return curr_key;
}

void stringDecrypt(string& line, int rotate){
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] > 'a' && line[i] < 'z'){
            line[i] = decrypt(line[i], rotate);
        } 
    }
    
}