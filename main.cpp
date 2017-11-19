#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iterator>
#include <stack>
#include <stdlib.h>

using namespace std;

#include "include.h"
#include "tools.h"
#include "filereader.h"
#include "lexer.h"
#include "compiler.h"


int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "no input file provided" <<endl;
        return 0;
    }
	filereader * reader = new filereader(argv[1]);
	while(!reader->eof){
		for(auto& i:split(reader->next(),";")){
			lexer::decode(i);
		}
	}
	vector<instruction *> code = lexer::code();
	compiler::compile(code);
}