#include <iostream>
#include <string>
#include <vector>
#include <string>
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
    vector<string> rev;
    
    enc >> rotate;
    cout << rotate << endl;

    while (getline(enc, line)){
        lines.push_back(line);
    }
    
    for (size_t i = lines.size(); i > 0; --i){
        string curr = lines[i-1];
        for (char ind:curr){
            if (islower(ind)){

            }
            //cout << ind << ' ';
        }
        //rev.push_back(lines[i-1]);
        cout << lines[i-1] << endl;
    }

}