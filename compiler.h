 
#include "types.h"
#include "block.h"
#include "executer.h"

stack<vector<unsigned char>> vars;
unsigned char value;
bool wasvar;

namespace {
	bool 
	is_number(string line)
	{
		char* p;
		strtol(line.c_str(), &p, 10);
		return *p == 0;
	}

	static 
	bool 
	is_float_number(const std::string& string){
	string::const_iterator it = string.begin();
		bool decimalPoint = false;
		int minSize = 0;
		if(string.size()>0 && (string[0] == '-' || string[0] == '+')){
			it++;
			minSize++;
		}
		while(it != string.end()){
			if(*it == '.'){
				if(!decimalPoint) decimalPoint = true;
				else break;
			}else if(!std::isdigit(*it) && ((*it!='f') || it+1 != string.end() || !decimalPoint)){
				break;
			}
			++it;
		}
		return string.size()>minSize && it == string.end();
	}
}



namespace compiler{
	codeblock * global = new codeblock();
	codeblock * current = global;
	int const_counter;
	int var_counter;

	void compile(vector<instruction *> code){
		instruction * s;
		instruction * sp;
		for (int i = 0; i < code.size(); ++i)
		{
			s = code[i];
			if(i != code.size()){
				sp = code[i+1];
			}
			if(s->type == "LITERAL"){
				wasvar = false;
				cout<<endl;
				cout<<s->value<<endl;
				//string
				if(sp->type == "STRING"){
					const_counter++;
					current->add_constant(const_counter, new string_var(s->value));
					cout<<"string"<<endl;
				}
				//float
				else if(s->value.find('.') != std::string::npos && is_float_number(s->value) && sp->type != "STRING"){
					const_counter++;
					current->add_constant(const_counter,new float_var(atof(s->value.c_str())));
					cout<<"float"<<endl;
				}
				//int
				else if(s->value.find('.') == std::string::npos && is_number(s->value) && sp->type != "STRING"){
					const_counter++;
					current->add_constant(const_counter,new int_var(atoi(s->value.c_str())));
					cout<<"int"<<endl;
				}			
				//variable
				else{
					wasvar = true;
					cout<<"var"<<endl;
					if(s->nextisequals){
						vector<unsigned char> var;
						s->value;
						cout<<"--> "<<s<<endl;
						var.push_back((value >> 24) & 0xFF);
						var.push_back((value >> 16) & 0xFF);
						var.push_back((value >> 8) & 0xFF);
						var.push_back(value & 0xFF);
						vars.push(var);
					}else{
						current->add_instruction(LV);
						value = var_counter;

						current->add_instruction((value >> 24) & 0xFF);
						current->add_instruction((value >> 16) & 0xFF);
						current->add_instruction((value >> 8) & 0xFF);
						current->add_instruction(value & 0xFF);
						var_counter++;
					}
				}
				if(!wasvar){
					current->add_instruction(LC);
					value = const_counter;
					current->add_instruction((value >> 24) & 0xFF);
					current->add_instruction((value >> 16) & 0xFF);
					current->add_instruction((value >> 8) & 0xFF);
					current->add_instruction(value & 0xFF);					
				}


			}else if(s->type == "LIST"){
				cout<<s->argument<<endl;
				cout<<"list"<<endl;
				current->add_instruction(LST);        
				value = s->argument;
				current->add_instruction((value >> 24) & 0xFF);
				current->add_instruction((value >> 16) & 0xFF);
				current->add_instruction((value >> 8) & 0xFF);
				current->add_instruction(value & 0xFF);				
			}			
			//operators	
			else if(s->type == "="){
				current->add_instruction(SV);
				current->add_instruction(vars.top().at(0));
				current->add_instruction(vars.top().at(1));
				current->add_instruction(vars.top().at(2));
				current->add_instruction(vars.top().at(3));
				vars.pop();  
			}
			//+
			else if(s->type == "+"){
				current->add_instruction(ADD);
			}else if(s->type == "++"){
				
			}else if(s->type == "+="){
				
			}
			//-
			else if(s->type == "-"){
				current->add_instruction(SUB);
			}else if(s->type == "--"){
				
			}else if(s->type == "-="){
				
			}else if(s->type == "NEG"){
				current->add_instruction(UNARY_NEG);
			}
			//*
			else if(s->type == "*"){
				current->add_instruction(MUL);
			}else if(s->type == "**"){
				current->add_instruction(POW);
			}
			else if(s->type == "*="){
				
			}
			else if(s->type == "**="){
				
			}
			// /
			else if(s->type == "/"){
				current->add_instruction(DIV);
			}else if(s->type == "//"){
				current->add_instruction(TRUEDIV);	
			}else if(s->type == "/="){
				
			}			
			else if(s->type == "//="){
				
			}else{
				//
			}
		}
		current->add_instruction(STP);
		for(auto& i:current->code){
			cout<<to_string(i);
		}
		cout<<endl;
		for (auto& t : current->constants)
            cout << t.first << " " << t.second->print() <<endl;
		execute(current);
	}
}