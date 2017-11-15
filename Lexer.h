
namespace {
	void __newvar__(){

	}
	void __newstring__(){

	}
}

namespace {
	class _LANGSPEC{
		public:
			vector<_LANGSPEC> children;
			_LANGSPEC * parent;
			string letter;
			_LANGSPEC(string letter, _LANGSPEC * parent){
				this->letter = letter;
				this->parent = parent;
			}

			_LANGSPEC(){

			}

			void print(){
				cout<<this->letter<<endl;
				for(auto& i:this->children){
					i.print();
				}
			}
	};

	class LANGSPEC{
		public:
			vector<LANGSPEC> children;
			void (* function) (void);
			string type = "";
			string name = "";

			LANGSPEC(string type, string name, vector<LANGSPEC> children){
				// this->next = v(children, children + sizeof children / sizeof children[0]);
				this->children = children;
				this->type = type;
				this->name = name;
			}
			LANGSPEC(string type, string name, void (*f) (void)){
				this->function = f;
				this->type = type;
				this->name = name;
			}

			LANGSPEC(vector<LANGSPEC>){
				this->children = children;
			}


			void print(){
				cout<<this->name<<endl;
				for(auto& i:this->children){
					i.print();
				}
			}
	};
}
_LANGSPEC * LANGUAGE_SPECIFICATION = NULL;
_LANGSPEC * LANGUAGE_SPECIFICATION_CURRENT = NULL;
	
namespace lexer{
	void decode(string line){
		cout<<"hey"<<endl;
		LANGUAGE_SPECIFICATION->print();
		cout<<"hey"<<endl;

	}


	void recursive_gen(LANGSPEC spec){
		for(auto& i:spec.children){

			if(i.name != "" && i.type != ""){
				if(i.type == "ANY"){
					cout<<"any"<<endl;
					for (int j = 0; j < i.name.size(); ++j)
					{
						string s = i.name.substr(j,1);
						_LANGSPEC * sp = new _LANGSPEC(s,LANGUAGE_SPECIFICATION_CURRENT);
						LANGUAGE_SPECIFICATION_CURRENT = sp;
						recursive_gen(i);
					}
				}
			}
			if(i.type == ""){
				recursive_gen(i);
			}
		}
	}

	void GEN_LANGSPEC(LANGSPEC spec){
		cout<<"generating langspec"<<endl;	
		LANGUAGE_SPECIFICATION = new _LANGSPEC();
		LANGUAGE_SPECIFICATION_CURRENT = LANGUAGE_SPECIFICATION;
		recursive_gen(spec);
	}
}


LANGSPEC variable = LANGSPEC("ANY","$_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",{
	LANGSPEC("NOT"," \n\t\r",&__newvar__)
});

LANGSPEC str = LANGSPEC("EXACT","\"",{
	LANGSPEC("NOT","\"",&__newstring__)
});

LANGSPEC spec = LANGSPEC({
	variable,
	str,
});	














