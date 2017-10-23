class filewriter{
	public:
		string filename;
		ofstream file;

		filewriter(string name){
			this->filename = name;
			this->file.open (this->filename);
		}

		void write(string line){
			// if(this->file.is_open()){
			// 	getline (this->file,line);
			// 	return line;
			// }
		}

		void close(){
			this->file.close();
			delete this;
		}

		~filewriter() {
			if(this->file.is_open()){
				this->file.close();
			}
		}
};