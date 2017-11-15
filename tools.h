


vector<string> split_string(string str, string delimitor){
	char s,d;
	bool Match;
	int indexdiff;
	vector<string> result;
	string substr = "";
	for (int i = 0; i < str.size(); ++i)
	{
		indexdiff = 0;
		Match = true;
		for (int j = 0; j < delimitor.size(); ++i)
		{
			if(indexdiff+i < str.size()){
				s = str[i + indexdiff];
				cout<<s<<endl;
				d = delimitor[j];
				if(d != s){
					Match = false;
					break;
				}
				indexdiff++;
			}else{
				Match = false;
				break;
			}
		}
		substr += str.substr(i,1);
		if(Match){
			result.push_back(substr);
			substr = "";
		}
	}
	return result;
}