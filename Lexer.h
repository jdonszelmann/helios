
#include <stack>

stack<string> postfixstack;
stack<string> bracketstack;
vector<string> output;
stack<bool> lastbracketwaspostfix;


namespace {
	constexpr unsigned int str2int(const char* str, int h=0){
		return !str[h] ?5381 : (str2int(str,h+1)*33) ^ str[h];
	}

	bool
	isbracket(string val){
		return val == "[" || val == "{" || val == "(" || val == "\"";
	}

	bool
	isnumeric(string val){
		return val == "1" || val == "1" || val == "2" || val == "4" || val == "5" || val == "6" || val == "7" || val == "8" || val == "9" || val == "0";
	}

	bool
	isoperator(string val){
		return val == "+" || val == "-" || val == "*" || val == "/" || val == "=" || val == ">" || val == "<" || val == "!" || val == "~" || (val == ")" && lastbracketwaspostfix.top());
	}	

	char 
	getindex(string op){
		switch(str2int(op.c_str())){
			// assignment
			case str2int("=")	:{return 128;	}
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
			output.push_back(postfixstack.top());
			postfixstack.pop();
		}				
	}

	void
	popuntil(string limit){
		while(!postfixstack.empty() && postfixstack.top() != limit){
			output.push_back(postfixstack.top());
			postfixstack.pop();
		}
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
}


namespace lexer{
	void
	decode(string str)
	{
		string s, sp, sm;
		for
		(int i = 0; i < str.size(); ++i)
		{
			s 	= str.substr	(		i,	1		);
			sp	= nextnotspace	(str,	i,	true	);
			sm	= nextnotspace	(str,	i,	false	);
	
			//brackets closing
					if(s == "]"											)	{		output.push_back(bracketstack.top()); bracketstack.pop()								}
			else 	if(s == "}"											)	{		output.push_back(bracketstack.top()); bracketstack.pop()								}
			else 	if(s == ")"	&& !lastbracketwaspostfix.top()			)	{		output.push_back(bracketstack.top()); bracketstack.pop()	lastbracketwaspostfix.pop();}
			else 	if(s == ")"	&& lastbracketwaspostfix.top()			)	{		popuntil(	"("		);										lastbracketwaspostfix.pop();}
			else 	if(s == "\""										)	{		output.push_back(bracketstack.top()); bracketstack.pop()								}
			//brackets opening
			else 	if(s == "["											)	{		bracketstack.push(0);																	}
			else 	if(s == "{"											)	{		bracketstack.push(0);																	}
			else 	if(s == "("	&& !(isnumeric(sm) || isoperator(sm))	)	{		bracketstack.push(0);	lastbracketwaspostfix.push(false);								}
			else 	if(s == "("	&&  (isnumeric(sm) || isoperator(sm))	)	{		postfixstack.push("(");	lastbracketwaspostfix.push(true);								}
			else 	if(s == "\""										)	{		bracketstack.push(0);																	}
			//assignment
			else 	if(s == "=" && sp != "="							)	{		popuntilequal("=");		postfixstack.push("=");											}
			//lists
			else 	if(s == ","											)	{		bracketstack.top() += 1																	}
			//comparison
			else 	if(s == "=" && sp == "="							)	{i+=1; 	popuntilequal("==");	postfixstack.push("==");										}
			else 	if(s == "!" && sp == "="							)	{i+=1; 	popuntilequal("!=");	postfixstack.push("!=");										}
			else 	if(s == ">" && sp == "="							)	{i+=1; 	popuntilequal(">=");	postfixstack.push(">=");										}
			else 	if(s == "<" && sp == "=" 							)	{i+=1; 	popuntilequal("<=");	postfixstack.push("<=");										}			
			else 	if(s == ">" && sp != "="							)	{		popuntilequal(">");		postfixstack.push(">");											}
			else 	if(s == "<" && sp != "=" 							)	{		popuntilequal("<");		postfixstack.push("<");											}			
			// +
			else 	if(s == "+" && sp == "+"							)	{i+=1; 	popuntilequal("++");	postfixstack.push("++");										}
			else 	if(s == "+" && sp != "+"							)	{		popuntilequal("+");		postfixstack.push("+");											}
			else 	if(s == "+" && sp == "="							)	{i+=1;	popuntilequal("+=");	postfixstack.push("+=");										}
			// -
			else 	if(s == "-" && sp == "-"							)	{i+=1;	popuntilequal("--");	postfixstack.push("--");										}
			else 	if(s == "-" && sp != "-"							)	{		popuntilequal("-");		postfixstack.push("-");											}
			else 	if(s == "-" && sp == "="							)	{i+=1;	popuntilequal("-=");	postfixstack.push("-=");										}
			// *
			else 	if(s == "*" && sp == "*"							)	{i+=1;	popuntilequal("**");	postfixstack.push("**");										}
			else 	if(s == "*" && sp != "*"							)	{		popuntilequal("*");		postfixstack.push("*");											}
			else 	if(s == "*" && sp == "="							)	{i+=1;	popuntilequal("*=");	postfixstack.push("*=");										}
			// /
			else 	if(s == "/" && sp == "/"							)	{i+=1;	popuntilequal("//");	postfixstack.push("//");										}
			else 	if(s == "/" && sp != "/"							)	{		popuntilequal("/");		postfixstack.push("/");											}
			else 	if(s == "/" && sp == "="							)	{i+=1;	popuntilequal("/=");	postfixstack.push("/=");										}
			else	if(s == " "											)	{continue;																						}
			else															{output.push_back(s);																			}
		}
		while(!postfixstack.empty() && !isbracket(postfixstack.top())){
			output.push_back(postfixstack.top());
			postfixstack.pop();
		}		

		for(auto& i : output){
			cout<<i<<" ";
		}
		cout<<endl;
		output.clear();
	}
}