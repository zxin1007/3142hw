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
                sum = pow(value1 , value2);
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
        case subtract:
            return 1;
        case divide:
        case multiple:
            return 2;
        case exp:
            return 3;
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

    int index = 0; //store the postion of currrent operand
    int i=0; //

    if (str[0]=='-'){ //if the first pace was a - which means it's negative
        i++;
    } 

    //iterate through user's input
    //split operand and operator into vector sorted by locating the operator
    for (i=i;i<str.size();i++){

        if (str[i]!=' '){
            //detect if it's operater
            if (!isdigit(str[i]))
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
    //detect if the last place is a number and added to vector
    if (index< str.size() && isdigit(str[str.size()-1])){
        sorted.push_back(str.substr(index,str.size()));
    }

    //iterate through the sorted user input
    //s1 will store the the operators and use to check the precedence of operators 
    //s2 will store the operands and operators in precedence.
    for (int i = 0; i < sorted.size() ;i++){
        
        string s(sorted[i]);

        // add the operand to s2
        if (s.length()>1 || isdigit(s[0])){
            s2.push_back(sorted[i]);
        } else { //if it operator
            //if stack s1 is empty or the top of the s1 is open parentheses or the current opeerator is a open parentheses 
            //push the operator into s1
            if (s1.empty()||s[0]=='('||s1.top()=='('){
                s1.push(s[0]);
            } else if (s[0]!=')'){ 
                //if the operator is not a close parentheses
                //check the priority of the operator
                //if current operator is prior than stack's top, push it to stack
                if (cal.check(s[0])>cal.check(s1.top())){
                    s1.push(s[0]);
                } else {
                    //if it's not prior than stack top, push the the top into s2, and pop the top of stack which result in empty stack/a new top
                    //keep comparing the top until the stack is empty or the current operator is prior than top
                    while (!s1.empty() && s1.top()!='(' && cal.check(s[0])<=cal.check(s1.top())){
                        string top (1,s1.top());
                        s2.push_back(top);
                        s1.pop();
                    }  
                    s1.push(s[0]);
                }
            } else if (s[0]==')'){ //if the operator is close parentheses
                //push the top into s2 unitl top is a open parentheses
                while (s1.top()!='('){
                    string top (1,s1.top());
                    s2.push_back(top);
                    s1.pop();
                }
                s1.pop();
            }
        }
    }
    //if s1 is not empty push all the rest operator into s2
    while (!s1.empty()){
        string top (1,s1.top());
        s2.push_back(top);
        s1.pop();
    }


    stack<double> values; 

    //iterate through s2
    for (int i = 0; i < s2.size();i++){

        //if it a number, push it the value stack
        if (strlen(s2[i].c_str())>1 || atoi(s2[i].c_str())){
            values.push(atoi(s2[i].c_str()));
        }  else {
            //if it operator
            //get the two element from value stack
            double operand1 = values.top();
            values.pop();

            double operand2 = values.top();
            values.pop();

            //cal struct function
            double result = cal.calculate(operand2 , operand1, s2[i][0]);
            //push the result into values stack
            values.push(result);
        }
    }
    //end; print the sum
    printf("The result of %s is %.2f\n", str.c_str(), cal.sum);

}
