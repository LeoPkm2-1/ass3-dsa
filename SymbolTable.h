#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

//===============================help function declare=====================
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
int transfer_Name_to_Key(string name,int level=0);


//=========================================================================


class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};

class sperate_command{
public:
    int numOfpart;
    bool valid;
    

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
int transfer_Name_to_Key(string name,int level){
    if(level>=0){
        int key=level;
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
        return -1;
    }
}
bool is_Number(string str){
    return str.find_first_not_of("0123456789")== string::npos;
}









//=========================================================================









#endif