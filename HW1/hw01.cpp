#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

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
        for (char &ind:curr){
            if (islower(ind)){
                ind -= rotate;
                if (ind < 'a'){
                    ind += 26;
                }
            }
        }
        cout << curr << endl;
    }
    enc.close();
}