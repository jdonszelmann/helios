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

#include "./exec.h"

struct treeitem{
	string name;
	int linennum;
	int type;
};

struct Current{
	void * current;
};

class objectTree{
	public:
		// struct * content;
		treeitem * content;
		vector<objectTree *> childs;
		objectTree * parent;
		Current * current;

		objectTree(objectTree * parent, Current * current, treeitem * content){
			this->content = content;
			this->parent = parent;
			this->current = current;
		}

		objectTree(treeitem * content){
			this->content = content;
			this->parent = this;
			Current * current = new Current();
			current->current = this;
			this->current = current;
		}

		objectTree * appendChild(treeitem * content, bool select = false){
			objectTree * temp = static_cast<objectTree *>(this->current->current);
			objectTree * item = new objectTree(temp,this->current,content);
			if(select){
				item->current->current = item;
			}
			temp->childs.push_back(item);
			return item;
		}

		void moveback(){
			this->current->current=static_cast<objectTree *>(this->current->current)->parent;
		}

		void printall(){
			if(this->parent = this){
				this->print(0);
				return;
			}else{
				parent->print();
				return;
			}
		}

		objectTree * top(){
			if(this->parent = this){
				return this;
			}else{
				return this->parent->top();
			}
		}

		void settop(){
			if(this->parent = this){
				this->current->current = this;
				return;
			}else{
				this->parent->top();
				return;
			}
		}

		void select(int item){
			if (item < static_cast<objectTree *>(this->current->current)->childs.size()){
				this->current->current = static_cast<objectTree *>(this->current->current)->childs[item];
			}
		}

		void print(int indent = 0){
			for (int i = 0; i < indent-1; ++i)
			{
				cout<<char(179);
			}
			if (indent>0){
				cout<<char(195);
			}
			if (this->childs.size()==0){
				cout<<char(196);
			}else{
				cout<<char(194);
			}

			if (this->current->current == this){
				cout<<this->content->name<<" <--CURRENT"<<endl;
			}else{
				cout<<this->content->name<<endl;
			}

			for (int i = 0; i < this->childs.size(); ++i)
			{
				this->childs[i]->print(indent + 1);
			}
		}
};

void print(stack<string> a){
	while (!a.empty()) {
		cout<<a.top()<<", ";
		a.pop();
	}

	cout<<endl;
}

int getimportance(string type){
	

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

void rem(vector<string> * postfix, stack<string> * opstack, string type){

	if(!opstack->empty()){
		while(getimportance(opstack->top()) > getimportance(type) && !opstack->empty()){
			postfix->push_back(opstack->top());
			opstack->pop(); 
		}
	}
}

int main(int argc, char *argv[]){
	string infix;
	vector<string> postfix;
	string c,c1,c_1;
	stack<string> opstack;
	map<int,string> constants;
	map<int,string> type;
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
					c_1 = infix.at(i_t);
					i_t--;
					if(i_t == infix.size() + 1){break;}
					if(c_1 != " "){break;}
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

				postfix.push_back(to_string(c_counter));

				i--;
			}
			else if (c == "-" && !isinteger(c_1) && isinteger(c1)){rem(&postfix,&opstack,"unary_neg" );      opstack.push("unary_neg");     }
			else if (c == "+"                                    ){rem(&postfix,&opstack,"add"       );      opstack.push("add");           }
			else if (c == "-"                                    ){rem(&postfix,&opstack,"sub"       );      opstack.push("sub");           }
			else if (c == "*" && c1 != "*"                       ){rem(&postfix,&opstack,"mul"       );      opstack.push("mul");           }
			else if (c == "/" && c1 != "/"                       ){rem(&postfix,&opstack,"div"       );      opstack.push("div");           }
			else if (c == "*" && c1 == "*"                       ){rem(&postfix,&opstack,"pow"       );      opstack.push("pow");      i++; }
			else if (c == "/" && c1 == "/"                       ){rem(&postfix,&opstack,"truediv"   );      opstack.push("truediv");  i++; }
			else if (c == "("                                    ){rem(&postfix,&opstack,"add"       );      opstack.push("open");          }
			else if (c == ")"                                    ){
				while(opstack.top()!="open"){
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
					s += c;
					if (c == " " || c == "\n"){break;} 				
				}
			}
		}

		while(!opstack.empty()){ 
			postfix.push_back(opstack.top());
			opstack.pop();
		}

		cout<<infix<<endl;
		for (auto& t : type)
			cout << t.first << " " << t.second << "; ";
		cout<<endl;
		for (auto& t : constants)
			cout << t.first << " " << t.second << "; ";
		cout<<endl;
		for (auto& t :  postfix)
			cout << t << "; ";
		cout<<endl;
	}
	vector<unsigned char> program;
	unsigned char value;

	for(auto& i:postfix){
			 if (i == "add"			){	program.push_back(ADD);			}
		else if (i == "sub"			){	program.push_back(SUB);			}
		else if (i == "mul"		 	){	program.push_back(MUL);			}
		else if (i == "div"		 	){	program.push_back(DIV);			}
		else if (i == "unary_neg"	){	program.push_back(UNARY_NEG);	}
		else if (i == "truediv"		){	program.push_back(TRUEDIV);	}
		else if (i == "pow"			){	program.push_back(POW);	}
		else {
			program.push_back(LC);
			value = (unsigned char)atoi(i.c_str());
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






















