#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

//===============================help function declare=====================
typedef long long int KEY_NUM;
typedef unsigned long long int U_KEY_NUM;
int count_CharR(string& str,char c=' ');
int count_Char(string str,char c=' ');
bool start_With_SpaceR(string& str);
bool start_With_Space(string str);
bool end_With_Space(string str);
bool end_With_SpaceR(string &str);
bool is_Number_tempR(string &str);
bool is_Number_temp(string str);
bool is_Number(string str);
int convert_To_NumR(string& str);
int convert_To_Num(string str);
U_KEY_NUM transfer_Name_to_num_Key(string name,int level=0);
bool congfigcheck(string &configcommand,int (&configarr)[4]);
bool is_NumberR(string &str);
bool command_Form_check(string command, string (&componet)[3],int& numOfComponent);
bool identifierrule(string & str);
string transfer_Name_to_str_Key(string name,int level);
U_KEY_NUM transfer_strKey_to_numKey(string strKEY);
//=========================================================================

class Symbol{
public:
    bool empty;
    string identifier;
    int level;
    char type;
    int paranum;
    string signature;
    Symbol(){
        empty=true;
        identifier.clear();
        level=0;
        type='#';   // # chưa có kiểu ,  N : number , S: string, F: hàm
        paranum=0;
        signature.clear();
    }

};

class SymbolHashing{
public:
    Symbol* Hashtable;
    char probing;   // phuong phap do L: linear, Q: quadratic, D: double
    int capacity;   // sức chứa
    int numofSymbol;    // số lượng node hiện tại
    int maxLoop;        // max loop
    string level_Hashlist;      //lưu trữ danh sách level trong bảng hash
    int c1;
    int c2;
    SymbolHashing(){ 
        Hashtable=NULL;
        probing='-';
        capacity=0;
        numofSymbol=0;
        maxLoop=0;
        level_Hashlist.clear();
        c1=0;
        c2=0;

    }
    SymbolHashing(char _probing,int _capacity,int _numofSymbol,int _c1=0,int _c2=0):probing(_probing)
    ,capacity(_capacity),numofSymbol(_numofSymbol),maxLoop(0)
    ,level_Hashlist(_numofSymbol,'-'),c1(_c1),c2(_c2){

    }
protected:
    int h1(U_KEY_NUM key=0){
        int h1_key=(int)(key % capacity);
        return h1_key;
    }

    int h2(U_KEY_NUM key=0){
        int h2_key=1 + (int)( key % (capacity-2) );
        return h2_key;
    }


public:

    int linear_Probing(U_KEY_NUM key){
        int h_k=h1(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h_k+c1*i)%capacity;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;        
    }

    int linear_Probing_i(U_KEY_NUM key,int &loop){
        int h_k=h1(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h_k+c1*i)%capacity;
            loop=i;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;        
    }

    int quadratic_Probing(U_KEY_NUM key){
        int h_k=h1(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h_k+c1*i+c2*i*i)%capacity;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;
        
    }

    int quadratic_Probing_i(U_KEY_NUM key,int &loop){
        int h_k=h1(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h_k+c1*i+c2*i*i)%capacity;
            loop=i;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;
        
    }

    int double_Probing(U_KEY_NUM key){
        int h1_k=h1(key);
        int h2_k=h2(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h1_k + c1*i*h2_k)%capacity;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;

    }

    int double_Probing_i(U_KEY_NUM key,int&loop){
        int h1_k=h1(key);
        int h2_k=h2(key);
        for (int i = 0; i < capacity; i++)
        {
            int h_p=(h1_k + c1*i*h2_k)%capacity;
            loop=i;
            if(Hashtable[h_p].empty){
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;

    }



};


class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};







//===============================help function define=====================
int count_CharR(string& str,char c){
    int times=0;
	for( unsigned int i =0;i<str.length();i++)
	{
		if(str[i]==c) times+=1;
	}
	return times;

}
int count_Char(string str,char c){
    int times=0;
	for( unsigned int i =0;i<str.length();i++)
	{
		if(str[i]==c) times+=1;
	}
	return times;

}
bool start_With_SpaceR(string& str){
    if(str.length()==0){
        return false;
    }
    return (str[0]==' ')?true:false;
}
bool start_With_Space(string str){
    if(str.length()==0){
        return false;
    }
    return (str[0]==' ')?true:false;
}
bool end_With_SpaceR(string &str){
    if(str.length()==0){
        return false;
    }
    int last_index=str.length()-1;
    return (str[last_index]==' ')? true:false;
}
bool end_With_Space(string str){
    if(str.length()==0){
        return false;
    }
    int last_index=str.length()-1;
    return (str[last_index]==' ')? true:false;
}
bool is_Number_tempR(string &str){ // check is number;
    int lengthofstring=str.size();
    for(int i =0;i<lengthofstring;i++){
        if(str[i]<48||str[i]>57){
            return false;
        }
    }
    return true;
}
bool is_Number_temp(string str){
    int lengthofstring=str.size();
    for(int i =0;i<lengthofstring;i++){
        if(str[i]<48||str[i]>57){
            return false;
        }
    }
    return true;
}
bool is_Number(string str){
    return str.find_first_not_of("0123456789")== string::npos;
}
bool is_NumberR(string &str){
    return str.find_first_not_of("0123456789")== string::npos;
}
int convert_To_Num(string str){
    int result=0;
    int leng=str.size();
    for(int i =0;i<leng;i++){
        int temp=str[i]-48;
        result=result*10+temp;
    }
    return result;
}
int convert_To_NumR(string& str){
    int result=0;
    int leng=str.size();
    for(int i =0;i<leng;i++){
        int temp=str[i]-48;
        result=result*10+temp;
    }
    return result;
}
U_KEY_NUM transfer_Name_to_num_Key(string name,int level){
    if(level>=0){
        U_KEY_NUM key=level;
        int leng=name.length();
        for (int i = 0; i < leng;i++)
        {
            int insert_value=((int)name[i]) -48;
          int temp=to_string(insert_value).length();
          for (int i = 1; i <= temp; i++)
          {
            key=key*10;
          }
          key=key+insert_value;      
    
        }
        return key;
    }else{
        return 0;
    }
}
string transfer_Name_to_str_Key(string name,int level){
    string key(to_string(level));
    int leng=name.length();
    for (int i = 0; i < leng; i++)
    {
        key.append(to_string((name[i]-48)));
    }
    return key;
    
}
U_KEY_NUM transfer_strKey_to_numKey(string strKEY){
    int leng=strKEY.length();
    U_KEY_NUM key=0;
    for (int i = 0; i < leng; i++)
    {
        key=key*10;
        key=key+(strKEY[i]-48);
    }
    return key;
    
}
bool congfigcheck(string &configcommand,int (&configarr)[4]){    //ham2 nay co nhiem vu kiem tra xem lenh cau hin bang hash co dung hay khong
   int strleng=configcommand.length();
   if(configcommand[0]==' '||configcommand[strleng-1]==' '){
       
       return false;
   }

   int numOfspace=count_CharR(configcommand,' ');

   if(numOfspace!=2&&numOfspace!=3){
       
       return false;
   }

    int temp1=configcommand.find_first_of(' ');
    int temp2=configcommand.find_first_of(' ', temp1+1);

    if((temp1+1)==temp2){
        
        return false;
    }

    if(numOfspace==3){
        int temp3=configcommand.find_first_of(' ', temp2+1);
        if((temp2+1)==temp3){
            
            return false;
        }else{  //dau cach chinh xac
            if(configcommand.compare(0,temp1,"QUADRATIC")==0){
                string cmd=configcommand.substr(0,temp1);
                string m=configcommand.substr(temp1+1,temp2-temp1-1);
                string c1=configcommand.substr(temp2+1,temp3-temp2-1);
                string c2=configcommand.substr(temp3+1);
                bool valid=false;
                if(cmd.compare("QUADRATIC")==0){
                    valid=true;
                }
                valid=valid&&is_Number(m)&&is_Number(c1)&&is_Number(c2)&&(m.length()<7)&&(c1.length()<7)&&(c2.length()<7);
                if(!valid){
                    
                    //cout<<"-"<<cmd<<"-"<<m<<"-"<<c1<<"-"<<c2<<"="<<endl;
                    return false;
                }
                char temp_c='Q';
                configarr[0]=(int)temp_c;
                configarr[1]=convert_To_NumR(m);
                configarr[2]=convert_To_NumR(c1);
                configarr[3]=convert_To_NumR(c2);

            }



        }
    }

    if (numOfspace==2){
        //string m=configcommand.substr()
        string cmd=configcommand.substr(0,temp1);
        bool valid=false;
        if(cmd.compare("LINEAR")==0||cmd.compare("DOUBLE")==0){

            valid=true;
        }
        string m=configcommand.substr(temp1+1,temp2-temp1-1);
        string c=configcommand.substr(temp2+1);
        valid=valid&&is_Number(m)&&is_Number(c)&&(c.length()<7)&&(m.length()<7);
        if(!valid){
            
            //cout<<"-"<<cmd<<"-"<<m<<"-"<<c<<"="<<endl;
            return false;
        }


        char temp_c=(cmd[0]=='L')?'L':'D';
        configarr[0]=(int)temp_c;
        configarr[1]=convert_To_NumR(m);
        configarr[2]=convert_To_NumR(c);
        //configarr[3]=convert_To_NumR(c2);

    }

    
    return true;

}
bool command_Form_check(string command, string (&componet)[3],int& numOfComponent){
    int numSpace=count_CharR(command,' ');
    if(numSpace>2){
        return false;
    }
    if(numSpace==0){
        if(command.compare("BEGIN")==0){
            componet[0]=command;
            numOfComponent=1;
            return true;
        }
        else if(command.compare("END")==0){
            componet[0]=command;
            numOfComponent=1;
            return true;
        }
        else if(command.compare("PRINT")==0){
            componet[0]=command;
            numOfComponent=1;
            return true;
        }
        else{
            return false;
        }
    }
    int cmdLength=command.length();
    if(command[0]==' '||command[cmdLength-1]==' '){
        return false;
    }

    if(numSpace==1){
        int temp1=command.find_first_of(' ');
        string cmd_temp=command.substr(0,temp1);
        if((cmd_temp.compare("INSERT")==0)||(cmd_temp.compare("LOOKUP")==0)){
            string iden_temp=command.substr(temp1+1);
            if(identifierrule(iden_temp)){
                componet[0]=cmd_temp;
                componet[1]=iden_temp;
                numOfComponent=2;
                return true;
            }

            return false;

        }
        else if(cmd_temp.compare("CALL")==0){
            componet[0]=cmd_temp;
            componet[1]=command.substr(temp1+1);
            numOfComponent=2;
            return true;

        }
        else{
            return false;
        }
    }
    else if(numSpace==2){
        int temp1=command.find_first_of(' ');
        string cmd_temp=command.substr(0,temp1);
        if(cmd_temp.compare("INSERT")==0){
            int temp2=command.find_last_of(' ');
            string iden_temp=command.substr(temp1+1,temp2-temp1-1);
            if(identifierrule(iden_temp)){               
               string value=command.substr(temp2+1);
               if(is_NumberR(value)){
                    componet[0]=cmd_temp;
                    componet[1]=iden_temp;
                    componet[2]=value;
                    numOfComponent=3;
                    return true;
               }
               return false;

            }
            return false;
        }
        else if(cmd_temp.compare("ASSIGN")==0){
            int temp2=command.find_last_of(' ');
            string iden_temp=command.substr(temp1+1,temp2-temp1-1);
            if(identifierrule(iden_temp)){               
                string value=command.substr(temp2+1);
                componet[0]=cmd_temp;
                componet[1]=iden_temp;
                componet[2]=value;
                numOfComponent=3;
                return true;

            }
            return false;
        }
        return false;
    }
    return false;

}
bool identifierrule(string & str){// check name is accept
    int lengthofstring = str.length();

    if(lengthofstring>0){
        if(str[0]<97|| str[0]>122){
            return false;
        }

        for(int i =1;i<lengthofstring;i++){
            if(str[i]=='_'){
                continue;
            }
            else if(str[i]>=97 && str[i] <=122){
                continue;
            }
            else if(str[i]>=65 && str[i]<=90){
                continue;
            }
            else if(str[i]>=48 && str[i]<=57){
                continue;
            }
            else{
                return false;
            }
        }

        return true;
    }

    return false;
}



//=========================================================================









#endif