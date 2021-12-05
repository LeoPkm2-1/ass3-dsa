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
    int blockLevel=0;
    SymbolHashing hash;
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
            if(configinfor[0]=='Q'){    // quadratic
                cout<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<"--"<<configinfor[3]<<endl;
                hash.probing=configinfor[0];
                hash.capacity=configinfor[1];
                hash.level_Hashlist.assign(hash.capacity,'-');
                hash.c1=configinfor[2];
                hash.c2=configinfor[3];
                hash.Hashtable=new Symbol[hash.capacity];


            }else{  // linear or double
                cout<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<endl;
                hash.probing=configinfor[0];
                hash.capacity=configinfor[1];
                hash.level_Hashlist.assign(hash.capacity,'-');
                //cout<<"0+0"<<hash.level_Hashlist<<"0+0"<<endl;
                //cout<<hash.capacity<<endl;
                hash.c1=configinfor[2];
                hash.Hashtable=new Symbol[hash.capacity];
                
                
            }

        }
        else{
            string component[3];
            int numOfComponent=0;
            if(command_Form_check(line,component,numOfComponent)){  //lệnh dung

                if(component[0].compare("INSERT")==0){
                    if(numOfComponent==2){  // them bien thuong
                        cout<<"-temp--"<<blockLevel<<endl;
                        cout<<component[0]<<"-"<<component[1]<<endl;
                        string id_symbol(component[1]); // get identifier
                        int level_id=blockLevel;
                        U_KEY_NUM num_key =transfer_Name_to_num_Key(id_symbol,level_id);   //get key(int) from identifer
                        int loop=0; //the number that loop through
                        int check=hash.insert_to_hash(num_key,level_id,loop,component[1]);   //get slot avaible
                        if(check>=0){   // da tim thay vi tri
                            cout<<"loop: "<<loop<<"---"<<"max loop:"<<hash.maxLoop<<"---"<<"block:"<<level_id<<"---"<<"check: "<<check<<endl;
                            //hash.Hashtable[check] =false---- da them trong ham insert
                            hash.Hashtable[check].identifier=component[1];  //them ten vao slot
                            hash.Hashtable[check].level=blockLevel; // them block
                            hash.Hashtable[check].type='#'; // them kieu
                            hash.Hashtable[check].paranum=0;    //them tham so
                            // cout<<hash.level_Hashlist.size()<<endl;
                            // cout<<hash.level_Hashlist<<endl;
                            hash.level_Hashlist[check]=((char)(blockLevel+48));     //them block de check
                            cout<<hash.level_Hashlist<<endl;        

                        }
                        else if(check==-1){ //bien da ton tai
                           // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<" giai phong vung nho khi khai bao trung ne : -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            // quang loi
                            Redeclared Redeclaredmessage(component[1]);
                            throw Redeclared(component[1]);

                        }
                        else{   //loi overload
                            // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<" giai phong vung nho khi overload ne: -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            Overflow Overflowmessage(line);
                            throw Overflow(line);

                        }
                        
                    }else{  // them ham 
                        cout<<component[0]<<"-"<<component[1]<<"-"<<component[2]<<endl;
                        string id_symbol(component[1]); // get identifier
                        int level_id=blockLevel;
                        U_KEY_NUM num_key =transfer_Name_to_num_Key(id_symbol,level_id);   //get key(int) from identifer
                        int loop=0; //the number that loop through
                        int check=hash.insert_to_hash(num_key,level_id,loop,component[1]);   //get slot avaible
                        if(check>=0){       //da tim thay vi tri
                            cout<<"loop: "<<loop<<"---"<<"max loop:"<<hash.maxLoop<<"---"<<"block:"<<level_id<<"---"<<"check: "<<check<<endl;
                            hash.Hashtable[check].identifier=component[1];
                            hash.Hashtable[check].level=blockLevel;
                            hash.Hashtable[check].type='F';
                            hash.Hashtable[check].paranum=convert_To_NumR(component[2]);
                            hash.Hashtable[check].signature=initial_signature(hash.Hashtable[check].paranum);
                            //cout<<"para num: "<<hash.Hashtable[check].paranum<<endl;
                            hash.level_Hashlist[check]=((char)(blockLevel+48));
                            cout<<hash.level_Hashlist<<endl;
                        }
                        else if(check==-1){ //bien da ton tai
                           // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<" giai phong vung nho khi khai bao trung ne : -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            // quang loi
                            Redeclared Redeclaredmessage(component[1]);
                            throw Redeclared(component[1]);

                        }
                        else{   //  loi overload
                            // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<" giai phong vung nho khi overload ne: -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            Overflow Overflowmessage(line);
                            throw Overflow(line);

                        }

                    }
                                   
                }
                else if(component[0].compare("ASSIGN")==0){
                    cout<<component[0]<<"-"<<component[1]<<endl;
                }
                else if(component[0].compare("CALL")==0){
                    cout<<component[0]<<"-"<<component[1]<<endl;
                }
                else if(component[0].compare("BEGIN")==0){
                    cout<<component[0]<<endl;//<<"-"<<component[1]<<endl;
                    blockLevel+=1;
                }
                else if(component[0].compare("END")==0){
                    cout<<component[0]<<endl;//<<"-"<<component[1]<<endl;
                    if(blockLevel==0){  // dong khoi nhung khong tim duoc noi bat dau
                        // dong file
                        myFile.close();
                        // giai phong vung nho ne
                        cout<<" giai phong vung nho khi khong tim duoc khoi ne: -- "<<boolalpha<<hash.releaseMemory()<<endl;
                        UnknownBlock UnknownBlockmessage();
                        throw UnknownBlock();

                    }
                    else{   //co the dong khoi
                        int block_delete=blockLevel;
                        int temp=hash.delete_all_identifier_at_level(block_delete);
                        cout<<"the block delete: "<<block_delete<<" - the number have delete: "<<temp<<endl;

                        blockLevel-=1;
                    }
                }
                else if(component[0].compare("LOOKUP")==0){
                    cout<<component[0]<<"-"<<component[1]<<endl;
                    int level_found=blockLevel;
                    //int level_found=3;
                    int slot_find=hash.lookupR(component[1],level_found);
                    cout<<component[1]<<" in slot "<<slot_find<<" at level : "<<level_found<<endl;

                }
                else{ //print
                   cout<<component[0]<<endl;
                    
                }

            }else{ //lenh sai
                // khi lenh sai tien hanh dong file 
                    myFile.close();   
                // giai phong toàn bộ vùng nhớ
                cout<<" giai phong vung nho khi lenh sai : -- "<<boolalpha<<hash.releaseMemory()<<endl;
                //báo lỗi
                InvalidInstruction InvalidInstructionmessage(line);
                throw InvalidInstruction(line);

            }

        }

    }

    if(blockLevel>0){   // loi chua dong khoi
        myFile.close(); 
        cout<<" giai phong vung nho khi chua dong khoi: -- "<<boolalpha<<hash.releaseMemory()<<endl;
        UnclosedBlock UnclosedBlockmessage(blockLevel);
        throw UnclosedBlock(blockLevel);

    }
      // ket thuc thanh cong

    
        cout<<" giai phong vung nho game done: -- "<<boolalpha<<hash.releaseMemory()<<endl;
        
    

    myFile.close();                     // nhớ đóng file sau khi đọc xong
}