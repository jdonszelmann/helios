class filereader{
	public:
		string filename;
		ifstream file;
		bool eof;

		filereader(string name){
			this->filename = name;
			this->file.open (this->filename);
			this->eof = this->file.eof();
		}

		string next(){
			if(this->file.eof()){
				this->file.close();
				this->eof = true;
			}

			if(this->file.is_open()){
				string line;
				getline (this->file,line);
				return line;
			}
			return "";
		}
};