#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("publisher.sql");
    ofstream fout("testStr.sql");
    string line;
    getline(fin, line);
    for(int i=0; i< 1000; i++)
    {
        fout << "Insert INTO publisher VALUES ";
        getline(fin,line);
        for(int i=line.size()-1; i>=0; i--)
        {
            if(line[i]==',')
            {
                line[i]=';';
                break;
            }

        }
        fout << line << endl;
        fout << "select name from publisher where name > '...';"<<endl<<endl;
    }
    fout.close();
    fin.close();
}