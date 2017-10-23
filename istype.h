




bool isinteger(string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

static bool isFloatNumber(const string& string){
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
		}else if(!isdigit(*it) && (it+1 != string.end() || !decimalPoint)){
			break;
		}
		++it;
	}
	return string.size()>minSize && it == string.end();
 }


bool isvariablestart(string s){
	return s.find_first_not_of( "_$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ) == string::npos;
}