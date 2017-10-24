
class variable{
	public:
		variable(){

		}

		virtual string print(){return (string)"object";}
		virtual string get_type			(				 )=0;	 //link to error mechanics
		virtual variable * _add			(variable * other) = 0;  //link to error mechanics
		virtual variable * _sub			(variable * other) = 0;  //link to error mechanics
		virtual variable * _mul			(variable * other) = 0;  //link to error mechanics
		virtual variable * _div			(variable * other) = 0;  //link to error mechanics
		virtual variable * _unary_neg	(				 ) = 0;  //link to error mechanics
		virtual variable * _pow			(variable * other) = 0;  //link to error mechanics
};

ostream & operator<<(ostream & os, stack<variable *> my_stack) //function header
{
	cout << "[";
    while(!my_stack.empty()) //body
    {	
        os << my_stack.top()->print()<< " ";
        my_stack.pop();
    }
    cout << "]"<<endl;
    return os; // end of function
}

class float_var: public variable{
	public:
		long double val;

		virtual string print(){return (string)"float object with value: " + to_string(val);}

		float_var(float val = 0){
			this->val = val;
		}

		virtual string get_type(){
			return (string)"float_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
};


class int_var: public variable{
	public:
		int val;

		int_var(int val = 0){
			this->val = val;
		}

		virtual string print(){return (string)"int object with value: " + to_string(val);}

		virtual string get_type(){
			return (string)"int_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
};



variable * float_var::_add(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val + (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val + dynamic_cast<float_var *>(other)->val);
	}
}
variable * float_var::_sub(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val - (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val - dynamic_cast<float_var *>(other)->val);
	}

}
variable * float_var::_mul(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val * (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val * dynamic_cast<float_var *>(other)->val);
	}
}
variable * float_var::_div(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var((float)this->val / (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val / dynamic_cast<float_var *>(other)->val);
	}
}	
variable * float_var::_unary_neg(){
	return new float_var(-this->val);
}

variable * float_var::_pow(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val * (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)pow(this->val, dynamic_cast<float_var *>(other)->val));
	}
}



variable * int_var::_add(variable * other){
	if(other->get_type() =="int_var"){
		return new int_var(this->val + dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val + dynamic_cast<float_var *>(other)->val);
	}
}
variable * int_var::_sub(variable * other){
	if(other->get_type() =="int_var"){
		return new int_var(this->val - dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val - dynamic_cast<float_var *>(other)->val);
	}
}
variable * int_var::_mul(variable * other){
		if(other->get_type() =="int_var"){
		return new int_var(this->val * dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val * dynamic_cast<float_var *>(other)->val);
	}
	
}
variable * int_var::_div(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var((float)this->val / (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val / dynamic_cast<float_var *>(other)->val);
	}
}

variable * int_var::_unary_neg(){
	return new int_var(-this->val);
}

variable * int_var::_pow(variable * other){			
	if(other->get_type() =="int_var"){
		return new int_var(pow(this->val,dynamic_cast<int_var *>(other)->val));
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)pow(this->val, dynamic_cast<float_var *>(other)->val));
	}
}