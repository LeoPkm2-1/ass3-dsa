#include <iostream>
#include <string>
#include <fstream>
#include <regex>


using namespace std;

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

bool is_NumberR(string &str){ // check is number;
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

bool is_Number(string str);
int number_length(int);
int transfer_Name_to_Key(string name,int level=0);
int count_CharR(string& str,char c);
void congfigcheck(string configcommand){
   int strleng=configcommand.length();
   if(configcommand[0]==' '||configcommand[strleng-1]==' '){
       cout<<"config SAI-X";
       return;
   }
   int numOfspace=count_CharR(configcommand,' ');

   if(numOfspace!=2&&numOfspace!=3){
       cout<<"config SAI-X";
       return;
   }

    int temp1=configcommand.find_first_of(' ');
    int temp2=configcommand.find_first_of(' ', temp1+1);
    if((temp1+1)==temp2){
        cout<<"config SAI-X";
        return;
    }
    if(numOfspace==3){
        int temp3=configcommand.find_first_of(' ', temp2+1);
        if((temp2+1)==temp3){
            cout<<"config SAI-X";
            return;
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
                valid=is_Number(m)&&is_Number(c1)&&is_Number(c2)&&(m.length()<7)&&(c1.length()<7)&&(c2.length()<7);
                if(!valid){
                    cout<<"config SAI-X";
                    return;
                }

            }



        }
    }

    if (numOfspace==2){
        //string m=configcommand.substr()
        string cmd=configcommand.substr(0,temp1);
        bool valid=false;
        if(cmd.compare("LINEAR")==0||cmd.compare("DOUBLE")==0){
            //valid=true;
        }
        string m=configcommand.substr(temp1+1,temp2-temp1-1);
        string c=configcommand.substr(temp2+1);
        valid=is_Number(m)&&is_Number(c)&&(c.length()<7)&&(m.length()<7);
        if(!valid){
            cout<<"config SAI-X";
            return;
        }

    }

    cout<<"0k";

}

int count_CharR(string &str,char c){
    int times=0;
	for( unsigned int i =0;i<str.length();i++)
	{
		if(str[i]==c) times+=1;
	}
	return times;

}



int main(){

    congfigcheck("QUADRATIC 42 3");
    // string str="DOUBLE 53453 543 65";
    // int temp1=str.find_first_of(' ');
    // cout<<str.substr(0,temp1)<<"-";
    // int temp2=str.find_first_of(' ',temp1+1);
    // int temp3=str.find_last_of(' ');
    // cout<<str.substr(temp1+1,temp2-temp1-1)<<"-";
    // cout<<str.substr(temp2+1,temp3-temp2-1)<<"-";
    // cout<<str.substr(temp3+1)<<endl;

    //cout<<boolalpha<<is_Number("-54353");
    // string temp="12a34";
    // int t=stoi(temp);
    // cout<<t<<endl;
    // string a="aihihi xin chao";
    // int temp1=a.find_first_of(' ');
    // cout<<a.compare(0,temp1,"aihihi")<<endl;
    // string a="ahiihi";
    // int temp1=a.find_first_of('i');
    //cout<<temp1<<endl;
    //cout<<a.find_first_of('i',temp1+1)<<endl;
    // cout<<a.find_last_of('i')<<endl;
    // cout<<a.length()<<endl;
    //ongfigcheck("ahihi xin chao");
    // cout<<transfer_Name_to_Key("xB",1);
    //cout<<transfer_Name_to_Key("xb")<<endl;
    //cout <<transfer_Name_to_Key("AA",1);
    //cout<<endl<<to_string(123)+"3";
    //cout<<("ahihi"+'c')<<endl;
    // string a="ahihi";
    // a.push_back('x');
    // cout<<a<<endl;

    //cout<<count_cha
    // string s1="0.2121";
   // cout<<boolalpha<<start_With_Space(s1)<<" - "<<end_With_SpaceR(s1)<<endl;
//    string num="43242";
//     if(is_NumberR(num)){
//         int a=convert_To_Num(num);
//         if(a==4324.2)
//             cout<<a<<endl;
//         else
//             cout<<"wrong work";
//     }
//     else{
//         cout<<"it not number"<<endl;
//     }

    return 0;
}

bool is_Number(string str){
    return str.find_first_not_of("0123456789")== string::npos;
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