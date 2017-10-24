



class codeblock{
	vector<unsigned char> code;
	vector<variable *> constants;

	codeblock(vector<unsigned char> code, vector<variable *> constants){
		this->constants = constants;
		this->code = code;
	}

};