#include "folder.h"
#include "dirent.h"
#include <errno.h>
#include <direct.h>
#include <io.h>

string folder::decimal_to_binary(int in)
{
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(8 - temp.size(), '0');													//append '0' ahead to let the result become fixed length of 8
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

inline void folder::build_tree(string& path, char a_code)
{//build a new branch according to the inpue code and ignore the already existed branches
	node_ptr current = root;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '0')
		{
			if (current->left == NULL)
				current->left = new huffman_node;
			current = current->left;
		}
		else if (path[i] == '1')
		{
			if (current->right == NULL)
				current->right = new huffman_node;
			current = current->right;
		}
	}
	current->id = a_code;																	//attach id to the leaf
}
int folder::find_directory(char *dirname)
{
	DIR *dir;
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	char *src;
	char *end = &buffer[PATH_MAX];
	int ok;

	/* Copy directory name to buffer */
	src = dirname;
	while (p < end  &&  *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';

	/* Open directory stream */
	dir = opendir(dirname);
	if (dir != NULL) {
		struct dirent *ent;

		/* Print all files and directories within the directory */
		while ((ent = readdir(dir)) != NULL) {
			char *q = p;
			char c;

			/* Get final character of directory name */
			if (buffer < q) {
				c = q[-1];
			}
			else {
				c = ':';
			}

			/* Append directory separator if not already there */
			if (c != ':'  &&  c != '/'  &&  c != '\\') {
				*q++ = '\\';
			}

			/* Append file name */
			src = ent->d_name;
			while (q < end  &&  *src != '\0') {
				*q++ = *src++;
			}
			*q = '\0';

			/* Decide what to do with the directory entry */
			switch (ent->d_type) {
			case DT_LNK:
			case DT_REG:
			{
						   /* Output file name with directory */
						   //   printf("%s\n", buffer);
						   char* temp = new char[PATH_MAX + 2];
						   strcpy(temp, buffer);
						   _list_link.push_back(temp);
						   break;
			}

			case DT_DIR:
				/* Scan sub-directory recursively */
				if (strcmp(ent->d_name, ".") != 0
					&& strcmp(ent->d_name, "..") != 0) {
					find_directory(buffer);
				}
				break;

			default:
				/* Ignore device entries */
				/*NOP*/;
			}
		}
		closedir(dir);
		ok = 1;
	}
	else {
		/* Could not open directory */
		fprintf(stderr, "Cannot open %s (%s)\n", dirname, strerror(errno));
		ok = 0;
	}
	return ok;
}
void folder::encode()
{
	cout << "Compressing..." << endl;
	char* name = new char[PATH_MAX];
	strcpy(name, in_file_name.c_str());
	find_directory(name);
	const char* out = out_file_name.c_str();

	for (int i = 0; i < _list_link.size(); i++)
	{
		huffman_folder h(_list_link[i], out);
		h.encode(in_file_name.c_str());

		delete[] _list_link[i];
	}
	cout << "Finish!" << endl;
}

void folder::make_directory(const char* link)
{
	string a("mkdir ");
	a = a + out_file_name + '\\' + link;
	this->out_link = out_file_name + '\\' + link;

	int pos;
	for (int i = a.size() - 1; i >= 0; i--)
	{
		if (a[i] == '\\')
		{
			pos = i;
			break;
		}
	}
	a.erase(pos, -1);
	cout << "make direc: " << a << endl;
	system(a.c_str());
}

void folder::decode()
{
	cout << "Extracting..." << endl;
	//vector<char*> out = { "C:\\Users\\home\\Documents\\Test_folder\\test1.txt", "C:\\Users\\home\\Documents\\Test_folder\\test2.txt", "C:\\Users\\home\\Documents\\Test_folder\\test3.txt", "C:\\Users\\home\\Documents\\Test_folder\\test4.txt"};
	in_file.open(in_file_name, ios::in|ios::binary);
	in_file.seekg(0, ios::end);
	int leng_file = in_file.tellg();
	while (byte_dadoc<leng_file)
	{
		//dieu kien dung
		//tao thu muc
		in_file.seekg(byte_dadoc, ios::beg);
		in_file.read(reinterpret_cast<char*>(&tong_byte), 4);
		in_file.read(reinterpret_cast<char*>(&leng_link), 1);
		link = new char[_MAX_PATH];
		in_file.read(link, leng_link);
		link[leng_link] = '\0';
		make_directory(link);


		//giai nen tap tin
		//tao lai cay huffman tu thu muc nen
		//recreate_huffman_tree
		unsigned char size;																			//unsigned char to get number of node of humman tree
		in_file.read(reinterpret_cast<char*>(&size), 1);
		root = new huffman_node;
		for (int i = 0; i < size; i++)
		{
			char a_code;
			unsigned char h_code_c[16];																//16 unsigned char to obtain the binary code
			in_file.read(&a_code, 1);
			in_file.read(reinterpret_cast<char*>(h_code_c), 16);
			string h_code_s = "";
			for (int i = 0; i < 16; i++)
			{//obtain the oringinal 128-bit binary string
				h_code_s += decimal_to_binary(h_code_c[i]);
			}
			int j = 0;
			while (h_code_s[j] == '0')
			{//delete the added '000бнбн1' to get the real huffman code
				j++;
			}
			h_code_s = h_code_s.substr(j + 1);
			build_tree(h_code_s, a_code);
		}

		//giai nen thu muc
		//this->decoding_save(out[i]);
		//cout << "---out link----" << out_link << endl;
		out_file.open(out_link, ios::out);
	//	in_file.seekg(byte_dadoc + 4 + 1 + leng_link, ios::beg);                                        //get the size of huffman tree
		//cout << "Size of huffman: " << (int)size << endl;
		in_file.seekg(byte_dadoc + tong_byte - 1, ios::beg);														//jump to the last one byte to get the number of '0' append to the string at last
		char count0;
		in_file.read(&count0, 1);
		//cout << "Last byte: " << (int)count0 << endl;
		in_file.seekg(byte_dadoc + 4 + 1 + leng_link + 1 + 17 * size, ios::beg);													//jump to the position where text starts


		vector<unsigned char> text;
		unsigned char textseg;
		in_file.read(reinterpret_cast<char*>(&textseg), 1);
		//cout << "Byte:  " << byte_dadoc + tong_byte << endl;
		while (in_file.tellg() <= (byte_dadoc + tong_byte) && (int)in_file.tellg() != -1)
		{//get the text byte by byte using unsigned char
			text.push_back(textseg);
			in_file.read(reinterpret_cast<char*>(&textseg), 1);
		//	cout << "ftell: " << in_file.tellg() << endl;
		}

		node_ptr current = root;
		string path;
		for (int i = 0; i < text.size() - 1; i++)
		{//translate the huffman code
			path = decimal_to_binary(text[i]);
			if (i == text.size() - 2)
				path = path.substr(0, 8 - count0);
			for (int j = 0; j < path.size(); j++)
			{
				if (path[j] == '0')
					current = current->left;
				else
					current = current->right;
				if (current->left == NULL && current->right == NULL)
				{
					out_file.put(current->id);
					current = root;
				}
			}
		}
		out_file.close();
		text.clear();

		byte_dadoc += tong_byte;
		cout << "Byte da doc: " << byte_dadoc << endl;
	}
	in_file.close();
	cout << "Finish!" << endl;
}
folder::folder(string in, string out)
{
	in_file_name = in;
	out_file_name = out;
	byte_dadoc = 0;
}
folder::~folder()
{
	_list_link.clear();
}