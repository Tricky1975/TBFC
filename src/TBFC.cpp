// TBCF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool qreplace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


void Translate(string file) {	
	cout << file << "\t";
	ifstream src(file);
	if (src.is_open()) {
		string tarfile(file); qreplace(tarfile, ".bf", ".c"); // cout << tarfile;
		ofstream tar(tarfile);		
		int instructions(0);	
		if (!tar.is_open()) {
			cout << "ERROR: Can't write target " << tarfile << "\n";
			src.close();
			return;
		}
		tar << "#include <stdio.h>\n int main(void) {\n\tunsigned char ptr=0;\n\tunsigned char val[256];\n\n\tfor(int i=0;i<256;++i) val[i]=0;\n";
		while (!src.eof()) {
			char c;
			src.read(&c, 1);
			switch (c) {
			case '<': tar << "\t--ptr;\n"; instructions++; break;
			case '>': tar << "\t++ptr;\n"; instructions++; break;
			case '+': tar << "\t++val[ptr];\n"; instructions++; break;
			case '-': tar << "\t--val[ptr];\n"; instructions++; break;
			case '.': tar << "\tputchar(val[ptr]);\n"; instructions++; break;
			case ',': tar << "\tval[ptr]=getchar();\n"; instructions++; break;
			case '[': tar << "\twhile(val[ptr]) {\n"; instructions++; break;
			case ']': tar << "\t}\n"; instructions++; break;
			}
		}
		tar << "\n\treturn 0;\n}\n";
		cout << instructions<<" instructions \n";
		src.close();
	} else {
		cout << "ERROR: Couldn't open file!\n";
	}
	
	//cout << "\n";
}

int main(int acount,char** args) {
    cout << "TBFC - (c) Jeroen P. Broks - Released under the terms of the GPL3\n\n";
	if (acount == 1) {
		cout << "Usage " << args[0] << " [switches] <files>\n";
		return 0;
	}
	for (int i = 1; i < acount; ++i) {
		Translate(args[i]);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
