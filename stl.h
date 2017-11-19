
variable * print(tuple_var * v){
	for(auto& i:v->vals){
		cout<<i->print()<<endl;
	}
	return new None_var();
}
variable * input(tuple_var * v){
	string inp;
	print(v);
	cin >> inp;
	return new string_var(inp);
}


namespace stl{
	vector<variable *> stl_functions = {
		new cpp_function_var(print),
		new cpp_function_var(input)
	};
	vector<string> stl_function_names = {
		"print",
		"input"
	};
}

