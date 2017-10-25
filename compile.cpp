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
#include "./block.h"

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
    map<int,codeblock> blocks;
    codeblock * global_block = new codeblock();
    codeblock * current = global_block;

    // vector<unsigned char> program = {ES};
    unsigned char value;
    stack<vector<unsigned char>> vars;
    // map<int,variable *> constants_new;

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
                    if(i_t == infix.size() - 1){break;}
                    i_t++;
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
            else if (c == "["                                                    ){
                


                
            }
            else if (c == ";"                                                    ){continue;}
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
            else if (isvariablestart(c)){
                string s = c;
                while(true){
                    i++;
                    c = infix.at(i);
                    if (c == " " || c == "\n" || isoperator(c) || c=="="){break;} 
                    s += c;             
                }
                i--;

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

                if(c1 == "("){
                    rem(&postfix,&opstack,"call"       );
                    opstack.push(instruction("call"));



                }

                // if(s == "function"){
                //     current = current->add_codeblock()
                //     //


                // }
                else if(c1 == " " || c1 != "="){
                    postfix.push_back(instruction("variable",s));
                }else{
                    postfix.push_back(instruction("assignment-variable",s));
                    if (variables.count(s)){
                        variables[s] = v_counter;
                        v_counter++;
                    }     
                }
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

        for(auto& i:postfix){

            if (i.type == "assignment"  ){  
                    current->add_instruction(SV);
                    current->add_instruction(vars.top().at(0));
                    current->add_instruction(vars.top().at(1));
                    current->add_instruction(vars.top().at(2));
                    current->add_instruction(vars.top().at(3));
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
                current->add_instruction(LV);
                value = variables[i.value];

                current->add_instruction((value >> 24) & 0xFF);
                current->add_instruction((value >> 16) & 0xFF);
                current->add_instruction((value >> 8) & 0xFF);
                current->add_instruction(value & 0xFF);
            }
            else if (i.type == "add"         ){  current->add_instruction(ADD);         }
            else if (i.type == "sub"         ){  current->add_instruction(SUB);         }
            else if (i.type == "mul"         ){  current->add_instruction(MUL);         }
            else if (i.type == "div"         ){  current->add_instruction(DIV);         }
            else if (i.type == "unary_neg"   ){  current->add_instruction(UNARY_NEG);   }
            else if (i.type == "truediv"     ){  current->add_instruction(TRUEDIV);     }
            else if (i.type == "pow"         ){  current->add_instruction(POW);         }
            else {
                current->add_instruction(LC);
                value = (unsigned char)atoi(i.value.c_str());
                current->add_instruction((value >> 24) & 0xFF);
                current->add_instruction((value >> 16) & 0xFF);
                current->add_instruction((value >> 8) & 0xFF);
                current->add_instruction(value & 0xFF);
            }
           

        }

        for(auto& i : constants){
            if(type[i.first] == "float"){
                current->add_constant(i.first,new float_var(stof(i.second)));
            }
            else if(type[i.first] == "int"){
                current->add_constant(i.first,new int_var(atoi(i.second.c_str())));
            }
        }

        postfix.clear();
        constants.clear();

        for (auto& t : global_block->code)
            cout << to_string(t) << "; ";
        cout<<endl;

    }
    global_block->add_instruction(STP);        
    execute(global_block);
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






















