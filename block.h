
class codeblock: public variable{
	public:
		vector<unsigned char> code;
		map<int,variable *> constants;

		virtual string get_type(){
			return (string)"block";
		}

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
};