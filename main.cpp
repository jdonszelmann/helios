#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "tools.h"
#include "filereader.h"
#include "lexer.h"


int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "no input file provided" <<endl;
        return 0;
    }
	filereader * reader = new filereader(argv[1]);
	while(!reader->eof){
		for(auto& i:split(reader->next(),";")){
			// cout<<i<<endl;
			lexer::decode(i);
		}
	}
}