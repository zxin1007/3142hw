// Zixin Zou
//This calculator program will translate user/file input of strings
//translate the string into postfix expression
//and calculate the result

// write the expression in the testcase.txt.
// have () for square root such as 9^(1/2)
// no () need for exp
// - for minus, + for add, * for multiply, / for divide

#include <iostream>
#include<stdio.h>
#include <math.h>  
#include <stack>
#include <vector>
#include <fstream>

using namespace std; 
void evaluate(string str);

struct Calculator{
    
    enum operators { add='+', subtract='-', divide='/', multiple='*', exp='^'};

    double sum; //store the sum

    Calculator(){ //initalize the sum to 0 when struct created
        sum = 0;
    }

    double calculate(double value1, double value2, char c){
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
}cal; //calculator

int main() {

    //test cases
    ifstream in_stream;
    in_stream.open("testcase.txt"); //opening the file.

    if (!in_stream.fail()) { //if the file is open
        string line;

        while (getline(in_stream,line)) {
            evaluate(line);
        }
    }

    in_stream.close();

    printf("--finished-- Modify testcase.txt for expressions \n");
}

void evaluate (string str){
    stack<char> s1; 
    vector<string> s2;
    string operand = ""; //store the current digit
    int index = 0; //use to keep track the last operand
    int i=0;

    if (str[0]=='-'){ //if the first pace was a - which means it's negative
        i++;
        operand+= (char)str[0];
    } 

    //iterate through the user input
    //s1 will store the the operators and use to check the precedence of operators 
    //s2 will store the operands and operators in precedence.
    for (i = i; i < str.size() ;i++){

        if (!isdigit(str[i]) && str[i]!='.'){

            if (operand!=""){ //push in the tracked operand before this operator
                s2.push_back(operand);
                operand="";
                //printf("%s\n", operand.c_str());
                index = i+1;
            }
            //if stack s1 is empty or the top of the s1 is open parentheses or the current opeerator is a open parentheses 
            //push the operator into s1
            if (s1.empty()||str[i]=='('||s1.top()=='('){
                //deal with 3(...) = 3*(...)
                if (i>0 && str[i]=='(' && isdigit(str[i-1])){
                    s1.push('*');
                }
                s1.push(str[i]);
            } else if (str[i]!=')'){ 
                //if the operator is not a close parentheses
                //check the priority of the operator
                //if current operator is prior than stack's top, push it to stack
                if (cal.check(str[i])>cal.check(s1.top())){
                        s1.push(str[i]);
                } else {
                    //if it's not prior than stack top, push the the top into s2, and pop the top of stack which result in empty stack/a new top
                    //keep comparing the top until the stack is empty or the current operator is prior than top
                    while (!s1.empty() && s1.top()!='(' && cal.check(str[i])<=cal.check(s1.top())){
                        string top (1,s1.top());
                        s2.push_back(top);
                        s1.pop();
                    }  
                    s1.push(str[i]);
                }

                if (i<str.size()-1 && !isdigit(str[i+1])){
                    index+=1;
                }
            } else if (str[i]==')'){ //if the operator is close parentheses
                //push the top into s2 unitl top is a open parentheses
                while (s1.top()!='('){
                    string top (1,s1.top());
                    s2.push_back(top);
                    s1.pop();
                }
                s1.pop();

                //deal with (...)3 = (...)*3
                if (i>1 && (isdigit(str[i+1])||str[i+1]=='(')){
                    s1.push('*');
                }
                //deal with consecutive operator
                if (i<str.size()-1 && !isdigit(str[i+1])){
                    index+=1;
                }
            }
        } else if ((str[i]>='0'&&str[i]<='9') || str[i]=='.'){
            operand += (char) str[i];
        } 
    }

    //detect if the last place is a number and added to s2
    if (index< str.size() && isdigit(str[str.size()-1])){
        s2.push_back(str.substr(index,str.size()));
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
        if (strlen(s2[i].c_str())>1 || atof(s2[i].c_str())){
            values.push(atof(s2[i].c_str()));
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
    printf("The result of %s is %.2f\n\n", str.c_str(), cal.sum);
}
