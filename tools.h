#include <sstream>


vector<string> split(string str, string token){
	vector<string>result;
	while(str.size()){
		int index = str.find(token);
		if(index!=string::npos){
			result.push_back(str.substr(0,index));
			str = str.substr(index+token.size());
			if(str.size()==0)result.push_back(str);
		}else{
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

template <typename T>
string join(const T& v, const string& delim) {
	ostringstream s;
	for (const auto& i : v) {
		if (&i != &v[0]) {
			s << delim;
		}
		s << i;
	}
	return s.str();
}

