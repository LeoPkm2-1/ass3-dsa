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
                    // kiem tra xem kieu chuyen vao ham la number hay string hay bien hay ham
                    // neu la 1 thi la num, 2 la string ,3 la bien, 4 la function
                    int assign_value_type=check_value(component[2]);
                    
            //assign type is number or string==================================================================================================== 
                    if(assign_value_type==1||assign_value_type==2){ 
                        //cout<<"------- assign is string or number : "<<component[2]<<endl;
                        int level_found=blockLevel; // level found identifier
                        int loop=0;
                        int slot_id_found=hash.lookupR(component[1],level_found,loop);   // where identifier in block
                        //cout<<" - loop: "<<loop;
                        if(slot_id_found==-1){ //not found identifier
                            myFile.close(); // dong file 
                            // giai phong bo nho
                            cout<<" //---- not found: "<< component[1]<<" -- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            //bao loi
                            Undeclared Undeclaredmessage(component[1]);
                            throw Undeclared(component[1]);
                        }
                        // found identifier
                        if(hash.Hashtable[slot_id_found].type=='#'){    // identifier don't have type 
                            hash.Hashtable[slot_id_found].type=(assign_value_type==1)?'N':'S';  // assign type 
                            cout<<" // ----- bien "<<hash.Hashtable[slot_id_found].identifier<<" - loop: "<<loop<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<" - da dc suy dien kieu la: "<<hash.Hashtable[slot_id_found].type<<endl;
                        }
                        else if(hash.Hashtable[slot_id_found].type=='N'&&assign_value_type==1){ //both is number => ok
                            cout<<" // ------ gan hop le bien: "<<hash.Hashtable[slot_id_found].identifier<<" - loop: "<<loop<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<endl;
                            cout<<" // ------"<<hash.Hashtable[slot_id_found].type<<" -vs- N"<<endl;
                        }
                        else if(hash.Hashtable[slot_id_found].type=='S'&&assign_value_type==2){ //both is string => ok
                            cout<<" // ------ gan hop le bien: "<<hash.Hashtable[slot_id_found].identifier<<" - loop: "<<loop<<" - level: "<<hash.Hashtable[slot_id_found].level<<" - at slot: "<<slot_id_found<<endl;
                            cout<<" // ------"<<hash.Hashtable[slot_id_found].type<<" -vs- S"<<endl;
                        }
                        else{   // khong hop kieu
                            // dong file 
                            myFile.close();
                            //giai phong vung nho
                            cout<<" ko hop kieu: "<<hash.Hashtable[slot_id_found].identifier<<" - level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<endl;
                            cout<<hash.Hashtable[slot_id_found].type<<" -vs- "<<((assign_value_type==1)?'N':'S')<<endl;
                            cout<<" release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }

                    }

            //assign type is variable============================================================================================================
                    else if(assign_value_type==3){  
                        // cout<<"------- assign is varible: "<<component[2]<<endl;                        
                        int level_val_find=blockLevel; // level found variable 
                        int loop_val=0;
                        int slot_val_find = hash.lookupR(component[2],level_val_find,loop_val);  // where varible is hash
                        // cout<<" - loop: "<<loop;


                        if(slot_val_find==-1){  // not found varible
                            // close file
                            myFile.close();
                            // release memory
                            cout<<" //---- not found: "<< component[2]<<" -- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // throw error
                            Undeclared Undeclaredmessage(component[2]);
                            throw Undeclared(component[2]);
                        }
                        // found varible => found identifier
                        if(hash.Hashtable[slot_val_find].type=='F'){
                            cout<<"// ------ bien la ham => sai: "<<component[2]<<endl;
                            //close file
                            myFile.close();
                            //release memory
                            cout<<"// ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            InvalidInstruction InvalidInstructionmessage(line);
                            throw InvalidInstruction(line);
                        }

                        
                        int level_id_find=blockLevel;
                        int loop_id=0;
                        int slot_id_find=hash.lookupR(component[1],level_id_find,loop_id);
                        if(slot_id_find==-1){  // not found identifier
                            // close file
                            myFile.close();
                            // release memory
                            cout<<" //---- not found: "<< component[1]<<" -- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // throw error
                            Undeclared Undeclaredmessage(component[1]);
                            throw Undeclared(component[1]);
                        }

                        if(hash.Hashtable[slot_id_find].type=='F'){
                            cout<<"// ------ bien la ham => sai luon: "<<component[2]<<endl;
                            //close file
                            myFile.close();
                            //release memory
                            cout<<"// ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // InvalidInstruction InvalidInstructionmessage(line); bỏ
                            // throw InvalidInstruction(line);  bỏ
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }
                        //cout<<" - loop: "<<loop;
                        // both identifier and varible is found => compare type
                        char val_type=hash.Hashtable[slot_val_find].type;
                        char id_type=hash.Hashtable[slot_id_find].type;
                        if(val_type=='#'&&val_type==id_type){ // the both haven't any type
                            // close file
                            myFile.close();
                            // release memory
                            cout<<"// ------ ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_find].identifier<<" -level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_val_find].identifier<<" -level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;
                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                            throw TypeCannotBeInferred(line);
                        }
                        else if(val_type==id_type&&id_type!='F'){   // same type => ok  note: cai nay co the bo cai id_type !='F' đi nha
                            cout<<" //------ gan kieu hop le: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_find].identifier<<" - loop: "<<loop_id<<" - level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_val_find].identifier<<" - loop: "<<loop_val<<" - level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;
                        }
                        else if(id_type=='#'&&val_type!='#'&&val_type!='F'){    // identifier  don't have type note: cai nay co the bo cai val_type!='F' đi nha
                            cout<<" // ------ before: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            hash.Hashtable[slot_id_find].type=hash.Hashtable[slot_val_find].type;
                            cout<<" // ------ after: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_find].identifier<<" - loop: "<<loop_id<<" -level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_val_find].identifier<<" - loop: "<<loop_val<<" -level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;

                        }
                        else if(val_type=='#'&&id_type!='#'&&id_type!='F'){ // varible  don't have type note: cai nay co the bo cai id_type !='F' đi nha
                            cout<<" // ------ before: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            hash.Hashtable[slot_val_find].type=hash.Hashtable[slot_id_find].type;
                            cout<<" // ------ after: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_find].identifier<<" - loop: "<<loop_id<<" -level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_val_find].identifier<<" - loop: "<<loop_val<<" -level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;
                        }
                        else{   // types are different
                            //close file
                            myFile.close();
                            // release memory
                            cout<<" // ----- khong cung kieu: "<<hash.Hashtable[slot_id_find].type<<" -vs- "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_find].identifier<<" -level: "<<hash.Hashtable[slot_id_find].level<<" -at slot: "<<slot_id_find<<" -type: "<<hash.Hashtable[slot_id_find].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_val_find].identifier<<" -level: "<<hash.Hashtable[slot_val_find].level<<" -at slot: "<<slot_val_find<<" -type: "<<hash.Hashtable[slot_val_find].type<<endl;
                            cout<<"// -- release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }
                    }


            // assign type is function call=======================================================================================================
                    else if(assign_value_type==4){  
                        cout<<"------- assign is function call: "<<component[2]<<endl;

                        // kiem tra ham ton tai
                        int name_lengh_temp=component[2].find('(');
                        string functionname(component[2],0,name_lengh_temp);
                        int level_function_found=blockLevel;
                        int loop_func=0;
                        int slot_function_found=hash.lookupR(functionname,level_function_found,loop_func);
                        if(slot_function_found==-1){    //ko tim thay ham
                            // close file
                            myFile.close();   
                            cout<<" // ------ function: "<<functionname <<" is not found."<<endl;
                            cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // show error
                            Undeclared Undeclaredmessage(functionname);
                            throw Undeclared(functionname);
                        }
            // nho kiem tra xem co phai la ham khong nha =============================================================================================   

                        if(hash.Hashtable[slot_function_found].type!='F'){  // neu mot bien khong phai dang ham la la loi goi ham thi bao loi
                            myFile.close();
                            cout<<" // ------ identifier: "<<hash.Hashtable[slot_function_found].identifier<<" is not a function type!"<<endl;
                            cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // show error
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }


                        
                        // tim thay ham
                        // chi thuc hien set so luong tham so truyen vao, tinh hop le cua cac tham so so voi doi so=> chua kiem tra kieu tra ve cua ham, voi lai chua tim identifier, va xet kieu tra ve cua no
                        // kiem tra tinh hop le cua tham so
                        int num_of_para=hash.Hashtable[slot_function_found].paranum;    // so luong tham so
                        int num_of_argu=num_of_arguments(component[2]); // so luong doi so truyen vao ham
                        if(num_of_argu!=num_of_para){   // so luong tham so va so luong doi so la khac nhau
                            myFile.close(); // close file when get error
                            cout<<"// ------ so luong doi so truyen vao khac voi so luong tham so: "<<num_of_argu<<" -> "<<hash.Hashtable[slot_function_found].paranum<<endl;
                            cout<<" //------- release memory: "<<boolalpha<<hash.releaseMemory();
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);

                        }

                            // so luong tham so va doi so bang nhau
                        if(num_of_para==0){}    // ham ko co tham so coi nhu la tham so hop le
                        else if(num_of_para==1){    // ham co 1 tham so
                            int start_argu=component[2].find('(');
                            int end_argu=component[2].find(')');
                            string argument(component[2],start_argu+1,end_argu-start_argu-1);
                            //cout<<"===="<<argument<<"===="<<endl;
                            int argu_type= check_value(argument);   // xet kieu cua doi so truyen vao

                            if(argu_type==1||argu_type==2){ // doi so duy nhat truyen vao ham la number or string
                                if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so chua co kieu
                                    cout<<" tham so duy nhat dc suy dien: "<<hash.Hashtable[slot_function_found].signature;
                                    hash.Hashtable[slot_function_found].signature[2]=(argu_type==1)?'N':'S';
                                    cout<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else if(hash.Hashtable[slot_function_found].signature[2]=='N'&&argu_type==1){   // tham so duy nhay co kieu num va doi so cung la num
                                    cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else if(hash.Hashtable[slot_function_found].signature[2]=='S'&&argu_type==2){   // tham so duy nhay co kieu string va doi so cung la string
                                    cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else{   // tham so duy nhat va doi so khong hop kieu
                                    // dong file
                                    myFile.close();
                                    //giai phong
                                    cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    TypeMismatch TypeMismatchmessage(line);
                                    throw TypeMismatch(line);
                                }
                            }

                            else if(argu_type==3){  // tham so duy nhat la bien
                                int level_id_found=blockLevel;
                                int loop_arg=0;
                                int slot_id_found=hash.lookupR(argument,level_id_found,loop_arg);
                                if(slot_id_found==-1){  // ko tim thay bien trong tham so duy nhat
                                    // close file
                                    myFile.close();   
                                    cout<<" // ------ argument: "<<argument <<" is not found."<<endl;
                                    cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    // show error
                                    Undeclared Undeclaredmessage(argument);
                                    throw Undeclared(argument);
                                }

                                // tim thay bien
                                // xem kieu co hop le ko:
                                if(hash.Hashtable[slot_id_found].type=='F'){    // kieu cua tham so la ham => InvalidInstruction
                                    // close file
                                    myFile.close();   
                                    // release memory
                                    cout<<"// ----- tham so duy nhat co kieu la ham: "<<hash.Hashtable[slot_id_found].type<<" --- "<<hash.Hashtable[slot_id_found].signature<<endl;
                                    cout<<"// ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    // InvalidInstruction InvalidInstructionmessage(line);  xoa
                                    // throw InvalidInstruction(line);  xoa 
                                    TypeMismatch TypeMismatchmessage(line);
                                    throw TypeMismatch(line);

                                }


                                

                                // bien truyen vao co kieu khac ham
                                char argu_type=hash.Hashtable[slot_id_found].type;
                                char para_type=hash.Hashtable[slot_function_found].signature[2];
                                 // doi so khong phai la ham thi chi co the la number hoac la string  hoac la chua co kieu
                                if(argu_type=='N'||argu_type=='S'){ // doi so la number hoac string
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so duy nhat chua co kieu
                                        //cout<<hash.Hashtable[slot_id_found].type<<endl;
                                        cout<<"--- before: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" // ---- tham so duy nhat chua co kieu nen se dc suy theo kieu cua doi so truyen vao:";
                                        hash.Hashtable[slot_function_found].signature[2]=(argu_type=='N')?'N':'S';
                                        cout<<" // ----- "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='N'&&argu_type==1){   // tham so duy nhay co kieu num va doi so cung la num
                                        cout<<" // ------ hop le: "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='S'&&argu_type==2){   // tham so duy nhay co kieu string va doi so cung la string
                                        cout<<" // ------ hop le: "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else{   // tham so duy nhat va doi so khong hop kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }
                                }
                                else if(argu_type=='#'){    // doi so vo kieu
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so cung vo kieu => bao doi ko the xet kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------ tham so va doi so deu ko co kieu: "<<argu_type<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" // ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                        throw TypeCannotBeInferred(line);
                                    
                                    }
                                    else{   // parameter have type => argument will be type of parameter
                                        cout<<" //------ before: "<<hash.Hashtable[slot_id_found].type<<" -> "<<hash.Hashtable[slot_function_found].signature[2];
                                        hash.Hashtable[slot_id_found].type=hash.Hashtable[slot_function_found].signature[2];
                                        cout<<" //------ after: "<<hash.Hashtable[slot_id_found].type<<" <- "<<hash.Hashtable[slot_function_found].signature[2]<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                }



                            }
                            
                            else if(argu_type==4){ // tham so duy nhat la loi goi ham => mistype
                                cout<<"// ------ tham so la loi goi ham => ko xet: "<<argument<<endl;
                                //close file
                                myFile.close();
                                //release memory
                                cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                InvalidInstruction InvalidInstructionmessage(line);
                                throw InvalidInstruction(line);
                            }
                            else {  // lenh sai
                                cout<<"// ------ tham so: "<<argument<<" khong hop le"<<endl;
                                //close file
                                myFile.close();
                                //release memory
                                cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                InvalidInstruction InvalidInstructionmessage(line);
                                throw InvalidInstruction(line);

                            }

                        }
                        
                        else if(num_of_para>=2){     // ham co nhieu tham so                                              
                            int start_argu=component[2].find('(');
                            int comma_1=component[2].find(',');
                            int comma_2=comma_1;
                            int end_argu=component[2].find(')');
                            string * argument_arr=new string[num_of_argu];  // mang chua doi so
                            for (int i = 0; i < num_of_argu; i++)   // lay doi so bo vao mang
                            {
                                if(i==0){
                                    argument_arr[i]=component[2].substr(start_argu+1,comma_2-start_argu-1);
                                    continue;
                                }
                                else if(i==num_of_argu-1){
                                    argument_arr[i]=component[2].substr(comma_2+1,end_argu-comma_2-1);
                                    continue;
                                }
                                comma_1=comma_2;
                                comma_2=component[2].find(',',comma_2+1);
                                argument_arr[i]=component[2].substr(comma_1+1,comma_2-comma_1-1);
                            }


                        
                            for (int i = 0; i < num_of_argu; i++){  // xu ly
                                // kiem tra kiem cua ham so
                                int argu_type= check_value(argument_arr[i]);

                                if(argu_type==1||argu_type==2){         // tham so thu i la string or number
                                    if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){  // tham so chua co kieu
                                        cout<<" tham so thu "<<i<<" dc suy dien: "<<hash.Hashtable[slot_function_found].signature[2*i+2];
                                        hash.Hashtable[slot_function_found].signature[2*i+2]=(argu_type==1)?'N':'S';
                                        cout<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='N'&&argu_type==1){   // tham so thu i co kieu num va doi so cung la num
                                        cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='S'&&argu_type==2){   // tham so thu i co kieu string va doi so cung la string
                                        cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;

                                    }
                                    else{   // tham so thu i va doi so khong hop kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------- tham so thu i va doi so khong hop kieu: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        delete[] argument_arr;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }

                                }
                                
                                else if(argu_type==3){  // tham so thu i la bien
                                    int level_argu_found=blockLevel;
                                    int loop_arg_i=0;
                                    int slot_argu_found=hash.lookupR(argument_arr[i],level_argu_found,loop_arg_i);
                                    if(slot_argu_found==-1){  // ko tim thay bien trong tham so thu i
                                        // close file
                                        myFile.close();   
                                        cout<<" // ------ argument: "<<argument_arr[i] <<" is not found."<<endl;
                                        cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        // show error
                                        string arr_temp=argument_arr[i];
                                        delete[] argument_arr;
                                        Undeclared Undeclaredmessage(arr_temp);
                                        throw Undeclared(arr_temp);
                                    }
                                    // tim thay bien
                                    // xem kieu co hop le ko:
                                    if(hash.Hashtable[slot_argu_found].type=='F'){    // kieu cua tham so la ham => mistype
                                        // close file
                                        myFile.close();   
                                        // release memory
                                        cout<<"// ----- tham so thu "<<i<<" co kieu la ham: "<<hash.Hashtable[slot_argu_found].type<<" --- "<<hash.Hashtable[slot_argu_found].signature<<endl;
                                        delete[] argument_arr;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);

                                    }

                                    //cout<<" - loop: "<<loop;

                                    // bien truyen vao co kieu khac ham
                                    char argu_type_=hash.Hashtable[slot_argu_found].type;
                                    char para_type_=hash.Hashtable[slot_function_found].signature[2*i+2];
                                    // doi so khong phai la ham thi chi co the la number hoac la string  hoac la chua co kieu
                                    if(argu_type_=='N'||argu_type_=='S'){   // doi so la number hoac string
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){
                                            cout<<"--- before: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" // ---- tham so thu "<<i<<" chua co kieu nen se dc suy theo kieu cua doi so truyen vao:";
                                            cout<<" // ----- "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            hash.Hashtable[slot_function_found].signature[2*i+2]=(argu_type_=='N')?'N':'S';
                                            cout<<"--- after: "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='N'&&argu_type_=='N'){ // tham so thu i co kieu num va doi so cung la num
                                            cout<<" // ------ hop le: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // ------ "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='S'&&argu_type_=='S'){ // tham so thu i co kieu string va doi so cung la string
                                            cout<<" // ------ hop le: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // ------ "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else{   // tham so duy nhat va doi so khong hop kieu
                                            // dong file
                                            myFile.close();
                                            // giai phong
                                            cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // -------- signature: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] argument_arr;
                                            TypeMismatch TypeMismatchmessage(line);
                                            throw TypeMismatch(line);
                                        }
                                    }

                                    else if(argu_type_=='#'){   // doi so vo kieu
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){  // tham so cung vo kieu => bao doi ko the xet kieu
                                            // dong file
                                            myFile.close();
                                            // giai phong
                                            cout<<" // ------ tham so va doi so deu ko co kieu nha ahihi: "<<argu_type_<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // -------- signature: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] argument_arr;
                                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                            throw TypeCannotBeInferred(line);
                                        }
                                        else{   // parameter have type => argument will be type of parameter
                                            cout<<" //------ before: "<<hash.Hashtable[slot_argu_found].type<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2];
                                            hash.Hashtable[slot_argu_found].type=hash.Hashtable[slot_function_found].signature[2*i+2];
                                            cout<<" //------ after: "<<hash.Hashtable[slot_argu_found].type<<" <- "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<" - loop_arg_i: "<<loop_arg_i;
                                        }

                                    }



                                }
                                else if(argu_type==4){  // tham so thu i la ham => mistype
                                    cout<<"// ------ tham so la loi goi ham ahihi => ko xet: "<<argument_arr[i]<<endl;
                                    //close file
                                    myFile.close();
                                    //release memory
                                    cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                    delete[] argument_arr;
                                    InvalidInstruction InvalidInstructionmessage(line);
                                    throw InvalidInstruction(line);

                                }
                                else {  // lenh sai
                                    cout<<"// ------ tham so thu "<<i<<" : "<<argument_arr[i]<<" khong hop le"<<endl;
                                    //close file
                                    myFile.close();
                                    //release memory
                                    cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                    delete[] argument_arr;
                                    InvalidInstruction InvalidInstructionmessage(line);
                                    throw InvalidInstruction(line);

                                }

                            }
                            
                        }   
                        
    //=================================================================================================moi them     ===================================================================               

                        // so sanh kieu cua ten6 ham voi id
                        int level_id_found=blockLevel;
                        int loop_id=0;
                        int slot_id_found=hash.lookupR(component[1],level_id_found,loop_id);        // tim kiem bien id trogn lenh assign
                        if(slot_id_found==-1){  // not found identifier
                            // close file
                            myFile.close();
                            // release memory
                            cout<<" //---- not found: "<< component[1]<<" -- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // throw error
                            Undeclared Undeclaredmessage(component[1]);
                            throw Undeclared(component[1]);
                        }

                        if(hash.Hashtable[slot_id_found].type=='F'){    // check identifier is not function
                            cout<<"// ------ bien la ham => sai luon chu sao: "<<component[1]<<endl;
                            //close file
                            myFile.close();
                            //release memory
                            cout<<"// ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }

                        //cout<<" - loop: "<<loop_id;
                        
                        char func_type_assign=hash.Hashtable[slot_function_found].signature[0];  // luu kieu tra ve cua ham
                        char id_type_assign=hash.Hashtable[slot_id_found].type;
                        // cout<<" kieu tra ve: "<<hash.Hashtable[slot_id_found].identifier<<" --vs-- "<<hash.Hashtable[slot_function_found].identifier<<endl;
                        // cout<<" kieu tra ve: "<<id_type_assign<<" --vs-- "<<func_type_assign<<endl;
                            // cout<<" ok 1 tham so cung ok "<<endl;
                        if(func_type_assign==id_type_assign&&id_type_assign=='#'){  // ca 2 deu chua co kieu
                            // close file
                            myFile.close();
                            // release memory
                            cout<<"// ------ ca 2 chua duoc suy dien kieu: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_found].identifier<<" -level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_function_found].identifier<<" -level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature<<endl;
                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                            throw TypeCannotBeInferred(line);

                        }
                        else if(func_type_assign==id_type_assign&&id_type_assign!='F'){   // same type => ok
                            cout<<" //------ gan kieu hop le: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_found].identifier<<" - loop_id: "<<loop_id<<" - level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_function_found].identifier<<" - loop_func: "<<loop_func<<" - level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature<<endl;
                        }
                        else if(id_type_assign=='#'&&func_type_assign!='#'&&func_type_assign!='V'){
                            cout<<" // ------ before: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            hash.Hashtable[slot_id_found].type=hash.Hashtable[slot_function_found].signature[0];
                            cout<<" // ------ after: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_found].identifier<<" - loop_id: "<<loop_id<<" -level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_function_found].identifier<<" - loop_func: "<<loop_func<<" -level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature<<endl;
                        }
                        else if(func_type_assign=='#'&&id_type_assign!='#'&&id_type_assign!='F'){ // varible  don't have type
                            cout<<" // ------ before: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            hash.Hashtable[slot_function_found].signature[0]=hash.Hashtable[slot_id_found].type;
                            cout<<" // ------ after: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_found].identifier<<" - loop_id: "<<loop_id<<" -level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_function_found].identifier<<" - loop_func: "<<loop_func<<" -level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature<<endl;
                        }
                        else{   // types are different
                            //close file
                            myFile.close();
                            // release memory
                            cout<<" // ----- khong cung kieu: "<<hash.Hashtable[slot_id_found].type<<" -vs- "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_id_found].identifier<<" -level: "<<hash.Hashtable[slot_id_found].level<<" -at slot: "<<slot_id_found<<" -type: "<<hash.Hashtable[slot_id_found].type<<endl;
                            cout<<" // ---- "<<hash.Hashtable[slot_function_found].identifier<<" -level: "<<hash.Hashtable[slot_function_found].level<<" -at slot: "<<slot_function_found<<" -type: "<<hash.Hashtable[slot_function_found].signature<<endl;
                            cout<<"// -- release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }


    //=================================================================================================moi them     ===================================================================               


                    }

                    // assign wrong
                    else {  
                        cout<<" ------ cau lenh sai cmnr"<<endl;
                        myFile.close();
                        //release memory
                        cout<<"// ------release "<<boolalpha<<hash.releaseMemory()<<endl;
                        
                        InvalidInstruction InvalidInstructionmessage(line);
                        throw InvalidInstruction(line);
                    }


                }


  /*              else if(component[0].compare("ASSIGN")==0){

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
                */
                
                
                else if(component[0].compare("CALL")==0){
                    cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1]<<endl;
                        
                    int call_exp_type=check_value(component[1]);
                    
                    if(call_exp_type==4){   // type is function call => ok
                        int name_lengh_temp=component[1].find('(');
                        string functionname(component[1],0,name_lengh_temp);
                        int level_function_found=blockLevel;
                        int loop_func=0;
                        int slot_function_found=hash.lookupR(functionname,level_function_found,loop_func);
                        if(slot_function_found==-1){    //ko tim thay ham
                            // close file
                            myFile.close();   
                            cout<<" // ------ function: "<<functionname <<" is not found."<<endl;
                            cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // show error
                            Undeclared Undeclaredmessage(functionname);
                            throw Undeclared(functionname);
                        }

                        if(hash.Hashtable[slot_function_found].type!='F'){
                            myFile.close();
                            cout<<" // ------ identifier: "<<hash.Hashtable[slot_function_found].identifier<<" is not a function type => CALL command is false !"<<endl;
                            cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // show error
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }

                        //cout<<" - loop: "<<loop;

                        int num_of_para=hash.Hashtable[slot_function_found].paranum; // so luong tham so
                        int num_of_argu=num_of_arguments(component[1]); // so luong doi so truyen vao ham

                        if(num_of_argu!=num_of_para){   // so luong tham so va so luong doi so la khac nhau
                            myFile.close(); // close file when get error
                            cout<<"// ------ so luong doi so truyen vao khac voi so luong tham so: "<<num_of_argu<<" -> "<<hash.Hashtable[slot_function_found].paranum<<endl;
                            cout<<" //------- release memory: "<<boolalpha<<hash.releaseMemory();
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }

                        // so luong tham so va doi so bang nhau
                        if(num_of_para==0){}    // ham ko co tham so coi nhu la tham so hop le
                        else if(num_of_para==1){    // ham co 1 tham so
                            int start_argu=component[1].find('(');
                            int end_argu=component[1].find(')');
                            string argument(component[1],start_argu+1,end_argu-start_argu-1);
                            int argu_type= check_value(argument);   // xet kieu cua doi so truyen vao

                            if(argu_type==1||argu_type==2){  // doi so duy nhat truyen vao ham la number or string
                                if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so chua co kieu
                                    cout<<" tham so duy nhat dc suy dien: "<<hash.Hashtable[slot_function_found].signature;
                                    hash.Hashtable[slot_function_found].signature[2]=(argu_type==1)?'N':'S';
                                    cout<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else if(hash.Hashtable[slot_function_found].signature[2]=='N'&&argu_type==1){   // tham so duy nhay co kieu num va doi so cung la num
                                    cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else if(hash.Hashtable[slot_function_found].signature[2]=='S'&&argu_type==2){   // tham so duy nhay co kieu string va doi so cung la string
                                    cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                }
                                else{   // tham so duy nhat va doi so khong hop kieu
                                    // dong file
                                    myFile.close();
                                    //giai phong
                                    cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    TypeMismatch TypeMismatchmessage(line);
                                    throw TypeMismatch(line);
                                }

                            }

                            else if(argu_type==3){  // tham so duy nhat la bien
                                int level_id_found=blockLevel;
                                int loop_arg=0;
                                int slot_id_found=hash.lookupR(argument,level_id_found,loop_arg);
                                if(slot_id_found==-1){  // ko tim thay bien trong tham so duy nhat
                                    // close file
                                    myFile.close();   
                                    cout<<" // ------ argument: "<<argument <<" is not found."<<endl;
                                    cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    // show error
                                    Undeclared Undeclaredmessage(argument);
                                    throw Undeclared(argument);
                                }

                                // tim thay bien
                                // xem kieu co hop le ko:
                                if(hash.Hashtable[slot_id_found].type=='F'){    // kieu cua tham so la ham => TypeMismatch
                                    // close file
                                    myFile.close();   
                                    // release memory
                                    cout<<"// ----- tham so duy nhat co kieu la ham: "<<hash.Hashtable[slot_id_found].type<<" --- "<<hash.Hashtable[slot_id_found].signature<<endl;
                                    cout<<"// ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                    // InvalidInstruction InvalidInstructionmessage(line);  xoa
                                    // throw InvalidInstruction(line);  xoa 
                                    TypeMismatch TypeMismatchmessage(line);
                                    throw TypeMismatch(line);

                                }


                                // cout<<" - loop: "<<loop;

                                // bien truyen vao co kieu khac ham
                                char argu_type=hash.Hashtable[slot_id_found].type;
                                char para_type=hash.Hashtable[slot_function_found].signature[2];
                                 // doi so khong phai la ham thi chi co the la number hoac la string  hoac la chua co kieu
                                if(argu_type=='N'||argu_type=='S'){ // doi so la number hoac string
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so duy nhat chua co kieu
                                        //cout<<hash.Hashtable[slot_id_found].type<<endl;
                                        cout<<"--- before: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" // ---- tham so duy nhat chua co kieu nen se dc suy theo kieu cua doi so truyen vao:";
                                        hash.Hashtable[slot_function_found].signature[2]=(argu_type=='N')?'N':'S';
                                        cout<<" // ----- "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='N'&&argu_type==1){   // tham so duy nhay co kieu num va doi so cung la num
                                        cout<<" // ------ "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2]=='S'&&argu_type==2){   // tham so duy nhay co kieu string va doi so cung la string
                                        cout<<" // ------ "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg: "<<loop_arg<<endl;
                                    }
                                    else{   // tham so duy nhat va doi so khong hop kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }
                                }
                                else if(argu_type=='#'){    // doi so vo kieu
                                    if(hash.Hashtable[slot_function_found].signature[2]=='#'){  // tham so cung vo kieu => bao doi ko the xet kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------ tham so va doi so deu ko co kieu: "<<argu_type<<" -> "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" // ------ release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                        throw TypeCannotBeInferred(line);
                                    
                                    }
                                    else{   // parameter have type => argument will be type of parameter
                                        cout<<" //------ before: "<<hash.Hashtable[slot_id_found].type<<" -> "<<hash.Hashtable[slot_function_found].signature[2];
                                        hash.Hashtable[slot_id_found].type=hash.Hashtable[slot_function_found].signature[2];
                                        cout<<" //------ after: "<<hash.Hashtable[slot_id_found].type<<" <- "<<hash.Hashtable[slot_function_found].signature[2]<<" - loop_arg: "<<loop_arg;
                                    }
                                }



                            }
                            
                            else if(argu_type==4){ // tham so duy nhat la loi goi ham => mistype
                                cout<<"// ------ tham so la loi goi ham => ko xet: "<<argument<<endl;
                                //close file
                                myFile.close();
                                //release memory
                                cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                InvalidInstruction InvalidInstructionmessage(line);
                                throw InvalidInstruction(line);
                            }
                            else {  // lenh sai
                                cout<<"// ------ tham so: "<<argument<<" khong hop le"<<endl;
                                //close file
                                myFile.close();
                                //release memory
                                cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                InvalidInstruction InvalidInstructionmessage(line);
                                throw InvalidInstruction(line);

                            }



                        }

                        else if(num_of_para>=2){     // ham co nhieu tham so                                              
                            int start_argu=component[1].find('(');
                            int comma_1=component[1].find(',');
                            int comma_2=comma_1;
                            int end_argu=component[1].find(')');
                            string * argument_arr=new string[num_of_argu];  // mang chua doi so
                            for (int i = 0; i < num_of_argu; i++)   // lay doi so bo vao mang
                            {
                                if(i==0){
                                    argument_arr[i]=component[1].substr(start_argu+1,comma_2-start_argu-1);
                                    continue;
                                }
                                else if(i==num_of_argu-1){
                                    argument_arr[i]=component[1].substr(comma_2+1,end_argu-comma_2-1);
                                    continue;
                                }
                                comma_1=comma_2;
                                comma_2=component[1].find(',',comma_2+1);
                                argument_arr[i]=component[1].substr(comma_1+1,comma_2-comma_1-1);
                            }


                        
                            for (int i = 0; i < num_of_argu; i++){  // xu ly
                                // kiem tra kiem cua ham so
                                int argu_type= check_value(argument_arr[i]);

                                if(argu_type==1||argu_type==2){         // tham so thu i la string or number
                                    if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){  // tham so chua co kieu
                                        cout<<" tham so thu "<<i<<" dc suy dien: "<<hash.Hashtable[slot_function_found].signature[2*i+2];
                                        hash.Hashtable[slot_function_found].signature[2*i+2]=(argu_type==1)?'N':'S';
                                        cout<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='N'&&argu_type==1){   // tham so thu i co kieu num va doi so cung la num
                                        cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                    }
                                    else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='S'&&argu_type==2){   // tham so thu i co kieu string va doi so cung la string
                                        cout<<" // ------ hop le: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;

                                    }
                                    else{   // tham so thu i va doi so khong hop kieu
                                        // dong file
                                        myFile.close();
                                        //giai phong
                                        cout<<" // ------- tham so thu "<<i<<" va doi so khong hop kieu: "<<((argu_type==1)?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                        cout<<" \t// ========= signature now: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                        cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        delete[] argument_arr;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);
                                    }

                                }
                                
                                else if(argu_type==3){  // tham so thu i la bien
                                    int level_argu_found=blockLevel;
                                    int loop_arg_i=0;
                                    int slot_argu_found=hash.lookupR(argument_arr[i],level_argu_found,loop_arg_i);
                                    if(slot_argu_found==-1){  // ko tim thay bien trong tham so thu i
                                        // close file
                                        myFile.close();   
                                        cout<<" // ------ argument: "<<argument_arr[i] <<" is not found."<<endl;
                                        cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                                        // show error
                                        string arr_temp=argument_arr[i];
                                        delete[] argument_arr;
                                        Undeclared Undeclaredmessage(arr_temp);
                                        throw Undeclared(arr_temp);
                                    }
                                    // tim thay bien
                                    // xem kieu co hop le ko:
                                    if(hash.Hashtable[slot_argu_found].type=='F'){    // kieu cua tham so la ham => mistype
                                        // close file
                                        myFile.close();   
                                        // release memory
                                        cout<<"// ----- tham so thu "<<i<<" co kieu la ham: "<<hash.Hashtable[slot_argu_found].type<<" --- "<<hash.Hashtable[slot_argu_found].signature<<endl;
                                        delete[] argument_arr;
                                        TypeMismatch TypeMismatchmessage(line);
                                        throw TypeMismatch(line);

                                    }

                                    //cout<<" - loop_arg_i: "<<loop_arg_i;
                                    
                                    // bien truyen vao co kieu khac ham
                                    char argu_type_=hash.Hashtable[slot_argu_found].type;
                                    char para_type_=hash.Hashtable[slot_function_found].signature[2*i+2];
                                    // doi so khong phai la ham thi chi co the la number hoac la string  hoac la chua co kieu
                                    if(argu_type_=='N'||argu_type_=='S'){   // doi so la number hoac string
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){
                                            cout<<"--- before: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" // ---- tham so thu "<<i<<" chua co kieu nen se dc suy theo kieu cua doi so truyen vao:";
                                            cout<<" // ----- "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            hash.Hashtable[slot_function_found].signature[2*i+2]=(argu_type_=='N')?'N':'S';
                                            cout<<"--- after: "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='N'&&argu_type_=='N'){ // tham so thu i co kieu num va doi so cung la num
                                            cout<<" // ------ hop le: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // ------ "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else if(hash.Hashtable[slot_function_found].signature[2*i+2]=='S'&&argu_type_=='S'){ // tham so thu i co kieu string va doi so cung la string
                                            cout<<" // ------ hop le: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // ------ "<<hash.Hashtable[slot_function_found].signature<<" - loop_arg_i: "<<loop_arg_i<<endl;
                                        }
                                        else{   // tham so duy nhat va doi so khong hop kieu
                                            // dong file
                                            myFile.close();
                                            // giai phong
                                            cout<<" // ------- tham so duy nhat va doi so khong hop kieu: "<<((argu_type_=='N')?'N':'S')<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // -------- signature: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] argument_arr;
                                            TypeMismatch TypeMismatchmessage(line);
                                            throw TypeMismatch(line);
                                        }
                                    }

                                    else if(argu_type_=='#'){   // doi so vo kieu
                                        if(hash.Hashtable[slot_function_found].signature[2*i+2]=='#'){  // tham so cung vo kieu => bao doi ko the xet kieu
                                            // dong file
                                            myFile.close();
                                            // giai phong
                                            cout<<" // ------ tham so va doi so deu ko co kieu: "<<argu_type_<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<endl;
                                            cout<<" // -------- signature: "<<hash.Hashtable[slot_function_found].signature<<endl;
                                            cout<<" //------- release: "<<boolalpha<<hash.releaseMemory()<<endl;
                                            delete[] argument_arr;
                                            TypeCannotBeInferred TypeCannotBeInferredmessage(line);
                                            throw TypeCannotBeInferred(line);
                                        }
                                        else{   // parameter have type => argument will be type of parameter
                                            cout<<" //------ before: "<<hash.Hashtable[slot_argu_found].type<<" -> "<<hash.Hashtable[slot_function_found].signature[2*i+2];
                                            hash.Hashtable[slot_argu_found].type=hash.Hashtable[slot_function_found].signature[2*i+2];
                                            cout<<" //------ after: "<<hash.Hashtable[slot_argu_found].type<<" <- "<<hash.Hashtable[slot_function_found].signature[2*i+2]<<" - loop_arg_i: "<<loop_arg_i;
                                        }

                                    }



                                }
                                else if(argu_type==4){  // tham so thu i la ham => mistype
                                    cout<<"// ------ tham so la loi goi ham ahihi => ko xet: "<<argument_arr[i]<<endl;
                                    //close file
                                    myFile.close();
                                    //release memory
                                    cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                    delete[] argument_arr;
                                    InvalidInstruction InvalidInstructionmessage(line);
                                    throw InvalidInstruction(line);

                                }
                                else {  // lenh sai
                                    cout<<"// ------ tham so thu "<<i<<" : "<<argument_arr[i]<<" khong hop le"<<endl;
                                    //close file
                                    myFile.close();
                                    //release memory
                                    cout<<"// ------ "<<boolalpha<<hash.releaseMemory()<<endl;
                                    delete[] argument_arr;
                                    InvalidInstruction InvalidInstructionmessage(line);
                                    throw InvalidInstruction(line);

                                }

                            }
                            
                        }  

        //  ========================================== xử lý call o dây==============================


                        if(hash.Hashtable[slot_function_found].signature[0]=='#'){
                            cout<<"/====== this fucntion don't have type => type of fucntion will be: ";
                            hash.Hashtable[slot_function_found].signature[0]='V';
                            cout<<hash.Hashtable[slot_function_found].signature<<" - loop_func: "<<loop_func<<endl;
                        }
                        else if(hash.Hashtable[slot_function_found].signature[0]=='V'){
                            cout<<"this fucntion have type Void => call ok"<<" - loop_func: "<<loop_func<<endl;
                        }
                        else{
                            myFile.close();
                            cout<<" // ------ type is not void: "<<hash.Hashtable[slot_function_found].signature<<" can't to call  !"<<endl;
                            cout<<" // ------ release memory: "<<boolalpha<<hash.releaseMemory()<<endl;
                            // show error
                            TypeMismatch TypeMismatchmessage(line);
                            throw TypeMismatch(line);
                        }








        //  ========================================== xử lý call o dây==============================


                    }
                    else{   // type is not function call => wrong
                        cout<<" ------ cau lenh call sai cmnr"<<endl;
                        myFile.close();
                        //release memory
                        cout<<"// ------release "<<boolalpha<<hash.releaseMemory()<<endl;
                        
                        InvalidInstruction InvalidInstructionmessage(line);
                        throw InvalidInstruction(line);
                    }

                        







                }
                else if(component[0].compare("BEGIN")==0){      // begin command
                    cout<<(++the_number)<<"---"<<component[0];//<<"-"<<component[1]<<endl;
                    cout<<" // ------ level truoc khi beign: "<<blockLevel<<" --- level sau do: ";
                    blockLevel+=1;
                    cout<<blockLevel<<endl;
                }
                else if(component[0].compare("END")==0){         // end command
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
                else if(component[0].compare("LOOKUP")==0){     // lookup
                    cout<<(++the_number)<<"---"<<component[0]<<"-"<<component[1];
                    int level_found=blockLevel;
                    //int level_found=3;
                    int loop=0;
                    int slot_find=hash.lookupR(component[1],level_found,loop);
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
                        //cout<<" - loop: "<<loop;

                        // cout<<component[1]<<" in slot "<<slot_find<<" at level : "<<level_found<<endl;
                        cout<<" // ------ tim thay: "<<component[1]<<" --- tai: "<<slot_find<<" --- level: "<<level_found<<" - loop: "<<loop<<endl;

                    }
                    // cout<<component[1]<<" in slot "<<slot_find<<" at level : "<<level_found<<endl;

                }
                else{ //PRINT command
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