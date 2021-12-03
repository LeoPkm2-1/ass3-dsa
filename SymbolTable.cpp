#include "SymbolTable.h"

void SymbolTable::run(string filename)
{
    //cout << "success"<<endl;
    fstream myFile;                 //biến này là biến file
    myFile.open(filename,ios::in);  //mở file ở read mode
    if(!myFile.is_open()){  // kiểm tra xem file mở thanh công chưa hàm is_open() == true nếu thành công và false nếu ngược lại. Trong trường hợp này muốn kiểm tra xem file ko thành công mở
        cout<<"file not open success"<<endl;
    }         
    string line;                // biến này để chứa từng dòng lệnh trong file đọc dc 
    bool hash_config=true;      // biến này để kiểm tra xem là lệnh tạo hàm hash
    while (getline(myFile,line))        //dùng vòng lặp để đọc file sau đó dòng đọc dc sẽ dc lưu trong biến line 
    {               
        if(hash_config){    //dòng đầu tiên luôn là dòng config hash 
            hash_config=false;
            cout<< "lenh hash: "<<endl;
            int configinfor[4];
            if(!congfigcheck(line,configinfor)){
                cout<<"config wrong\n";
                break;
            }
            if(configinfor[0]=='Q'){
                cout<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<"--"<<configinfor[3]<<endl;
            }else{
                cout<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<endl;
            }

        }
        else{
            string component[3];
            int numOfComponent=0;
            cout<<boolalpha<<command_Form_check(line,component,numOfComponent)<<"-"<<count_CharR(line)<<"-"<<line<<endl;
        }
    }

        
        
    

    myFile.close();                     // nhớ đóng file sau khi đọc xong
}