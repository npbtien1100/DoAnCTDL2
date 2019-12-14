#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirent.h"
#include <errno.h>
#include <locale.h>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "huffman.h"
#include <fcntl.h>
#include <io.h>
#include <string>
#include <iostream>
#include "folder.h"
#include "Menu.h"
using namespace std;
//int find_directory(char *dirname, vector<char*>&a);

/* Find files and subdirectories recursively */
//int find_directory(char *dirname, vector<char*>&a)
//{
//	DIR *dir;
//	char buffer[PATH_MAX + 2];
//	char *p = buffer;
//	char *src;
//	char *end = &buffer[PATH_MAX];
//	int ok;
//
//	/* Copy directory name to buffer */
//	src = dirname;
//	while (p < end  &&  *src != '\0') {
//		*p++ = *src++;
//	}
//	*p = '\0';
//
//	/* Open directory stream */
//	dir = opendir(dirname);
//	if (dir != NULL) {
//		struct dirent *ent;
//
//		/* Print all files and directories within the directory */
//		while ((ent = readdir(dir)) != NULL) {
//			char *q = p;
//			char c;
//
//			/* Get final character of directory name */
//			if (buffer < q) {
//				c = q[-1];
//			}
//			else {
//				c = ':';
//			}
//
//			/* Append directory separator if not already there */
//			if (c != ':'  &&  c != '/'  &&  c != '\\') {
//				*q++ = '\\';
//			}
//
//			/* Append file name */
//			src = ent->d_name;
//			while (q < end  &&  *src != '\0') {
//				*q++ = *src++;
//			}
//			*q = '\0';
//
//			/* Decide what to do with the directory entry */
//			switch (ent->d_type) {
//			case DT_LNK:
//			case DT_REG:
//			{
//						   /* Output file name with directory */
//						//   printf("%s\n", buffer);
//						   char* temp = new char[PATH_MAX + 2];
//						   strcpy(temp, buffer);
//						   a.push_back(temp);
//						   break;
//			}
//
//			case DT_DIR:
//				/* Scan sub-directory recursively */
//				if (strcmp(ent->d_name, ".") != 0
//					&& strcmp(ent->d_name, "..") != 0) {
//					find_directory(buffer, a);
//				}
//				break;
//
//			default:
//				/* Ignore device entries */
//				/*NOP*/;
//			}
//
//		}
//
//		closedir(dir);
//		ok = 1;
//
//	}
//	else {
//		/* Could not open directory */
//		fprintf(stderr, "Cannot open %s (%s)\n", dirname, strerror(errno));
//		ok = 0;
//	}
//
//	return ok;
//}


int main(int argc, char *argv[])
{
	//char* s = "C:\\Users\\home\\Documents\\Create\\a.txt";

	/*int check=mkdir("C:/Users/home/Documents/Create");
	if (check == 0)
	printf("Khong thanh cong\n");*/
	/*char* a = "mkdir C:\\Users\\home\\Documents\\Create\\b\\c";
	int b = system(a);*/
	
	/*vector<char*> a;
	find_directory("C:\\Users\\home\\Documents\\18120592_1712781\\Test1", a);
	char* out = "C:\\Users\\home\\Documents\\testfolder.huff";
	cout << "--------------------" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		huffman h(a[i], out);
		h.encode(a[i]);

		printf("%s\n", a[i]);
		delete[] a[i];
	}*/

	/*int tong_byte;
	char leng_link;
	char* link = new char[MAX_PATH];

	fstream file("C:\\Users\\home\\Documents\\testfolder.huff", ios::in, ios::binary);
	file.read(reinterpret_cast<char*>(&tong_byte), 4);
	file.read(&leng_link, 1);
	file.read(link, leng_link);
	link[leng_link] = '\0';
	file.close();

	cout << "Tong byte: " << tong_byte << endl;
	cout << "Leng: " << (int)leng_link << endl;
	cout << "Link: " << link << endl;*/

	//int tong_byte;
	//fstream file("C:\\Users\\home\\Documents\\testfolder.huff", ios::in, ios::binary);
	//file >> tong_byte;
	//tong_byte += 1;
	//vector<unsigned char> text;
	//unsigned char textseg;
	//file.read(reinterpret_cast<char*>(&textseg), 1);
	//while (file.tellg() < tong_byte)
	//{//get the text byte by byte using unsigned char
	//	text.push_back(textseg);
	//	file.read(reinterpret_cast<char*>(&textseg), 1);
	//}
	//text.push_back(textseg);

	//for (int i = 0; i < text.size(); i++)
	//	cout << text[i];

	

	/*fstream file("C:\\Users\\home\\Documents\\testfolder.huff", ios::in|ios::binary);
	file.seekg(67, ios::beg);
	char c;
	file.read(&c, 1);
	cout << (int)c;
	file.close();*/

	/*folder fd("C:\\Users\\home\\Documents\\testfolder.huff", "C:\\Users\\home\\Documents\\Test_folder\\test1.txt");
	fd.decode();*/
	
	/*folder fd("C:\\Users\\home\\Documents\\project.huff", "C:\\Users\\home\\Documents\\projecthuff");
	fd.decode();*/
	
	//huffman file("C:\\Users\\home\\Documents\\testexe.huff", "C:\\Users\\home\\Documents\\testexe.exe");
	//file.decode();
	Menu();
}
