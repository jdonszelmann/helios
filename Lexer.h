
#include stack

stack<string> postfixstack;
vector<string> output;


namespace {
	void 
	popuntilequal(str op)
	{
		char index = getindex(op);
		while(!postfixstack.empty && getindex(postfixstack.top()) <= index){
			output.push_back(postfixstack.top())
			postfixstack.pop()
		}				
	}

	void
	popuntil(string limit){
		while(!postfixstack.empty() && postfixstack.top() != limit){
			output.push_back(postfixstack.top())
			postfixstack.pop()
		}
	}

	char 
	getindex(str op){
		switch(op.c_str()){
			// assignment
			case "=":{return 1000;}
			// +
			case "+":{return 30;}
			case "++":{return 20;}
			case "+=":{return 10;}
			// -
			case "-":{return 30;}
			case "--":{return 20;}
			case "-=":{return 10;}

			// *
			case "*":{return 31;}
			case "**":{return 22;}
			case "*=":{return 11;}

			// /
			case "/":{return 31;}
			case "//":{return 31;}
			case "/=":{return 11;}
		}
	}

	string
	nextnotspace(string str, int index, bool pos=true){
		string retval = "";
		string s
		if(index > str.size() || index < 0){
			return retval;
		}
		if(pos){
			for 
			(int i = index+1; i < str.size(); ++i)
			{
				s = string.substr(i,1);
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
				s = string.substr(i,1);
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
		(int i = 0; i < str.size; ++i)
		{
			s 	= str.substr	(		i,	1		);
			sp	= nextnotspace	(str,	i,	true	);
			sm	= nextnotspace	(str,	i,	false	);

			//brackets closing
					if(s == "]"					){		popuntil(	"["		);								}
			else 	if(s == "}"					){		popuntil(	"{"		);								}
			else 	if(s == ")"					){		popuntil(	"("		);								}
			else 	if(s == "\""				){		popuntil(	"\""	);								}
			//brackets opening
			else 	if(s == "["					){		postfixstack.push(s);								}
			else 	if(s == "{"					){		postfixstack.push(s);								}
			else 	if(s == "("					){		postfixstack.push(s);								}
			else 	if(s == "\""				){		postfixstack.push(s);								}
			//assignment
			else 	if(s == "=" 				){		popuntilequal("=");		postfixstack.push("=");		}
			// +
			else 	if(s == "+" && sp == "+"	){i+=1; popuntilequal("++");	postfixstack.push("++");	}
			else 	if(s == "+" && sp != "+"	){		popuntilequal("+");		postfixstack.push("+");		}
			else 	if(s == "+" && sp == "="	){i+=1; popuntilequal("+=");	postfixstack.push("+=");	}
			// -
			else 	if(s == "-" && sp == "-"	){i+=1; popuntilequal("--");	postfixstack.push("--");	}
			else 	if(s == "-" && sp != "-"	){		popuntilequal("-");		postfixstack.push("-");		}
			else 	if(s == "-" && sp == "="	){i+=1; popuntilequal("-=");	postfixstack.push("-=");	}
			// *
			else 	if(s == "*" && sp == "*"	){i+=1; popuntilequal("**");	postfixstack.push("**");	}
			else 	if(s == "*" && sp != "*"	){		popuntilequal("*");		postfixstack.push("*");		}
			else 	if(s == "*" && sp == "="	){i+=1; popuntilequal("*=");	postfixstack.push("*=");	}
			// /
			else 	if(s == "/" && sp == "/"	){i+=1; popuntilequal("//");	postfixstack.push("//");	}
			else 	if(s == "/" && sp != "/"	){		popuntilequal("/");		postfixstack.push("/");		}
			else 	if(s == "/" && sp == "="	){i+=1; popuntilequal("/=");	postfixstack.push("/=");	}
			else{
				output.push_back(s);
			}
		}
	}
}