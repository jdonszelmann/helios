
class codeblock{
	public:
		vector<unsigned char> code;
		map<int,variable *> constants;
		vector<codeblock *> children;
		codeblock * parent;

		codeblock(vector<unsigned char> code, map<int, variable *> constants){
			this->constants = constants;
			this->code = code;
		}
		codeblock(){}

		void add_instruction(unsigned char instruction){
			this->code.push_back(instruction);		
		}

		void add_constant(int item, variable * var){
			this->constants[item] = var;
		}

		codeblock * add_codeblock(){
			codeblock * c = new codeblock();
			this->children.push_back(c);
			return c;
		}
};