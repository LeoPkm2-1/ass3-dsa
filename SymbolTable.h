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
string initial_signature(int para);
bool is_string(string str);
bool is_stringR(string &str);
bool is_form_function(string);
int check_value(string);
int num_of_arguments(string);


//=========================================================================

class Symbol{
public:
    bool empty; // indicate this slot is avaible to insert a new symbol to
    string identifier;  //name of varible which u would like to insert to the slot
    int level;          //level of of the variable
    char type;          // type of slot : # - not type, N - number, S -string, F - function
    int paranum;        // this field is meaningful when type is function and one show number of parameter of funtion
    string signature;   // this is describe function signature. for example : num(string,num,string): which meaning return type is num and para1: string, para2: num, para3: string
    Symbol(){
        empty=true;
        identifier.clear();
        level=0;
        type='#';   // # chưa có kiểu ,  N : number , S: string, F: hàm , 
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
    ,level_Hashlist(_numofSymbol,'-'),c1(_c1),c2(_c2){}

    bool releaseMemory(){
        if(Hashtable!=NULL){
            delete[] Hashtable;
            Hashtable=NULL;
            this->level_Hashlist.clear();
            //level_Hashlist.clear();

            return false;
        }
        return true;
        
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
            //else if(Hashtable[h_p])
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
                //Hashtable[h_p].empty=false;
                return h_p;
            }
            else{
                continue;
            }
        }
        return -1;

    }

    int insert_to_hash(U_KEY_NUM key,int &level,int &loop,string name=""){

        if(this->probing=='L'){ //linear
            int h_k=h1(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=(h_k+c1*i)%capacity;
                loop=i;
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            return -2;  //over follow           

        }
        else if(probing=='D'){  //double
            int h1_k=h1(key);
            int h2_k=h2(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=( h1_k +c1*i*h2_k )%capacity;
                //cout<<"ret--"<<h1_k<<"-"<<h2_k<<"-"<<i<<"-"<<c1<<"-"<<h_p<<endl;
                loop=i;
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            return -2;  //over follow;
            
        }
        else{   //quadratic

            int h_k=h1(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=(h_k+c1*i+c2*i*i)%capacity;
                loop=i;
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            
            return -2;  //over follow

        }
    }

    int insert_to_hash(U_KEY_NUM key,int &level,int &loop,int& at,string name=""){

        if(this->probing=='L'){ //linear
            int h_k=h1(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=(h_k+c1*i)%capacity;
                loop=i;
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    at =h_p;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    at =h_p;
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            return -2;  //over follow           

        }
        else if(probing=='D'){  //double
            int h1_k=h1(key);
            int h2_k=h2(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=( h1_k +c1*i*h2_k )%capacity;
                //cout<<"ret--"<<h1_k<<"-"<<h2_k<<"-"<<i<<"-"<<c1<<"-"<<h_p<<endl;
                loop=i;
                // cout<<endl<<"h1: "<<h1_k<<" - "<<"h2: "<<h2_k<<" - c: "<<c1<<" - hp: "<<h_p<<" - level: "<<level<<" - loop: "<<i<<" capacity: "<<capacity<<endl;
                
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    at =h_p;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    at =h_p;
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            return -2;  //over follow;
            
        }
        else{   //quadratic

            int h_k=h1(key);
            for (int i = 0; i < capacity; i++)
            {
                int h_p=(h_k+c1*i+c2*i*i)%capacity;
                loop=i;
                if(Hashtable[h_p].empty){
                    Hashtable[h_p].empty=false;
                    if(this->maxLoop<loop){
                        //Hashtable[h_p].empty=false;
                        maxLoop=loop;
                        //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    }
                    //cout<<"max loop:"<<maxLoop<<"loop: "<<loop<<endl;
                    at =h_p;
                    return h_p;
                }
                else if((name.compare(Hashtable[h_p].identifier)==0)&&(level==Hashtable[h_p].level)){
                    at =h_p;
                    return -1;  //da ton tai
                }
                else{
                    continue;
                }
            }
            
            return -2;  //over follow

        }
    }

    int delete_all_identifier_at_level(int &level){
        int number_deleted=0;
        char level_temp = level+48;
        //cout<<"de le te at: "<<level_temp<<endl;
        size_t position_found=this->level_Hashlist.find_first_of(level_temp,0);
        
        //cout<<"hihi---"<<position_found<<endl;
        while (position_found!=std::string::npos)
        {
            number_deleted+=1;
            Hashtable[position_found].empty=true;   //bat buoc
            Hashtable[position_found].identifier.clear();
            Hashtable[position_found].level=0;
            Hashtable[position_found].type='#';
            Hashtable[position_found].paranum=0;
            Hashtable[position_found].signature.clear();
            level_Hashlist[position_found]='-'; //bat buoc
            position_found=level_Hashlist.find_first_of(level_temp,position_found+1);
            numofSymbol=numofSymbol-1;

        }
        
        //cout<<level_Hashlist<<endl;
        return number_deleted;
    }

    int lookup_linear(string name,int level){
        int level_temp=level;
        int mxloop=this->maxLoop;
        
        for (int i = level; i >=0; i--)
        {
            U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
            int h_k=h1(key);
            for (int j = 0; j <= mxloop; j++)
            {
                int h_p=(h_k+c1*i)%capacity;
                if((Hashtable[h_p].empty==false)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
                else{
                    continue;
                }
            }
            

        }
        return -1;
        
    }

    // int lookup_linearR(string name,int& level){
    //     int level_temp=level;
    //     int mxloop=this->maxLoop;        
    //     for (int i = level_temp; i >=0; i--)
    //     {
    //         level=i;
    //         U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
    //         int h_k=h1(key);
    //         for (int j = 0 ; j <mxloop; j++)
    //         {
    //             int h_p=(h_k+c1*j)%capacity;
    //             if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
    //                 return h_p;
    //             }
    //             else{
    //                 continue;
    //             }
    //         }          
    //     }
    //     return -1;        
    // }

    int lookup_linearR(string name,int& level){
        int level_temp=level;
        int mxloop=this->maxLoop;        
        for (; level >=0; level--)
        {
            //level=level;
            U_KEY_NUM key=transfer_Name_to_num_Key(name,level);
            int h_k=h1(key);
            for (int j = 0 ; j <=mxloop; j++)
            {
                int h_p=(h_k+c1*j)%capacity;
                if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
                // cout<<"----###-----"<<j<<"-"<<level<<endl;
                
            }          
        }
        return -1;        
    }

    int lookup_double(string name,int level){
        int level_temp=level;
        int mxloop=this->maxLoop;
        for (int i = level_temp; i >=0; i--)
        {
            level=i;
            U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
            int h1_k=h1(key);
            int h2_k=h2(key);

            for (int j = mxloop; j >=0; j--)
            {
                int h_p=(h1_k+c1*j*h2_k)%capacity;
                if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
                else{
                    continue;
                }
            }        

        }
        return -1;         
    }
    int lookup_doubleR(string name,int& level){
        int level_temp=level;
        int mxloop=this->maxLoop;
        for (int i = level_temp; i >=0; i--)
        {
            level=i;
            U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
            int h1_k=h1(key);
            int h2_k=h2(key);

            for (int j = mxloop; j >=0; j--)
            {
                int h_p=(h1_k+c1*j*h2_k)%capacity;
                //cout<<i<<"-"<<j<<"-"<<c1<<"-"<<h1_k<<"-"<<h2_k<<endl;
                if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
                else{
                    continue;
                }
            }        

        }
        return -1;         

    }

    int lookup_quadratic(string name,int level){
        int level_temp=level;
        int mxloop=this->maxLoop;
        for (int i = level_temp; i >=0; i--)
        {
            level=i;
            U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
            int h_k=h1(key);
            for (int j = 0; j <= mxloop; j++)
            {
                int h_p=(h_k+c1*j+c2*j*j)%capacity;
                // cout<<level<<"-"<<h_k<<"-"<<h_p<<"-"<<j<<"-"<<c1<<"-"<<c2<<endl;
                if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
            }
            
        }
        return -1;
        
    }

    int lookup_quadraticR(string name,int &level){
        int level_temp=level;
        int mxloop=this->maxLoop;
        for (int i = level_temp; i >=0; i--)
        {
            level=i;
            U_KEY_NUM key=transfer_Name_to_num_Key(name,i);
            int h_k=h1(key);
            for (int j = 0; j <= mxloop; j++)
            {
                int h_p=(h_k+c1*j+c2*j*j)%capacity;
                // cout<<level<<"-"<<h_k<<"-"<<h_p<<"-"<<j<<"-"<<c1<<"-"<<c2<<endl;
                if((Hashtable[h_p].empty==false)&&(level==Hashtable[h_p].level)&&(name.compare(Hashtable[h_p].identifier)==0)){
                    return h_p;
                }
            }
            
        }
        return -1;
        
    }

    int lookupR(string name,int &level){
        if(this->probing=='Q'){
            return lookup_quadraticR(name,level);
        }
        else if(this->probing=='D'){
            return lookup_doubleR(name,level);
        }
        else{
            return lookup_linearR(name,level);
        }
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

bool is_form_function(string value){
    int leng=value.length();
    if(leng<3){
        return false;
    }
    if((value.find('(')==std::string::npos)||(value.find(')')==std::string::npos)||(value[leng-1]!=')')||(count_CharR(value,'(')!=1)||( count_CharR(value,')')!=1 )  ){
        return false;
    }
    int num_temp=count_CharR(value,',');
    int num1=value.find('(');
    int num2=value.find(')');
    if(num_temp!=0){
        //int num3=value.find(',');
        if(value[num1+1]==','||value[num2-1]==','){
            return false;
        }
        
        if(num_temp>1){
            for (int i = num1+1; i < num2; i++)
            {
                if(value[i]==','&&value[i+1]==',')
                {
                    return false;
                }
            }
            
        }


    }
   
   
    int temp=value.find('(');
    string id(value,0,temp);
    return identifierrule(id);    
}

int check_value(string value){
    // 0 wrong
    // 1 number
    // 2 string
    // 3 varible
    // 4 funtion
   
    if(is_Number(value)){
        return 1;
    }
    else if(is_stringR(value)){
        return 2;
    }
    else if(identifierrule(value)){
        return 3;
    }
    else if(is_form_function(value)){
        return 4;
    }else{
        return 0;

    }
    
   

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

    if(numSpace!=0){    // kiểm tra assign
        int pos1=command.find(' ');
        string cmd(command,0,pos1);
        if(cmd.compare("ASSIGN")==0){ // lenh assign
            int pos2=command.find(' ',pos1+1);
            string id(command,pos1+1,pos2-pos1-1);
            if(identifierrule(id)){
                string value(command,pos2+1);
                componet[0]=cmd;
                componet[1]=id;
                componet[2]=value;
                // cout<<"day la assign"<<endl;
                // cout<<cmd<<"==="<<id<<"==="<<value<<endl;
                numOfComponent=3;
                return true;


            }else{
                return false;
            }
        }
        else if(cmd.compare("CALL")==0){    //lenh call
            componet[0]=cmd;
            int temp=command.find_first_of('(');
            if(temp<=pos1+1){
                return false;
            }
            string id=command.substr(pos1+1,temp-pos1-1);
            if(identifierrule(id)){
                componet[1]=command.substr(pos1+1);
                numOfComponent=2;
                return true;
            }else{
                return false;
            }


        }
        
        
    }
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
        // else if(cmd_temp.compare("CALL")==0){
        //     componet[0]=cmd_temp;
        //     componet[1]=command.substr(temp1+1);
        //     numOfComponent=2;
        //     return true;

        // }
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
        // else if(cmd_temp.compare("ASSIGN")==0){
        //     int temp2=command.find_last_of(' ');
        //     string iden_temp=command.substr(temp1+1,temp2-temp1-1);
        //     if(identifierrule(iden_temp)){               
        //         string value=command.substr(temp2+1);
        //         componet[0]=cmd_temp;
        //         componet[1]=iden_temp;
        //         componet[2]=value;
        //         numOfComponent=3;
        //         return true;

        //     }
        //     return false;
        // }
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

string initial_signature(int para){
    if(para==0){
        return "#()";
    }
    else if(para==1){
        return "#(#)";
    }
    else if(para==2){
        return "#(#,#)";
    }
    else if(para>=3){
        string temp="#(#";
        for (int i = 1; i < para; i++)
        {
            temp.append(",#");
        }
        temp.push_back(')');
        return temp;
        
        // "#(#,#,#)"
    }
    return "";
}

bool is_string(string str){
    int leng=str.length();
    if(leng<=1) return false;
    else if(str[0]!='\'' ||str[leng-1]!=str[0]) return false;

    for (int i = 1; i < leng-1; i++)
    {
        if(str[i]==' '){
            continue;
        }
        else if(str[i]>=48&&str[i]<=57){
            continue;
        }
        else if(str[i]>=65&&str[i]<=90){
            continue;
        }
        else if(str[i]>=97&&str[i]<=122){
            continue;
        }
        else{
            return false;
        }

    }

    return true;
    
}

bool is_stringR(string &str){
    int leng=str.length();
    if(leng<=1) return false;
    else if(str[0]!='\'' ||str[leng-1]!=str[0]) return false;

    for (int i = 1; i < leng-1; i++)
    {
        if(str[i]==' '){
            continue;
        }
        else if(str[i]>=48&&str[i]<=57){
            continue;
        }
        else if(str[i]>=65&&str[i]<=90){
            continue;
        }
        else if(str[i]>=97&&str[i]<=122){
            continue;
        }
        else{
            return false;
        }

    }

    return true;
    
}


int num_of_arguments(string str){
    int pos1=str.find('(');
    int pos2=str.find_last_of(')');
    int result=0;
    int temp=count_CharR(str,',');

    if(pos1+1==pos2){
       // result 0;
    }
    else{
        result=temp+1;
    }
    return result;
    
}



//=========================================================================









#endif