#include <iostream>
#include<stdio.h>
#include <math.h>  
#include <stack>
#include <vector>

using namespace std; 

int check(char x);

struct Calculator{
    
    enum operators { add='+', subtract='-', divide='/', multiple='*', exp='^'};

    double sum; //store the sum

    Calculator(){ //initalize the sum to 0 when struct created
        sum = 0;
    }

    double calculate(double value1, double value2, char c){
        printf("%.2f %c %.2f\n",value1,c,value2);

        switch (c)
        {
            case add:
                sum = value1 + value2;
                break;

            case subtract:
                sum = value1 - value2;
                break;

            case divide:
                sum = value1 / value2;
                break;

            case multiple:
                sum = value1 * value2;
                break;

            case exp:
                sum = pow(value1 , value2*1.0);
                break;

            default:
                break;
        }

        return sum;
    }

    //check the priority of operators
    int check (char x){ 
    switch (x)
    {
        case add:
            return 1;
        case subtract:
            return 2;
        case divide:
        case multiple:
            return 3;
        case exp:
            return 4;
        default:
            return -1;
    }
}

};


int main() {

    char input[100]; //user input
    vector<string> sorted;

    stack<char> s1; 
    vector<string> s2;
    
    struct Calculator cal; //calculator

    printf ("Enter the equation: \n");
    scanf("%s",input);
    string str(input);

    int index = 0;
    for (int i=0;i<str.size();i++){

        if (i==0 && str[0]=='-'){
            i++;
        } 
        if (str[i]!=' '){
            if (!isdigit(str[i])){

                if (str[i]=='('){
                    sorted.push_back(str.substr(i,1));
                    index = i+1;
                } else if (str[i]==')'){
                    sorted.push_back(str.substr(index,i-index));
                    sorted.push_back(str.substr(i,1));
                    index=i+1;
                    if (i<str.size()-1 && !isdigit(str[i+1])){
                        index+=1;
                    }
                } else if (str[i]=='^'){
                    sorted.push_back(str.substr(index,i-index));
                    sorted.push_back(str.substr(i,1));
                    index=i+1;
                    if (i<str.size()-1 && !isdigit(str[i+1])){
                        index+=1;
                    }
                }else {
                    if (i>0 && !isdigit(str[i-1]) && (str[i-1]==')'||str[i-1]=='^')){
                        sorted.push_back(str.substr(i,1));
                    } else{
                        sorted.push_back(str.substr(index,i-index));
                        sorted.push_back(str.substr(i,1));
                    }
                    index=i+1;
                }
            } 
        } 
    }

    if (index< str.size() && isdigit(str[str.size()-1])){
        sorted.push_back(str.substr(index,str.size()));
    }

    for (int i = 0; i < sorted.size() ;i++){
        
        string s(sorted[i]);

        if (s.length()>1 || isdigit(s[0])){
            s2.push_back(sorted[i]);
        } else {
            if (s1.empty()||s[0]=='('||s1.top()=='('){
                s1.push(s[0]);
            } else if (s[0]!=')'){
                if (cal.check(s[0])>cal.check(s1.top())){
                    s1.push(s[0]);
                } else {
                    while (!s1.empty() && s1.top()!='(' && cal.check(s[0])<=cal.check(s1.top())){
                        string top (1,s1.top());
                        s2.push_back(top);
                        s1.pop();
                    }  
                    s1.push(s[0]);
                }
            } else if (s[0]==')'){
                while (s1.top()!='('){
                    string top (1,s1.top());
                    s2.push_back(top);
                    s1.pop();
                }
                s1.pop();
            }
        }
    }

    while (!s1.empty()){
        string top (1,s1.top());
        s2.push_back(top);
        s1.pop();
    }


    stack<double> values; 

    for (int i = 0; i < s2.size();i++){

        if (strlen(s2[i].c_str())>1 || atoi(s2[i].c_str())){
            values.push(atoi(s2[i].c_str()));
        }  else {
                double operand1 = values.top();
                values.pop();

                double operand2 = values.top();
                values.pop();

                double result = cal.calculate(operand2 , operand1, s2[i][0]);
                values.push(result);
        }
    }

    printf("The result of %s is %.2f\n", str.c_str(), cal.sum);

}
