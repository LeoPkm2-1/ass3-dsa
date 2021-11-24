#include <iostream>
#include <string>


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
int main(){

    // string s1="0.2121";
   // cout<<boolalpha<<start_With_Space(s1)<<" - "<<end_With_SpaceR(s1)<<endl;
   string num="43242";
    if(is_NumberR(num)){
        int a=convert_To_Num(num);
        if(a==4324.2)
            cout<<a<<endl;
        else
            cout<<"wrong work";
    }
    else{
        cout<<"it not number"<<endl;
    }

    return 0;
}