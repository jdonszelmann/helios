#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "tools.h"
#include "filereader.h"


int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "no input file provided" <<endl;
        return 0;
    }
	filereader * reader = new filereader(argv[1]);
	while(!reader->eof){
		for(auto& i:split_string(reader->next(),";")){
			cout<<i<<endl;
		}
	}
}