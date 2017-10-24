#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cmath> 

using namespace std;

#include "./include.h"
#include "./filereader.h"
#include "./filewriter.h"
#include "./istype.h"
#include "./types.h"

#include "./executer.h"

void print(stack<string> a){
    while (!a.empty()) {
        cout<<a.top()<<", ";
        a.pop();
    }

    cout<<endl;
}


class instruction{
    public:
        string type;
        string value;
        instruction(string type, string value = ""){
            this->type = type;
            this->value = value;
        }
};

int getimportance(string type){

    //allways first/lowest value!
    if(type=="assignment"){
        return 1;
    }  

    if(type=="or"){
        return 3;
    }

    if(type=="xor"){
        return 4;
    }

    //and
    if(type=="and"){
        return 5;
    }

    //shift
    if(type=="Lshift" || type == "Rshift"){
        return 6;
    }

    //add,sub
    if(type=="add" || type == "sub"){
        return 7;
    }

    //mul,div
    if(type=="mul" || type == "div" || type == "truediv"){
        return 8;
    }

    //power
    if(type == "pow"){
        return 9;
    }    

    //unary
    if(type=="unary_neg" || type == "unary_not"){
        return 10;
    }
    
    if(type=="call"){
        return 11;
    }

    return 0;
}

void rem(vector<instruction> * postfix, stack<instruction> * opstack, string type){
    if(!opstack->empty()){
        while(!opstack->empty() && getimportance(opstack->top().type) >= getimportance(type)){  
            postfix->push_back(opstack->top());
            opstack->pop(); 
        }
    }
}

int main(int argc, char *argv[]){
    string infix;
    vector<instruction> postfix;
    string c,c1,c_1;
    stack<instruction> opstack;
    map<int,string> constants;
    map<int,string> type;
    map<string,int> variables;
    int v_counter = 0;
    int c_counter = 0;


    if(argc < 2){
        cout << "no input file provided" <<endl;
        return 0;
    }

    filereader * file = new filereader(argv[1]);
    while(!file->eof){
        infix = file->next();
        
        if(infix.empty()){
            continue;
        }

        int i_t;

        for (int i = 0; i < infix.size(); ++i)
        {

            c = infix.at(i);
            if(i != infix.size()-1){
                i_t = i+1;
                c1 = " ";
                while(true){
                    c1 = infix.at(i_t);
                    i_t++;
                    if(i_t == infix.size() - 1){break;}
                    if(c1 != " "){break;}
                }
            } 
            if(i > 0){
                i_t = i-1;
                c_1 = " ";
                while(true){
                    c_1 = infix.at(i_t);
                    i_t--;
                    if(i_t < 0){break;}
                    if(c_1 != " "){break;}
                }
            }

            cout<<c_1<<" "<<c<<" "<<c1<<endl;

            if (isinteger(c) || (c == "." && isinteger(c_1) && isinteger(c1))){
                string s = ""; 
                bool flt = false;
                while(isinteger(c) || (c == "." && isinteger(c_1) && isinteger(c1))){
                    if(i == infix.size()){
                        break;
                    }
                    if(c == "."){
                        flt = true;
                    }

                    c = infix.at(i);
                    if(i != infix.size()-1){c1 = infix.at(i+1);} 
                    
                    if(i > 0){c_1 = infix.at(i-1);}
                    if(isinteger(c) || (c == "." && isinteger(c_1) && isinteger(c1)) && c != " "){
                        s += c;
                    }else{
                        i--;
                    }
                    i++;
                }
                c_counter++;
                constants[c_counter] = s;
                type[c_counter] = flt?"float":"int";

                postfix.push_back(instruction("number",to_string(c_counter)));

                i--;
            }
            else if (c == "="                                                    ){rem(&postfix,&opstack,"assignment");      opstack.push(instruction("assignment"));    }
            else if (c == "=="                                                   ){rem(&postfix,&opstack,"checkequal");      opstack.push(instruction("checkequal"));    }
            else if (c == "-" && !isinteger(c_1) && (isinteger(c1) || c1 == "(") ){rem(&postfix,&opstack,"unary_neg" );      opstack.push(instruction("unary_neg"));     }
            else if (c == "+"                                                    ){rem(&postfix,&opstack,"add"       );      opstack.push(instruction("add"));           }
            else if (c == "-"                                                    ){rem(&postfix,&opstack,"sub"       );      opstack.push(instruction("sub"));           }
            else if (c == "*" && c1 != "*"                                       ){rem(&postfix,&opstack,"mul"       );      opstack.push(instruction("mul"));           }
            else if (c == "/" && c1 != "/"                                       ){rem(&postfix,&opstack,"div"       );      opstack.push(instruction("div"));           }
            else if (c == "*" && c1 == "*"                                       ){rem(&postfix,&opstack,"pow"       );      opstack.push(instruction("pow"));      i++; }
            else if (c == "/" && c1 == "/"                                       ){rem(&postfix,&opstack,"truediv"   );      opstack.push(instruction("truediv"));  i++; }
            else if (c == "("                                                    ){                                          opstack.push(instruction("open"));          }
            else if (c == ")"                                                    ){
                while(opstack.top().type!="open"){
                    postfix.push_back(opstack.top());
                    opstack.pop();
                }
                opstack.pop();
            }
            else if (isvariablestart(c) && c1 == "="){
                string s = c;
                while(true){
                    i++;
                    c = infix.at(i);
                    s += c;
                    if (c == " " || c == "\n"){break;}              
                }
                postfix.push_back(instruction("assignment-variable",s));
                if (variables.count(s)){
                    variables[s] = v_counter;
                    v_counter++;
                }
            }
            else if (isvariablestart(c)){
                string s = c;
                while(true){
                    i++;
                    c = infix.at(i);
                    s += c;
                    if (c == " " || c == "\n" || isoperator(c)){break;}  
                    if(i == infix.size()-1){break;}            
                }
                i--;
                postfix.push_back(instruction("variable",s));
            }
            else{continue;}
        }

        while(!opstack.empty()){ 
            postfix.push_back(opstack.top());
            opstack.pop();
        }

        cout<<infix<<endl;
        for (auto& t : type)
            cout << t.first << ":" << t.second << "; ";
        cout<<endl;
        for (auto& t : constants)
            cout << t.first << ":" << t.second << "; ";
        cout<<endl;
        for (auto& t :  postfix)
            cout << t.type << " " << t.value << "; ";
        cout<<endl;
    }
    vector<unsigned char> program = {ES};
    unsigned char value;
    stack<vector<unsigned char>> vars;

    for(auto& i:postfix){
             if (i.type == "assignment"  ){  
                program.push_back(SV);
                program.push_back(vars.top().at(0));
                program.push_back(vars.top().at(1));
                program.push_back(vars.top().at(2));
                program.push_back(vars.top().at(3));
                vars.pop();     
            }
        else if (i.type == "assignment-variable"){
            vector<unsigned char> var;
            value = variables[i.value];

            var.push_back((value >> 24) & 0xFF);
            var.push_back((value >> 16) & 0xFF);
            var.push_back((value >> 8) & 0xFF);
            var.push_back(value & 0xFF);
            vars.push(var);
        }
        else if (i.type == "variable"){
            program.push_back(LV);
            value = variables[i.value];

            program.push_back((value >> 24) & 0xFF);
            program.push_back((value >> 16) & 0xFF);
            program.push_back((value >> 8) & 0xFF);
            program.push_back(value & 0xFF);
        }
        else if (i.type == "add"         ){  program.push_back(ADD);         }
        else if (i.type == "sub"         ){  program.push_back(SUB);         }
        else if (i.type == "mul"         ){  program.push_back(MUL);         }
        else if (i.type == "div"         ){  program.push_back(DIV);         }
        else if (i.type == "unary_neg"   ){  program.push_back(UNARY_NEG);   }
        else if (i.type == "truediv"     ){  program.push_back(TRUEDIV);     }
        else if (i.type == "pow"         ){  program.push_back(POW);         }
        else {
            program.push_back(LC);
            value = (unsigned char)atoi(i.value.c_str());
            program.push_back((value >> 24) & 0xFF);
            program.push_back((value >> 16) & 0xFF);
            program.push_back((value >> 8) & 0xFF);
            program.push_back(value & 0xFF);
        }
    }
    program.push_back(STP);

    map<int,variable *> constants_new;
    for(auto& i : constants){
        if(type[i.first] == "float"){
            constants_new[i.first] = new float_var(stof(i.second));
        }
        else if(type[i.first] == "int"){
            constants_new[i.first] = new int_var(atoi(i.second.c_str()));
        }
    }

    for (auto& t :  program)
        cout << to_string(t) << "; ";
    cout<<endl;           

    execute(program,constants_new);
}




// treeitem a = {"hey"};
// treeitem * b = &a;
// objectTree * tree = new objectTree(b);
// tree->appendChild(b,true);
// tree->appendChild(b);
// tree->appendChild(b);
// // tree->moveback();
// tree->select(0);
// tree->print();






















