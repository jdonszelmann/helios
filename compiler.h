stack<vector<unsigned char>> vars;
map<string,int> varnames;
unsigned char value;
bool wasvar;

namespace {
	void
	decompile(codeblock * b){
		for (int i = 0; i < b->code.size(); ++i)
		{
			char s = b->code[i];
			switch(s){
				case(NOP):{
					cout<<"NOP"<<endl;
					break;
				}	     
				case(STP):{
					cout<<"STP"<<endl;
					break;
				}	     
				case(LV):{
					cout<<"LV"<<"  ";
					cout<<to_string(b->code[i+1]);
					cout<<to_string(b->code[i+2]);
					cout<<to_string(b->code[i+3]);
					cout<<to_string(b->code[i+4])<<endl;
					i += 4;
					break;
				}	      
				case(ADD):{
					cout<<"ADD"<<endl;
					break;
				}	     
				case(MUL):{
					cout<<"MUL"<<endl;
					break;
				}	     
				case(DIV):{
					cout<<"DIV"<<endl;
				}	     
				case(SUB):{
					cout<<"SUB"<<endl;
					break;
				}	     
				case(LC):{
					cout<<"LC"<<"  ";
					cout<<to_string(b->code[i+1]);
					cout<<to_string(b->code[i+2]);
					cout<<to_string(b->code[i+3]);
					cout<<to_string(b->code[i+4])<<endl;
					i += 4;
					break;
				}	      
				case(SV):{
					cout<<"SV"<<"  ";
					cout<<to_string(b->code[i+1]);
					cout<<to_string(b->code[i+2]);
					cout<<to_string(b->code[i+3]);
					cout<<to_string(b->code[i+4])<<endl;
					i += 4;
					break;
				}	      
				case(PT):{
					
					break;
				}	      
				case(UNARY_NEG):{
					cout<<"UNARY_NEG"<<endl;
					break;
				}       
				case(TRUEDIV):{
					cout<<"TRUEDIV"<<endl;
					break;
				}	 
				case(POW):{
					cout<<"POW"<<endl;
					break;
				}	     
				case(ES):{
					cout<<"ES"<<endl;
					break;
				}	      
				case(LST):{
					cout<<"LST"<<"  ";
					cout<<to_string(b->code[i+1]);
					cout<<to_string(b->code[i+2]);
					cout<<to_string(b->code[i+3]);
					cout<<to_string(b->code[i+4])<<endl;
					i += 4;
					break;
				}     
				case(CALL):{
					cout<<"CALL"<<endl;
					break;
				}	    
				case(TUP):{
					cout<<"TUP"<<"  ";
					cout<<to_string(b->code[i+1]);
					cout<<to_string(b->code[i+2]);
					cout<<to_string(b->code[i+3]);
					cout<<to_string(b->code[i+4])<<endl;
					i += 4;
					break;
				}     
			}
		}
	}

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
	void compile(vector<instruction *> code){
		int const_counter = 0;
		int block_counter = 0;
		int var_counter = stl::stl_functions.size();
		
		stack<int> blockpointer;
		stack<int> lastblock;
		map<int,codeblock *> codeblocks;
		codeblocks[block_counter] = new codeblock();
		blockpointer.push(block_counter);


		for (int i = 0; i < stl::stl_function_names.size(); ++i)
		{
			varnames[stl::stl_function_names[i]] = i;
		}


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
				//string
				if(sp->type == "STRING"){
					const_counter++;
					codeblocks[blockpointer.top()]->add_constant(const_counter, new string_var(s->value));
				}
				//float
				else if(s->value.find('.') != std::string::npos && is_float_number(s->value) && sp->type != "STRING"){
					const_counter++;
					codeblocks[blockpointer.top()]->add_constant(const_counter,new float_var(atof(s->value.c_str())));
				}
				//int
				else if(s->value.find('.') == std::string::npos && is_number(s->value) && sp->type != "STRING"){
					const_counter++;
					codeblocks[blockpointer.top()]->add_constant(const_counter,new int_var(atoi(s->value.c_str())));
				}			
				//variable
				else{
					wasvar = true;
					if(s->nextisequals){
						vector<unsigned char> var;
						var_counter++;
						value = var_counter;
						var.push_back((value >> 24) & 0xFF);
						var.push_back((value >> 16) & 0xFF);
						var.push_back((value >> 8) & 0xFF);
						var.push_back(value & 0xFF);
						vars.push(var);
						varnames[s->value] = var_counter;
					}else{	
						codeblocks[blockpointer.top()]->add_instruction(LV);
						value = varnames[s->value];
						codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
						codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
						codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
						codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);
					}
				}
				if(!wasvar){
					codeblocks[blockpointer.top()]->add_instruction(LC);
					value = const_counter;
					codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
					codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
					codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
					codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);					
				}


			}else if(s->type == "LIST"){
				codeblocks[blockpointer.top()]->add_instruction(LST);        
				value = s->argument;
				codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);				
			}else if(s->type == "TUPLE"){		
				codeblocks[blockpointer.top()]->add_instruction(TUP);        
				value = s->argument;
				codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);
			}else if(s->type == "CALL"){		
				codeblocks[blockpointer.top()]->add_instruction(TUP);        
				value = s->argument;
				codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction(CALL);        
			}
			//functions
			else if(s->type == "INDENT"){
				// codeblocks[blockpointer.top()]->add_instruction(ES);
				block_counter++;
				codeblocks[block_counter] = new codeblock();
				codeblocks[block_counter]->code.push_back(ES);
				blockpointer.push(block_counter);
			
			}else if(s->type == "DEDENT"){
				codeblock * temp  = codeblocks[blockpointer.top()];
				temp->code.push_back(LS);
				temp->code.push_back(RET);
				blockpointer.pop();
				const_counter++;
				codeblocks[blockpointer.top()]->add_constant(const_counter,temp);
				lastblock.push(const_counter);
			}else if(s->type == ":"){		
				codeblocks[blockpointer.top()]->code.back() = LC;
				value = lastblock.top();
				lastblock.pop();
				codeblocks[blockpointer.top()]->add_instruction((value >> 24) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 16) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction((value >> 8) & 0xFF);
				codeblocks[blockpointer.top()]->add_instruction(value & 0xFF);		
				codeblocks[blockpointer.top()]->add_instruction(CALL);		
			}
			//operators	
			else if(s->type == "="){
				codeblocks[blockpointer.top()]->add_instruction(SV);
				codeblocks[blockpointer.top()]->add_instruction(vars.top().at(0));
				codeblocks[blockpointer.top()]->add_instruction(vars.top().at(1));
				codeblocks[blockpointer.top()]->add_instruction(vars.top().at(2));
				codeblocks[blockpointer.top()]->add_instruction(vars.top().at(3));
				vars.pop();  
			}
			//+
			else if(s->type == "+"){
				codeblocks[blockpointer.top()]->add_instruction(ADD);
			}else if(s->type == "++"){
				
			}else if(s->type == "+="){
				
			}
			//-
			else if(s->type == "-"){
				codeblocks[blockpointer.top()]->add_instruction(SUB);
			}else if(s->type == "--"){
				
			}else if(s->type == "-="){
				
			}else if(s->type == "NEG"){
				codeblocks[blockpointer.top()]->add_instruction(UNARY_NEG);
			}
			//*
			else if(s->type == "*"){
				codeblocks[blockpointer.top()]->add_instruction(MUL);
			}else if(s->type == "**"){
				codeblocks[blockpointer.top()]->add_instruction(POW);
			}
			else if(s->type == "*="){
				
			}
			else if(s->type == "**="){
				
			}
			// /
			else if(s->type == "/"){
				codeblocks[blockpointer.top()]->add_instruction(DIV);
			}else if(s->type == "//"){
				codeblocks[blockpointer.top()]->add_instruction(TRUEDIV);	
			}else if(s->type == "/="){
				
			}			
			else if(s->type == "//="){
				
			}else{
				//
			}
		}
		codeblocks[blockpointer.top()]->add_instruction(STP);
		if(____DEBUG____){
			for(auto& i:codeblocks[blockpointer.top()]->code){
				cout<<to_string(i);
			}
			cout<<endl;

			for (auto& t : codeblocks[blockpointer.top()]->constants)
	            cout << t.first << " " << t.second->print() <<endl;
			decompile(codeblocks[blockpointer.top()]);
		}
		execute(codeblocks[blockpointer.top()]);
	}
}