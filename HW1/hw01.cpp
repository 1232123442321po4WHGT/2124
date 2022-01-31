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
    vector<string> rev;
    
    enc >> rotate;
    //cout << rotate << endl;

    while (getline(enc, line)){
        lines.push_back(line);
    }
    
    for (size_t i = lines.size(); i > 0; --i){
        string &curr = lines[i-1];
        for (char &ind:curr){
            if (islower(ind)){
                //cout << "lower";
                ind -= rotate;
                //rotating decode by the value at the top of the file
                if (ind < 'a'){
                    //cout << "less than";
                    ind += 26;

                    //cout << ind;
                    //If you rotate to a value below a, you loop back up to z and go from there
                }else{
                    //If it doesn't need to loop back then print as usual
                    //cout << ind;
                }
            }else{
                //Printing all non lowercase characters
                //cout << ind;
            }
        }
        //Creating a new line every time you finish decoding and printing out the line
        cout << curr << endl;
        //cout << endl;
    }
}