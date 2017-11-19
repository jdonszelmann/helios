
variable * print(tuple_var * v){
	for (int i = 0; i < v->vals.size(); ++i)
	{
		cout<<v->vals[i]->print()<<" ";
	}
	cout<<endl;
	return new None_var();
}
variable * input(tuple_var * v){
	string inp;
	for (int i = 0; i < v->vals.size(); ++i)
	{
		cout<<v->vals[i]->print()<<" ";
	}
	cin >> inp;
	return new string_var(inp);
}
variable * _int(tuple_var * v){
	if(v->vals[0]->get_type() == "int_var"){
		return new int_var(dynamic_cast<int_var *>(v->vals[0])->val);
	}	
	if(v->vals[0]->get_type() == "float_var"){
		return new int_var((int)dynamic_cast<float_var *>(v->vals[0])->val);
	}	
	if(v->vals[0]->get_type() == "string_var"){
		return new int_var(atoi(dynamic_cast<string_var *>(v->vals[0])->val.c_str()));
	}
}
variable * _float(tuple_var * v){
	if(v->vals[0]->get_type() == "int_var"){
		return new float_var((float)dynamic_cast<int_var *>(v->vals[0])->val);
	}	
	if(v->vals[0]->get_type() == "float_var"){
		return new float_var((float)dynamic_cast<float_var *>(v->vals[0])->val);
	}
	if(v->vals[0]->get_type() == "string_var"){
		return new float_var(atof(dynamic_cast<string_var *>(v->vals[0])->val.c_str()));
	}
}
variable * _str(tuple_var * v){
	if(v->vals[0]->get_type() == "int_var"){
		return new string_var(to_string(dynamic_cast<int_var *>(v->vals[0])->val));
	}	
	if(v->vals[0]->get_type() == "float_var"){
		return new string_var(to_string(dynamic_cast<float_var *>(v->vals[0])->val));
	}
	if(v->vals[0]->get_type() == "string_var"){
		return new string_var(dynamic_cast<string_var *>(v->vals[0])->val);
	}
}

variable * function(tuple_var * v){


	return new function_var();
}

namespace stl{
	vector<variable *> stl_functions = {
		new cpp_function_var(print),
		new cpp_function_var(input),
		new cpp_function_var(_int),
		new cpp_function_var(_float),
		new cpp_function_var(_str),
		new cpp_function_var(function),
	};
	vector<string> stl_function_names = {
		"print",
		"input",
		"int",
		"float",
		"str",
		"function",
	};
}

