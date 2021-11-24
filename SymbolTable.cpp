#include "SymbolTable.h"

void SymbolTable::run(string filename)
{
    //cout << "success"<<endl;
    fstream myFile;                 //biến này là biến file
    myFile.open(filename,ios::in);  //mở file ở read mode
    if(myFile.is_open()){           // kiểm tra xem file mở thanh công chưa hàm is_open() == true nếu thành công và false nếu ngược lại
        string line;                // biến này để chứa từng dòng lệnh trong file đọc dc 
        while (getline(myFile,line))        //dùng vòng lặp để đọc file sau đó dòng đọc dc sẽ dc lưu trong biến line 
        {                                   
            cout<<line<<endl;               // xuất dòng đọc dc đang dc lưu trong biến line ra màn hình
        }

        myFile.close();                     // nhớ đóng file sau khi đọc xong
        
    }
}