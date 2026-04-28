#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Usage: ./ex04 file s1 s2" << std::endl;
		return 1;
	}
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	std::ifstream ifs(filename.c_str());
	if (!ifs) {
		std::cerr << "Error: could not open file" << std::endl;
		return 1;
	}

	std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	std::string out;
	size_t pos = 0;
	size_t found;
	while ((found = content.find(s1, pos)) != std::string::npos) {
		out.append(content, pos, found - pos);
		out += s2;
		pos = found + s1.length();
	}
	out.append(content, pos, std::string::npos);

	std::ofstream ofs((filename + ".replace").c_str());
	if (!ofs) {
		std::cerr << "Error: could not create output file" << std::endl;
		return 1;
	}
	ofs << out;
	ofs.close();

	return 0;
}
