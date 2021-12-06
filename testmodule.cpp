#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <typeinfo>


using namespace std;
typedef int SONGUYEN;
typedef long long int KEY_NUM;
typedef unsigned long long int U_KEY_NUM;
bool end_With_SpaceR(string &str){
    if(str.length()==0){
        return false;
    }
    int last_index=str.length()-1;
    return (str[last_index]==' ')? true:false;
}

bool start_With_Space(string str){
    if(str.length()==0){
        return false;
    }
    return (str[0]==' ')?true:false;
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
bool is_NumberR(string &str);

int convert_To_Num(string str){
    int result=0;
    int leng=str.size();
    for(int i =0;i<leng;i++){
        int temp=str[i]-48;
        result=result*10+temp;
    }
    return result;
}
int convert_To_NumR(string& str);
bool is_Number(string str);
int number_length(int);
U_KEY_NUM transfer_Name_to_num_Key(string name,int level=0);
int count_CharR(string& str,char c);

string transfer_Name_to_str_Key(string name,int level);
U_KEY_NUM transfer_strKey_to_numKey(string strKEY);
bool congfigcheck(string configcommand,int (&configarr)[4]){
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
bool command_Form_check(string command, string (&componet)[3],int& numOfComponent);
bool identifierrule(string & str);
string initial_signature(int para);
bool is_string(string str);
bool is_stringR(string &str);
bool is_form_function(string value);
int check_value(string value);

int main(){

    string a="'fsad _'";
     cout<<check_value(a)<<endl;
    

    return 0;
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
    }

    return 0;
    

}

bool is_form_function(string value){
    int leng=value.length();
    if(leng<3){
        return false;
    }
    if((value.find('(')==std::string::npos)||(value.find(')')==std::string::npos)||(value[leng-1]!=')')){
        return false;
    }
    int temp=value.find('(');
    string id(value,0,temp);
    return identifierrule(id);    
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

int count_CharR(string &str,char c){
    int times=0;
	for( unsigned int i =0;i<str.length();i++)
	{
		if(str[i]==c) times+=1;
	}
	return times;

}

bool is_NumberR(string &str){
    return str.find_first_not_of("0123456789")== string::npos;
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

bool is_Number(string str){
    return str.find_first_not_of("0123456789")== string::npos;
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

int convert_To_NumR(string& str){
    int result=0;
    int leng=str.size();
    for(int i =0;i<leng;i++){
        int temp=str[i]-48;
        result=result*10+temp;
    }
    return result;
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

string transfer_Name_to_str_Key(string name,int level){
    string key(to_string(level));
    int leng=name.length();
    for (int i = 0; i < leng; i++)
    {
        key.append(to_string((name[i]-48)));
    }
    return key;
    
}