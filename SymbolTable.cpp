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
    int the_number=0;
    while (getline(myFile,line))        //dùng vòng lặp để đọc file sau đó dòng đọc dc sẽ dc lưu trong biến line 
    {               
        if(hash_config){    //dòng đầu tiên luôn là dòng config hash 
            hash_config=false;
            //cout<< "lenh hash: "<<endl; //xoa---
            int configinfor[4];
            if(!congfigcheck(line,configinfor)){
                cout<<(++the_number)<<"---"<<line<<"- config wrong\n";
                break;
            }
            if(configinfor[0]=='Q'){    // quadratic
                cout<<(++the_number)<<"---"<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<"--"<<configinfor[3]<<endl;
                hash.probing=configinfor[0];
                hash.capacity=configinfor[1];
                hash.level_Hashlist.assign(hash.capacity,'-');
                hash.c1=configinfor[2];
                hash.c2=configinfor[3];
                hash.Hashtable=new Symbol[hash.capacity];


            }else{  // linear or double
                cout<<(++the_number)<<"---"<<(char)configinfor[0]<<"--"<<configinfor[1]<<"--"<<configinfor[2]<<endl;
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
                        // cout<<"-temp--"<<blockLevel<<endl; //xoa--- 
                        cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1];
                        string id_symbol(component[1]); // get identifier
                        int level_id=blockLevel;
                        U_KEY_NUM num_key =transfer_Name_to_num_Key(id_symbol,level_id);   //get key(int) from identifer
                        int loop=0; //the number that loop through
                        int ref=0;
                        int check=hash.insert_to_hash(num_key,level_id,loop,ref,component[1]);   //get slot avaible
                        if(check>=0){   // da tim thay vi tri
                            // cout<<"loop: "<<loop<<"---"<<"max loop:"<<hash.maxLoop<<"---"<<"block:"<<level_id<<"---"<<"check: "<<check<<endl; //xoa
                            cout<<" // ------ so loop: "<<loop<<" --- maxloop: "<<hash.maxLoop<<" --- level: "<<level_id<<" --- at slot: "<<check<<endl;
                            //hash.Hashtable[check] =false---- da them trong ham insert
                            hash.Hashtable[check].identifier=component[1];  //them ten vao slot
                            hash.Hashtable[check].level=blockLevel; // them block
                            hash.Hashtable[check].type='#'; // them kieu
                            hash.Hashtable[check].paranum=0;    //them tham so
                            // cout<<hash.level_Hashlist.size()<<endl;
                            // cout<<hash.level_Hashlist<<endl;
                            hash.level_Hashlist[check]=((char)(blockLevel+48));     //them block de check
                            
                            //============================== //xoa
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================
                            hash.numofSymbol+=1;      

                        }
                        else if(check==-1){ //bien da ton tai
                            //============================== //xoa
                            cout<<" // ------ bien da ton tai: "<<ref<<" --- rong: "<<hash.Hashtable[ref].empty<<" --- ten: "<<hash.Hashtable[ref].identifier<<" --- level: "<<hash.Hashtable[ref].level<<" --- type: "<<hash.Hashtable[ref].type<<endl;
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================

                           // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<"\tgiai phong vung nho khi khai bao trung ne : -- "<<boolalpha<<hash.releaseMemory()<<endl<<"\t";
                            // quang loi
                            Redeclared Redeclaredmessage(component[1]);
                            throw Redeclared(component[1]);

                        }
                        else{   //loi overload
                            
                            //============================== //xoa
                            cout<<" // ------ tran bo nho"<<endl;
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================

                            // dong file
                            myFile.close();  
                            //giai phong vung nho ne
                            cout<<"\tgiai phong vung nho khi overload ne: -- "<<boolalpha<<hash.releaseMemory()<<endl<<"\t";
                            Overflow Overflowmessage(line);
                            throw Overflow(line);

                        }
                        
                    }else{  // them ham 
                        cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1]<<"-"<<component[2];
                        if(blockLevel!=0){  // neu khai bao ham trong muc khac 0 => bao loi invaliddeclaration
                            //============================== //xoa
                            cout<<" // ------ khai bao ham tai level: "<<blockLevel<<endl;
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================

                            // dong file
                            myFile.close();
                            // giai phong vung nho ne
                            cout<<"\tgiai phong vung nho khi khaii bao ham o muc khac 0: "<<boolalpha<<hash.releaseMemory()<<endl<<"\t";
                            InvalidDeclaration InvalidDeclarationmessage(component[1]);
                            throw InvalidDeclaration(component[1]);

                        }

                        // khai bao o muc 0
                        string id_symbol(component[1]); // get identifier
                        int level_id=blockLevel;
                        U_KEY_NUM num_key =transfer_Name_to_num_Key(id_symbol,level_id);   //get key(int) from identifer
                        int loop=0; //the number that loop through
                        int ref=0;
                        int check=hash.insert_to_hash(num_key,level_id,loop,ref,component[1]);   //get slot avaible
                        if(check>=0){       //da tim thay vi tri
                            cout<<" // ------ so loop: "<<loop<<" --- maxloop: "<<hash.maxLoop<<" --- level: "<<level_id<<" --- at slot: "<<check<<endl;
                            hash.Hashtable[check].identifier=component[1];
                            hash.Hashtable[check].level=blockLevel;
                            hash.Hashtable[check].type='F';
                            hash.Hashtable[check].paranum=convert_To_NumR(component[2]);
                            hash.Hashtable[check].signature=initial_signature(hash.Hashtable[check].paranum);
                            //cout<<"para num: "<<hash.Hashtable[check].paranum<<endl;
                            hash.level_Hashlist[check]=((char)(blockLevel+48));
                            
                            //============================== //xoa
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================

                            hash.numofSymbol+=1;    
                            //cout<<"----"  <<hash.Hashtable[check].signature<<endl;

                        }
                        else if(check==-1){ //bien da ton tai
                           //============================== //xoa
                            cout<<" // ------ da co 1 thanh phan trung ten tai: "<<ref<<" --- rong: "<<hash.Hashtable[ref].empty<<" --- ten: "<<hash.Hashtable[ref].identifier<<" --- level: "<<hash.Hashtable[ref].level<<" --- type: "<<hash.Hashtable[ref].type<<endl;
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                           //==============================

                           // dong file
                           myFile.close();  
                            //giai phong vung nho ne
                            cout<<"\tgiai phong vung nho khi khai bao trung ne : -- "<<boolalpha<<hash.releaseMemory()<<endl<<"\t";
                            // quang loi
                            Redeclared Redeclaredmessage(component[1]);
                            throw Redeclared(component[1]);

                        }
                        else{   //  loi overload

                            //============================== //xoa
                            cout<<" // ------ tran bo nho"<<endl;
                            cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                            cout<<"\t               : ";
                            for (int i = 0; i < hash.capacity; i++)
                            {
                                cout<<i;
                            }
                            cout<<endl;
                            //==============================

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

                    cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1]<<"-"<<component[2];

                    int assign_type=check_value(component[2]);
                    //cout<<assign_type<<endl;
                    if(assign_type==1||assign_type==2){ //value is num or string
                        int level_found=blockLevel;
                        int slot_id_find=hash.lookupR(component[1],level_found);

                        if(slot_id_find==-1){   //ko tim thay
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi khong tim thay : "<<component[1]<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            //báo lỗi
                            Undeclared Undeclaredmessage(component[1]);
                            throw Undeclared(component[1]);
                        }

                        // tim thay
                        if(hash.Hashtable[slot_id_find].type=='#'){
                            hash.Hashtable[slot_id_find].type=(assign_type==1)?'N':'S';
                            cout<<" // ------ bien: "<<component[1]<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" - da dc suy dien kieu la: "<<hash.Hashtable[slot_id_find].type<<endl;
                        }
                        else if(hash.Hashtable[slot_id_find].type=='N'&&assign_type==1){    //cung la num
                            cout<<"// ------ gan hop le bien: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" with: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<'N'<<endl;
                        }
                        else if(hash.Hashtable[slot_id_find].type=='S'&&assign_type==2){    //cung la string
                            cout<<"// ------ gan hop le bien: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" with: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<'S'<<endl;
                        }
                        else {  //ko hop kieu
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi bien: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" khong hop kieu: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<((assign_type==1)?'N':'S')<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }


                    }
                    else if(assign_type==3){    // value is variable
                        int level_val_found=blockLevel;
                        int slot_val_find=hash.lookupR(component[2],level_val_found);
                        if(slot_val_find==-1){   //ko tim thay value
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi khong tim thay : "<<component[2]<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            //báo lỗi
                            Undeclared Undeclaredmessage(component[2]);
                            throw Undeclared(component[2]);
                        }

                        // tim thay val => tim identifier
                        int level_id_found=blockLevel;
                        int slot_id_find=hash.lookupR(component[1],level_id_found);
                        if(slot_id_find==-1){   //ko tim thay id
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi khong tim thay : "<<component[1]<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            //báo lỗiha
                            Undeclared Undeclaredmessage(component[1]);
                            throw Undeclared(component[1]);
                        }

                        //=> tim thay ca 2 => so kieu
                        char val_type=hash.Hashtable[slot_val_find].type;
                        char id_type=hash.Hashtable[slot_id_find].type;
                        if(val_type==id_type&&id_type=='#'){    // ca 2 deu chu co kieu
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                            throw TypeCannotBeInferred(line);
                            
                        }
                        else if(val_type==id_type){ //ca 2 deu cung kieu
                            cout<<"// ------ gan hop le id: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<"// ------       voi val: "<<hash.Hashtable[slot_val_find].identifier<<" - level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<"\t\t "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                        }
                        else if(val_type=='#'&&id_type!='#'&&id_type!='F'){
                            hash.Hashtable[slot_val_find].type=hash.Hashtable[slot_id_find].type;
                            cout<<" // ------ bien: "<<hash.Hashtable[slot_val_find].identifier<<" - level: "<<hash.Hashtable[slot_val_find].level<<" - at slot: "<<slot_val_find<<" - da dc suy dien kieu la: "<<hash.Hashtable[slot_val_find].type<<endl;

                        }
                        else if(id_type=='#'&&val_type!='#'&&val_type!='F'){
                            hash.Hashtable[slot_id_find].type=hash.Hashtable[slot_val_find].type;
                            cout<<" // ------ bien: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" - da dc suy dien kieu la: "<<hash.Hashtable[slot_id_find].type<<endl;

                        }
                        else{   //2 thang khac kieu
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi bien: "<<hash.Hashtable[slot_id_find].identifier<<" - level: "<<hash.Hashtable[slot_id_find].level<<" - at slot: "<<slot_id_find<<" khong hop kieu voi: ";
                            cout<<hash.Hashtable[slot_val_find].identifier<<" - level: "<<hash.Hashtable[slot_val_find].level<<" - at slot: "<<slot_val_find<<endl;
                            cout<<"\t\t"<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<boolalpha<<hash.releaseMemory()<<endl;
                            
                        }



                    }
                    else if(assign_type==4){    //fucntion call
                        int pos1=component[2].find('(');
                        string functionname(component[2],0,pos1);
                        int level_function_found=0;
                        int slot_function_found=hash.lookupR(functionname,level_function_found);

                        if(slot_function_found==-1){    //ko tim thay ham
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi khong tim thay : "<<functionname<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                            //báo lỗi
                            Undeclared Undeclaredmessage(functionname);
                            throw Undeclared(functionname);
                        }

                        // tim thay ham
                        int numOfpara=hash.Hashtable[slot_function_found].paranum;
                        int numOfargu= num_of_arguments(component[2]);
                        if(numOfargu!=numOfpara){   // so luong tham so truyen vao khac voi so luong tham so thuc cua ham
                            // khi lenh sai tien hanh dong file 
                            myFile.close();   
                            // giai phong toàn bộ vùng nhớ
                            cout<<" // ------ giai phong vung nho khi so luong tham so va so luong doi so khac nhau: "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" - at slot: "<<slot_function_found<<" khong cung so luong tham so kieu: "<<hash.Hashtable[slot_function_found].paranum<<" -vs- "<<numOfargu<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }
                        
                        // so luong tham so va doi so = nhau
                        if(numOfargu==0){   // ham khong tham so
                            //cout<<"xin chao ahihi"<<endl;
                            char functype=hash.Hashtable[slot_function_found].signature[0];
                            int level_function_found=blockLevel;                            
                            int slot_id_found=hash.lookupR(component[1],level_function_found);
                            if(hash.Hashtable[slot_id_found].type=='F'){    // identifier la ham => ko the gan dc => loi mistype
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong vung nho khi ca 2 deu la ham: "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<endl;
                                cout<<" // ------- va :"<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                TypeMismatch TypeMismatchmessage(line);
                                throw TypeMismatch(line);

                            }
                            char id_type=hash.Hashtable[slot_id_found].type;
                            if(id_type==functype&&functype=='#'){       //ca 2 chua co kieu
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong vung nho khi ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" - at slot: "<<slot_function_found<<" - type: "<<hash.Hashtable[slot_function_found].signature[0];
                                cout<<" // ------ "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<" - type: "<<hash.Hashtable[slot_id_found].type<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                TypeMismatch TypeMismatchmessage(line);
                                throw TypeMismatch(line);
                            }
                            else if(id_type==functype){ // cung kieu
                                cout<<"// ------ gan hop le id: "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature[0]<<endl;
                                cout<<"// ------       voi val: "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                                cout<<"\t\t "<<hash.Hashtable[slot_function_found].signature[0]<<" -vs- "<<hash.Hashtable[slot_id_found].type<<endl;

                            }
                            else if(functype=='#'&&id_type!='#'&&id_type!='F'){ // gan gia tri cho ham
                                hash.Hashtable[slot_function_found].signature[0]=id_type;
                                cout<<" // ------ ham: "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" - at slot: "<<slot_function_found<<" - da dc suy dien kieu la: "<<hash.Hashtable[slot_function_found].signature[0]<<endl;
                                cout<<"// ------- "<<hash.Hashtable[slot_function_found].signature<<endl;
                                //InvalidInstruction InvalidInstruction
                            }
                            else if(functype!='#'&&functype!=id_type&&id_type!='F'){
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong khi khong cung kieu "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature[0]<<endl;
                                cout<<" // -------                  voi val la: "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot : "<<slot_id_found<<" - type: "<<hash.Hashtable[slot_id_found].type<<endl;
                                cout<<" // ------  "<<hash.Hashtable[slot_function_found].signature[0]<<" -vs- "<<hash.Hashtable[slot_id_found].type;
                                cout<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                TypeMismatch TypeMismatchmessage(line);
                                throw TypeMismatch(line);
                            }


                        }
                        else if(numOfargu>0){   // ham co  tham so

                            // gọi ham 1 tham so
                            if(numOfargu==1){
                                int num1=component[2].find('(');
                                int num2=component[2].find(')');
                                string argu(component[2],num1+1,num2-num1-1);
                                //cout<<"===="<<argu<<"==="<<endl;
                                int argu_type=check_value(argu);
                                if(argu_type==1||argu_type==2){ // tham so la number hoac string
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // ham dang ko co kiem => gan
                                        hash.Hashtable[slot_function_found].signature[2]=(argu_type==1)?'N':'S';
                                        cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='N'&&argu_type==1){
                                        cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='S'&&argu_type==2){
                                        cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else{   // ko hop kieu
                                        // khi lenh sai tien hanh dong file 
                                        myFile.close();   
                                        // giai phong toàn bộ vùng nhớ
                                        cout<<"\n ----- tham so thu nhat ko cung kieu: "<<hash.Hashtable[slot_function_found].signature[2]<<" -vs- "<<((argu_type==1)?'N':'S')<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }
                                }
                                else if(argu_type==3){  // tham so la bien
                                    int level_temp=blockLevel;
                                    int slot_argu=hash.lookupR(argu,level_temp);
                                    if(slot_argu==-1){  // ko tim thay argument
                                        // khi lenh sai tien hanh dong file 
                                        myFile.close();   
                                        // giai phong toàn bộ vùng nhớ
                                        cout<<"//------ khong tim thay argument: "<<argu<<boolalpha<<" - "<<hash.releaseMemory();
                                        Undeclared Undeclaredmessage(argu);
                                        throw Undeclared(argu);


                                    }
                                    // tim thay argument
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so chua co kieu
                                        if(hash.Hashtable[slot_argu].type=='#'){    // doi so cung chua co kieu
                                            // khi lenh sai tien hanh dong file 
                                            myFile.close();   
                                            // giai phong toàn bộ vùng nhớ
                                            cout<<" // ------ giai phong vung nho khi ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_function_found].signature[2]<<" -vs- "<<hash.Hashtable[slot_argu].type<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                            throw TypeCannotBeInferred(line);
                                        }
                                        else{
                                            hash.Hashtable[slot_function_found].signature[2]=hash.Hashtable[slot_argu].type;
                                            cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                        }
                                        
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]==hash.Hashtable[slot_argu].type){  // tham so cung kieu
                                        cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;

                                    }else{  // tham so khac kieu
                                        // khi lenh sai tien hanh dong file 
                                        myFile.close();   
                                        // giai phong toàn bộ vùng nhớ
                                        cout<<"\n ----- tham so thu nhat ko cung kieu: "<<hash.Hashtable[slot_function_found].signature[2]<<" -vs- "<<hash.Hashtable[slot_argu].type<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }

                                }                            
                            }
                            else { //goi co nhie hon 1 tham so    
                                //cout<<"\n---@ahihi---"<<component[2]<<"---"<<endl;
                                int num1=component[2].find('(');
                                int num2=component[2].find(',');
                                int num2_temp=num2;
                                int num3=component[2].find(')');
                                int numofargu=num_of_arguments(component[2]);                                
                                string* arguarr=new string[numofargu];  // mang tham so
                                for (int i = 0; i < numofargu; i++)     // lay tham so bo vao mang
                                {
                                    if(i==0){   // tham so thu nhat
                                        arguarr[i]=component[2].substr(num1+1,num2-num1-1);
                                        continue;
                                    }
                                    else if(i==numofargu-1){
                                        arguarr[i]=component[2].substr(num2+1,num3-num2-1);
                                        continue;
                                    }
                                    num2_temp=num2;
                                    num2=component[2].find(',',num2+1);
                                    arguarr[i]=component[2].substr(num2_temp+1,num2-num2_temp-1);
                                }


                                for (int i = 0; i < numofargu; i++) // xu ly tung tham so 1
                                {
                                    int argu_type=check_value(arguarr[i]);
                                    if(argu_type==1||argu_type==2){ // tham so la string hoac la number
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){
                                            hash.Hashtable[slot_function_found].signature[2*i+2]=(argu_type==1)?'N':'S';
                                            cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='N'&&argu_type==1){
                                            cout<<" \n---- argument"<<i<<" pass: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='S'&&argu_type==2){
                                            cout<<" \n---- argument"<<i<<" pass: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        }
                                        else{   // ko hop kieu
                                            // khi lenh sai tien hanh dong file 
                                            myFile.close();   
                                            // giai phong toàn bộ vùng nhớ
                                            cout<<"\n ----- tham so thu "<<i<<" ko cung kieu: "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<" -vs- "<<((argu_type==1)?'N':'S')<<" - giao phong: "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] arguarr;
                                            TypeMismatch TypeMismatchmessage(line);
                                            throw TypeMismatch(line);
                                        }
                                    }
                                    else if(argu_type==3){      // tham so la bien
                                        int level_temp=blockLevel;
                                        int slot_argu=hash.lookupR(arguarr[i],level_temp);
                                        if(slot_argu==-1){  // ko tim thay argument
                                            // khi lenh sai tien hanh dong file 
                                            myFile.close();   
                                            // giai phong toàn bộ vùng nhớ
                                            cout<<"//------ khong tim thay argument thu "<<i<<" : "<<arguarr[i]<<boolalpha<<" - giai phong : "<<hash.releaseMemory();
                                            delete[] arguarr;
                                            Undeclared Undeclaredmessage(arguarr[i]);
                                            throw Undeclared(arguarr[i]);

                                        }
                                        // tim thay argument
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){ // tham so chua co kieu
                                            if(hash.Hashtable[slot_argu].type=='#'){    // doi so cung chua co kieu
                                                // khi lenh sai tien hanh dong file 
                                                myFile.close();   
                                                // giai phong toàn bộ vùng nhớ
                                                cout<<" // ------ giai phong vung nho khi ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<" -vs- "<<hash.Hashtable[slot_argu].type<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                                                delete[] arguarr;
                                                TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                                throw TypeCannotBeInferred(line);                                               
                                            }
                                            else{
                                                hash.Hashtable[slot_function_found].signature[2*i+2]=hash.Hashtable[slot_argu].type;
                                                cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                            }
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]==hash.Hashtable[slot_argu].type){  // tham so cung kieu
                                            cout<<" \n----"<<hash.Hashtable[slot_function_found].signature<<endl;
                                        }
                                        else{   // tham so va doi so khong cung kieu
                                            // khi lenh sai tien hanh dong file 
                                            myFile.close();   
                                            // giai phong toàn bộ vùng nhớ
                                            cout<<"\n ----- tham so thu "<<i <<" ko cung kieu: "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<" -vs- "<<hash.Hashtable[slot_argu].type<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] arguarr;
                                            TypeMismatch TypeMismatchmessage(line);
                                            throw TypeMismatch(line);
                                        }

                                    }
                                }
                                delete [] arguarr;   
                                
                               
                            }

                            string id_name=component[1];
                            int level_id_found=blockLevel;
                            int slot_id_found=hash.lookupR(id_name,level_id_found);
                            if(slot_id_found==-1){      //ko tim thay ham
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong vung nho khi khong tim thay : "<<id_name<< " --- trong lenh assign -- "<<boolalpha<<hash.releaseMemory()<<endl;
                                //báo lỗi
                                Undeclared Undeclaredmessage(id_name);
                                throw Undeclared(id_name);

                            }    
                            char id_type_=hash.Hashtable[slot_id_found].type;
                            char function_type_ =hash.Hashtable[slot_function_found].signature[0];
                            if(id_type_==function_type_&&id_type_=='#'){    // ca 2 deu vo kieu
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong vung nho khi ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" - at slot: "<<slot_function_found<<" - type: "<<hash.Hashtable[slot_function_found].signature[0];
                                cout<<" // ------ "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<" - type: "<<hash.Hashtable[slot_id_found].type<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                TypeMismatch TypeMismatchmessage(line);
                                throw TypeMismatch(line);
                            }
                            else if(id_type_==function_type_){  //cung kieu
                                cout<<" // ---- hop le: "<<hash.Hashtable[slot_function_found].signature<<" -vs- "<<hash.Hashtable[slot_id_found].type<<endl;
                            }
                            else if(function_type_=='#'&&id_type_!='#'&&id_type_!='F'){ // gan gia tri cho ham
                                hash.Hashtable[slot_function_found].signature[0]=id_type_;
                                cout<<" ham da dc gian gia tri: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                //InvalidInstruction InvalidInstruction
                            }
                            else if(function_type_!='#'&&function_type_!=id_type_&&id_type_!='F'){
                                // khi lenh sai tien hanh dong file 
                                myFile.close();   
                                // giai phong toàn bộ vùng nhớ
                                cout<<" // ------ giai phong khi khong cung kieu "<<hash.Hashtable[slot_function_found].identifier<<" - level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature[0]<<endl;
                                cout<<" // -------                  voi val la: "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot : "<<slot_id_found<<" - type: "<<hash.Hashtable[slot_id_found].type<<endl;
                                cout<<" // ------  "<<hash.Hashtable[slot_function_found].signature[0]<<" -vs- "<<hash.Hashtable[slot_id_found].type;
                                cout<<" - "<<boolalpha<<hash.releaseMemory()<<endl;
                                TypeMismatch TypeMismatchmessage(line);
                                throw TypeMismatch(line);
                            }
                        }
                        


                    }
                    else{   // assign sai
                        
                        cout<<"lenh sai ahihi"<<endl;
                        
                    }




                }
                else if(component[0].compare("CALL")==0){
                    cout<<component[0]<<"-"<<component[1]<<endl;
                }
                else if(component[0].compare("BEGIN")==0){
                    cout<<(++the_number)<<"---"<<component[0];//<<"-"<<component[1]<<endl;
                    cout<<" // ------ level truoc khi beign: "<<blockLevel<<" --- level sau do: ";
                    blockLevel+=1;
                    cout<<blockLevel<<endl;
                }
                else if(component[0].compare("END")==0){
                    cout<<(++the_number)<<"---"<<component[0];//<<"-"<<component[1]<<endl;
                    if(blockLevel==0){  // dong khoi nhung khong tim duoc noi bat dau
                        // dong file
                        myFile.close();
                        // giai phong vung nho ne
                        cout<<" // ------ giai phong vung nho khi khong tim duoc khoi ne: -- "<<boolalpha<<hash.releaseMemory()<<endl<<"\t";
                        UnknownBlock UnknownBlockmessage();
                        throw UnknownBlock();

                    }
                    else{   //co the dong khoi
                        int block_delete=blockLevel;
                        int temp=hash.delete_all_identifier_at_level(block_delete);
                        cout<<" // ------ the level deleted: "<<block_delete<<" --- the number of identifier have deleted: "<<temp<<endl;
                        blockLevel-=1;
                        //============================== //xoa
                        cout<<"\tHash level list: "<<hash.level_Hashlist<<endl;  
                        cout<<"\t               : ";
                        for (int i = 0; i < hash.capacity; i++)
                        {
                            cout<<i;
                        }
                        cout<<endl;
                        //==============================

                    }
                }
                else if(component[0].compare("LOOKUP")==0){
                    cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1];
                    int level_found=blockLevel;
                    //int level_found=3;
                    int slot_find=hash.lookupR(component[1],level_found);
                    if(slot_find==-1){  //khong tim thay
                        // khi lenh sai tien hanh dong file 
                        myFile.close();   
                        // giai phong toàn bộ vùng nhớ
                        cout<<" // ------ giai phong vung nho khong tim thay : "<<component[1]<< " --- trong lenh lookup -- giai phong: "<<boolalpha<<hash.releaseMemory()<<endl;
                        //báo lỗi
                        Undeclared Undeclaredmessage(component[1]);
                        throw Undeclared(component[1]);

                    }
                    else{   //tim thay tai slot_find
                        // cout<<component[1]<<" in slot "<<slot_find<<" at level : "<<level_found<<endl;
                        cout<<" // ------ tim thay: "<<component[1]<<" --- tai: "<<slot_find<<" --- level: "<<level_found<<endl;

                    }
                    // cout<<component[1]<<" in slot "<<slot_find<<" at level : "<<level_found<<endl;

                }
                else{ //PRINT
                    cout<<(++the_number)<<"---"<<component[0]<<" : ";
                    int empty_node=count_CharR(hash.level_Hashlist,'-');
                    int index=hash.level_Hashlist.find_first_not_of('-');
                    for (int i = 0; i < hash.numofSymbol; i++)
                    {
                        if(i==0){
                            
                            cout<<index<<" "<<hash.Hashtable[index].identifier<<"//"<<hash.Hashtable[index].level;
                        }                       
                        else{
                            cout<<";"<<index<<" "<<hash.Hashtable[index].identifier<<"//"<<hash.Hashtable[index].level;
                        }

                        index=hash.level_Hashlist.find_first_not_of('-',index+1);

                    }
                    cout<<endl; //xoa

                    
                }

            }else{ //lenh sai
                // khi lenh sai tien hanh dong file 
                    myFile.close();   
                // giai phong toàn bộ vùng nhớ
                cout<<" giai phong vung nho khi lenh sai ###@@@###: -- giai phong: "<<boolalpha<<hash.releaseMemory()<<endl;
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