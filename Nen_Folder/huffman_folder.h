#ifndef _huff_folder
#define _huff_folder

#include "huffman.h"

class huffman_folder :public huffman
{
public:
	void coding_save(const char*);
	void encode(const char* link);
public:
	huffman_folder(string, string);
	~huffman_folder();
};


#endif