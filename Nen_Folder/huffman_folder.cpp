#include "huffman_folder.h"
#include <iostream>
#include <string>
using namespace std;


void huffman_folder::coding_save(const char* link)
{
	in_file.open(in_file_name, ios::in);
	out_file.open(out_file_name, ios::app | ios::binary);
	string in = "", s = "";

	in += (char)pq.size();				//the first byte saves the size of the priority queue
	priority_queue<node_ptr, vector<node_ptr>, compare> temp(pq);
	while (!temp.empty())
	{//get all characters and their huffman codes for output
		node_ptr current = temp.top();
		in += current->id;
		s.assign(127 - current->code.size(), '0'); 											//set the codes with a fixed 128-bit string form[000бнбн1 + real code]
		s += '1';																			//'1' indicates the start of huffman code
		s.append(current->code);
		in += (char)binary_to_decimal(s.substr(0, 8));
		for (int i = 0; i < 15; i++)
		{//cut into 8-bit binary codes that can convert into saving char needed for binary file
			s = s.substr(8);
			in += (char)binary_to_decimal(s.substr(0, 8));
		}
		temp.pop();
	}
	s.clear();

	in_file.read(reinterpret_cast<char*>(&id), 1);
	while (!in_file.eof())
	{//get the huffman code
		s += node_array[id]->code;
		while (s.size() > 8)
		{//cut into 8-bit binary codes that can convert into saving char needed for binary file
			in += (char)binary_to_decimal(s.substr(0, 8));
			s = s.substr(8);
		}
		in_file.read(reinterpret_cast<char*>(&id), 1);
	}
	int count = 8 - s.size();
	if (s.size() < 8)
	{//append number of 'count' '0' to the last few codes to create the last byte of text
		s.append(count, '0');
	}
	in += (char)binary_to_decimal(s);															//save number of 'count' at last
	in += (char)count;

	string str_link(in_file_name);
	str_link = str_link.substr(strlen(link) + 1);

	int n = sizeof(n)+1 + str_link.size() + in.size();
	out_file.write(reinterpret_cast<char*>(&n), 4);

	char leng = str_link.size();
	out_file.write(&leng, 1);

	out_file.write(str_link.c_str(),leng);

	out_file.write(in.c_str(), in.size());
	in_file.close();
	out_file.close();
}
void huffman_folder::encode(const char* link)
{
	this->create_pq();
	this->create_huffman_tree();
	this->calculate_huffman_codes();
	this->coding_save(link);
	cout << endl;
}

huffman_folder::huffman_folder(string in, string out) :huffman(in,out)
{
}
huffman_folder::~huffman_folder()
{

}