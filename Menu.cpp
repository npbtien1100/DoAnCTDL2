//
//  Menu.cpp
//  Matrix1
//
//  Created by Admin on 11/1/19.
//  Copyright � 2019 tvt3. All rights reserved.
//

#include "Menu.h"
using namespace std;
void getLink(string& linkNen,string& linkLuu)
{
    cout<<" Nhap vao duong dan toi file can nen."<<endl;
	fflush(stdin);
    getline(cin,linkNen);
    cout<<" Nhap duong dan toi folder luu file da nen."<<endl;
	fflush(stdin);
    getline(cin,linkLuu);
}
void GetLink2(string& linkgiainen, string& linkluu)
{
	cout << " Nhap vao duong dan toi file can giai nen." << endl;
	fflush(stdin);
	getline(cin, linkgiainen);
	cout << " Nhap duong dan toi file luu." << endl;
	fflush(stdin);
	getline(cin, linkluu);
}
int ChooseMenu()
{
    int n = 0;
    cout << "Lua chon cua ban: ";
    cin >> n;
    if (n >= 0 && n < 6)
        return n;
    else return ChooseMenu();
}
void Menu()
{
    //    HANDLE hConsoleColor;
    //    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    int choose = 1;
    while (choose)
    {
        string linkNen,linkLuu;
        cout << "\n\n\n\n " << endl;
        cout <<"\t    ====================WELCOM====================\n\n" << endl;
        cout << "\t     Button [1].Nen file chuoi. ( .txt, .cpp, .h) " << endl;
		cout << "\t     Button [2].Giai nen file chuoi( .txt, .cpp, .h)" << endl;
        cout << "\t     Button [3].Nen folder chua cac file chuoi         " << endl;
		cout << "\t     Button [4].Giai nen folder chua cac file chuoi         " << endl;
        cout << "\t     Button [5].Nen anh dinh dang bitmap ve jpge          " << endl;
        cout << "\t   _______________________________________________" << endl;
        cout << endl;
        
        choose = ChooseMenu();
        switch (choose)
        {
            case 0:   exit;
                break;
            case 1:
            {
                system("cls");
                getLink(linkNen,linkLuu);
                huffman file(linkNen,linkLuu);
				file.encode();
                break;
            }
			case 2:
			{
					  system("cls");
					  GetLink2(linkNen, linkLuu);
					  huffman file(linkNen, linkLuu);
					  file.decode();
					  break;
			}
            case 3:
            {
                system("cls");
                getLink(linkNen, linkLuu);
                folder fd(linkNen,linkLuu);
				fd.encode();
                break;
            }
			case 4:
			{
					  system("cls");
					  GetLink2(linkNen, linkLuu);
					  folder fd(linkNen, linkLuu);
					  fd.decode();
					  break;
			}
            case 5:
            {
                system("cls");
				cout << "Nhap link file anh can nen: " << endl;
				fflush(stdin);
				getline(cin, linkNen);
                const char *inputFileName = linkNen.c_str();
                
                JpegEncoder encoder;
                if(!encoder.readFromBMP(inputFileName))
                {
                    cout<<" khong mo duoc file"<<endl;
                }
                
                if(!encoder.encodeToJPG("out.jpg", 50))
                {
                    cout<<" Khong luu duoc file"<<endl;
                }
                cout<<" Nen thanh cong!"<<endl;
                break;
            }
            default:
            { choose = 0;
                break;
            }
        }
    }
}
