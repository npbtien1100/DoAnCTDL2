#ifndef _folder
#define _folder
#define _CRT_SECURE_NO_WARNINGS
#include "huffman.h"
#include "huffman_folder.h"

class folder{
private:
	fstream in_file, out_file;
	node_ptr root;
	string in_file_name, out_file_name, out_link;

	vector<char*> _list_link;
	int byte_dadoc;
	int tong_byte;
	unsigned char leng_link;
	char* link;
public:
	//encode 
	string decimal_to_binary(int in);
	inline void build_tree(string& path, char a_code);
	int find_directory(char *dirname);
public:
	void encode();
	void decode();
	void make_directory(const char*);
	folder(string, string);
	~folder();
};

#endif