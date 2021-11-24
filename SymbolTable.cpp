#include "SymbolTable.h"

void SymbolTable::run(string filename)
{
    cout << "success"<<endl;
    fstream myFile;
    myFile.open(filename,ios::in);  //read mode
    if(myFile.is_open()){   // kiểm tra xem file mở thanh công chưa
        string line;
        while (getline(myFile,line))
        {
            cout<<line<<endl;
        }

        myFile.close();
        
    }
}