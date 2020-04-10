// Lic:
// Tricky's BrainFuck Compiler
// Translates Brainfuck code into C
// 
// 
// 
// (c) Jeroen P. Broks, 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// Please note that some references to data like pictures or audio, do not automatically
// fall under this licenses. Mostly this is noted in the respective files.
// 
// Version: 20.04.10
// EndLic

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