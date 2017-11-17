
#include <stack>


class instruction{
	public:
		string type;
		string value;
		int argument;
		bool nextisequals;
		instruction(string type, bool nextisequals, int argument = 0,string value=""){
			this->nextisequals = nextisequals;
			this->type = type;
			this->value = value;
			this->argument = argument;
		}
};

stack<string> postfixstack;
stack<int> bracketstack;
vector<instruction *> output;
stack<bool> lastbracketwaspostfix;
bool stringopen;
int tabspaces = 4;
int tabdepth = 0;
int currenttabdepth = 0;
unsigned char spacesinarow;
string last;
bool wasliteral;
string s, sp, sm;


namespace {
	void calctabdepth(){
		currenttabdepth += 1;
		if(currenttabdepth > tabdepth){
			tabdepth = currenttabdepth;
			output.push_back(new instruction("INDENT", sp=="="));
		}
	}
	void calctabdepthend(){
		if(currenttabdepth < tabdepth){
			output.push_back(new instruction("DEDENT", sp=="="));
		}else{
			return;
		}
		tabdepth--;
		calctabdepthend();
	}

	constexpr unsigned int str2int(const char* str, int h=0){
		return !str[h] ?5381 : (str2int(str,h+1)*33) ^ str[h];
	}

	void
	prepare_literal(string current){
		if(last != "" && !output.empty()){
			output.back()->value += current;
			last = current;
		}else{
			output.push_back(new instruction("LITERAL",sp=="=",0,current));
			last = current;
		}
	}

	bool
	isbracket(string val){
		return val == "[" || val == "{" || val == "(" || val == "\"";
	}

	bool
	isnumeric(string val){
		return val == "0" || val == "1" || val == "2" || val == "4" || val == "5" || val == "6" || val == "7" || val == "8" || val == "9";
	}

	bool
	isoperator(string val){
		return val == "+" || val == "-" || val == "*" || val == "/" || val == "=" || val == ">" || val == "<" || val == "!" || val == "~" || (val == ")" && lastbracketwaspostfix.top());
	}

	char 
	getindex(string op){
		switch(str2int(op.c_str())){
			// assignment
			case str2int(":")	:{return 128;	}
			case str2int("=")	:{return 127;	}
			// .
			case str2int(".")	:{return 9;	}
			// +
			case str2int("+")	:{return 30;	}
			case str2int("++")	:{return 20;	}
			case str2int("+=")	:{return 10;	}
			// -
			case str2int("-")	:{return 30;	}
			case str2int("--")	:{return 20;	}
			case str2int("-=")	:{return 10;	}

			// *
			case str2int("*")	:{return 31;	}
			case str2int("**")	:{return 22;	}
			case str2int("*=")	:{return 11;	}

			// /
			case str2int("/")	:{return 31;	}
			case str2int("//")	:{return 31;	}
			case str2int("/=")	:{return 11;	}
			default				:{return 0;		}
		}
	}

	void 
	popuntilequal(string op)
	{
		char index = getindex(op);
		while(!postfixstack.empty() && getindex(postfixstack.top()) > index){
			output.push_back(new instruction(postfixstack.top(), sp=="="));
			postfixstack.pop();
		}				
	}

	void
	popuntil(string limit){
		while(!postfixstack.empty() && postfixstack.top() != limit){
			output.push_back(new instruction(postfixstack.top(), sp=="="));
			postfixstack.pop();
		}
		postfixstack.pop();
	}

	string
	nextnotspace(string str, int index, bool pos=true){
		string retval = "";
		string s;
		if(index > str.size() || index < 0){
			return retval;
		}
		if(pos){
			for 
			(int i = index+1; i < str.size(); ++i)
			{
				s = str.substr(i,1);
				if(s != " "){
					retval = s;
					break;
				}
			}	
			return retval;
		}else{
			for 
			(int i = index-1; i >= 0; i--)
			{
				s = str.substr(i,1);
				if(s != " "){
					retval = s;
					break;
				}
			}	
			return retval;
		}
	}

	template <typename T>
	void printstack(stack<T> stck){
		cout<<"printing stack"<<endl;
		for (int i = 0; i < stck.size(); ++i)
		{
			cout<<stck.top();
			stck.pop();
		}
		cout<<endl;
	}

	void popempty(){

		while(!postfixstack.empty()){
			output.push_back(new instruction(postfixstack.top(), sp=="="));
			postfixstack.pop();
		}		
	}
}


namespace lexer{
	void
	decode(string str)
	{
		currenttabdepth = 0;
		for
		(int i = 0; i < str.size(); ++i)
		{
			s 	= str.substr	(		i,	1		);
			sp	= nextnotspace	(str,	i,	true	);
			sm	= nextnotspace	(str,	i,	false	);
			if(stringopen){
				bracketstack.top() += 1;
			}
			if(s != "\t" && s != " " && spacesinarow == 0){
				calctabdepthend();
			}
			//brackets closing
					if(s == "]"											)	{		output.push_back(new instruction("LIST", sp=="=",bracketstack.top())); bracketstack.pop();											}
			else 	if(s == "}"											)	{		output.push_back(new instruction("DICT", sp=="=",bracketstack.top())); bracketstack.pop();											}
			else 	if(s == ")"	&& !lastbracketwaspostfix.top()			)	{		output.push_back(new instruction("TUPLE", sp=="=",bracketstack.top())); bracketstack.pop();	lastbracketwaspostfix.pop();			}
			else 	if(s == ")"	&& lastbracketwaspostfix.top()			)	{		popuntil("(");																					lastbracketwaspostfix.pop();		}
			else 	if(s == "\"" && stringopen							)	{					 output.push_back(new instruction("STRING",sp=="=",bracketstack.top()-2)); bracketstack.pop();stringopen = !stringopen;	}
			//brackets opening
			else 	if(s == "["											)	{		bracketstack.push(1);																												}
			else 	if(s == "{"											)	{		bracketstack.push(1);																												}
			else 	if(s == "("	&& !(isnumeric(sm) || isoperator(sm))	)	{		bracketstack.push(1);	lastbracketwaspostfix.push(false);																			}
			else 	if(s == "("	&&  (isnumeric(sm) || isoperator(sm))	)	{		postfixstack.push("(");	lastbracketwaspostfix.push(true);																			}
			else 	if(s == "\""&& !stringopen							)	{		bracketstack.push(1);	stringopen = !stringopen	;																				}
			//block
			else 	if(s == ":"											)	{		popuntilequal(":");		output.push_back(new instruction(":",sp=="="));																		}
			//assignment			
			else 	if(s == "=" && sp != "="							)	{		popuntilequal("=");		postfixstack.push("=");																						}
			//lists
			else 	if(s == ","											)	{		bracketstack.top() += 1;																											}
			//comparison
			else 	if(s == "=" && sp == "="							)	{i+=1; 	popuntilequal("==");	postfixstack.push("==");																					}
			else 	if(s == "!" && sp == "="							)	{i+=1; 	popuntilequal("!=");	postfixstack.push("!=");																					}
			else 	if(s == ">" && sp == "="							)	{i+=1; 	popuntilequal(">=");	postfixstack.push(">=");																					}
			else 	if(s == "<" && sp == "=" 							)	{i+=1; 	popuntilequal("<=");	postfixstack.push("<=");																					}			
			else 	if(s == ">" && sp != "="							)	{		popuntilequal(">");		postfixstack.push(">");																						}
			else 	if(s == "<" && sp != "=" 							)	{		popuntilequal("<");		postfixstack.push("<");																						}			
			// +
			else 	if(s == "+" && sp == "+"							)	{i+=1; 	popuntilequal("++");	postfixstack.push("++");																					}
			else 	if(s == "+" && sp != "+"							)	{		popuntilequal("+");		postfixstack.push("+");																						}
			else 	if(s == "+" && sp == "="							)	{i+=1;	popuntilequal("+=");	postfixstack.push("+=");																					}
			// -
			else 	if(s == "-" && sp == "-"							)	{i+=1;	popuntilequal("--");	postfixstack.push("--");																					}
			else 	if(s == "-" && sp != "-"							)	{		popuntilequal("-");		postfixstack.push("-");																						}
			else 	if(s == "-" && sp == "="							)	{i+=1;	popuntilequal("-=");	postfixstack.push("-=");																					}
			// *
			else 	if(s == "*" && sp == "*"							)	{i+=1;	popuntilequal("**");	postfixstack.push("**");																					}
			else 	if(s == "*" && sp != "*"							)	{		popuntilequal("*");		postfixstack.push("*");																						}
			else 	if(s == "*" && sp == "="							)	{i+=1;	popuntilequal("*=");	postfixstack.push("*=");																					}
			// /
			else 	if(s == "/" && sp == "/"							)	{i+=1;	popuntilequal("//");	postfixstack.push("//");																					}
			else 	if(s == "/" && sp != "/"							)	{		popuntilequal("/");		postfixstack.push("/");																						}
			else 	if(s == "/" && sp == "="							)	{i+=1;	popuntilequal("/=");	postfixstack.push("/=");																					}
			// .
			else 	if(s == "." && !isnumeric(sp)						)	{		popuntilequal(".");	postfixstack.push(".");																							}
			// #
			else 	if(s == "#" && !stringopen							)	{		break;																																}
			//tab
			else	if(s == "\t"										)	{calctabdepth();																															}
			//other
			else	if(s == " "											)	{if(spacesinarow == tabspaces-1){spacesinarow = 0;calctabdepth();}else{spacesinarow ++;}continue;											}
			else															{prepare_literal(s);	wasliteral = true;																									}
		
			if(s != " "){spacesinarow = 0;}
			if(!wasliteral){last = "";}
			wasliteral = false;

		}
		popempty();
		output.push_back(new instruction("EOL",sp=="="));
	}


	vector<instruction *> code(){

		for(auto& i : output){
			cout<<i->type<<"";
			if(i->argument != 0){
				cout<<"("<<i->argument<<") ";
			}
			if(i->value != ""){
				cout<<"["<<i->value<<"] ";
			}
		}
		cout<<endl;
		return output;
	}

}