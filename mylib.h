#ifndef _MYLIB_H
#define _MYLIB_H

#include <iostream>
#include<cmath>
#include<ctime>
#include "khoitao.h"
#include "mylib.h"
#include <conio.h>
#include<fstream>
#include <Windows.h>
#include<string>
using namespace std;

//Các hàm thao tac
int wherex()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}

void anConTro()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void hienConTro()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void ChangeColor(int k)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
}

void gotoxy(short x, short y) {
    static HANDLE h = NULL;
    if (!h)  h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void fullscreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void xoaManHinh() {
    system("cls");
    gotoxy(180, 45);
    cout << "________QUAN_LY_SAN_BAY________";
    ChangeColor(2);
    gotoxy(0, 0);
}
//ham chuong trinh

int SoSanhCMND(string a, string b)
{
	for (int i = 0; i < 10; i++)
	{
		if(a[i] > b[i])
		{
			return 1; // a > b
		}
		if (a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}

int SoSanhChuoiSo(string &a, string &b)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] > b[i])
		{
			return 1;
		}
		if (a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}


//-------------------------Ham go------------------------
char inHoa(char chuThuong) {
    chuThuong -= 32;
    return chuThuong;
}

void xuatMenu() {
    ChangeColor(2);
    cout << "\n                     *********QUAN LI SAN BAY************\n\n";
    cout << "			\n      1. CAP NHAT DANH SACH CAC MAY BAY		";
    cout << "			\n      2. CAP NHAT CHUYEN BAY					";
    cout << "			\n      3. VE MAY BAY								";
    cout << "			\n      4. IN DANH SACH CAC HANH KHACH THUOC CUNG MOT CHUYEN BAY		";
    cout << "			\n      5. IN DANH SACH CAC CHUYEN BAY KHOI HANH TRONG NGAY dd/mm/yyyy VA DEN NOI XXX MA CON VE	";
    cout << "			\n      6. IN DANH SACH CAC VE CON TRONG CUA 1 CHUYEN BAY		";
    cout << "			\n      7. THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA TUNG MAY BAY \n\n		";
    cout << "\n   -----------------------------------------------------------------------\n";

}

void xuatMuc_1() {
	ChangeColor(15);
	gotoxy(100,1);
    cout << "----------------------------------------------------------------------";
    gotoxy(120,2);
    cout << "|CAP NHAT DANH SACH MAY BAY|";
    gotoxy(100,3);
    cout << "----------------------------------------------------------------------";
    gotoxy(110,4);
    cout << "| 1.THEM |";
    gotoxy(130,4);
    cout << "| 2.XOA |";
    gotoxy(150,4);
    cout << "| 3.HIEU CHINH |";
    gotoxy(100,5);
    cout << "----------------------------------------------------------------------";
    gotoxy(100,6);
    cout << "|CHON THAO TAC MUON THUC HIEN:                                       |";
    gotoxy(100,7);
    cout << "----------------------------------------------------------------------";
    gotoxy(132,6);   
}

void xuatMuc_2() {
    ChangeColor(15);
	gotoxy(100,1);
    cout << "----------------------------------------------------------------------";
    gotoxy(120,2);
    cout << "|CAP NHAT DANH SACH CHUYEN BAY|";
    gotoxy(100,3);
    cout << "----------------------------------------------------------------------";
    gotoxy(110,4);
    cout << "| 1.THEM CHUYEN |";
    gotoxy(130,4);
    cout << "| 2.HIEU CHINH |";
    gotoxy(150,4);
    cout << "| 3.HUY CHUYEN |";
    gotoxy(100,5);
    cout << "----------------------------------------------------------------------";
    gotoxy(100,6);
    cout << "|CHON THAO TAC MUON THUC HIEN:                                       |";
    gotoxy(100,7);
    cout << "----------------------------------------------------------------------";
    gotoxy(132,6); 
}

void xuatMuc_3() {
	ChangeColor(6);
	gotoxy(75,10);
    cout << "+---------------------------------------------------------------+";
    gotoxy(75,11);
    cout << "|                        VE MAY BAY                             |";
    gotoxy(75,12);
    cout << "|---------------------------------------------------------------|";
    gotoxy(75,13);
    cout << "|                             |                                 |";
    gotoxy(75,14);
    cout << "|---------------------------------------------------------------|";
    gotoxy(84,13);
    cout << "  1. DAT VE";
    gotoxy(117,13);
    cout << "2. HUY VE  ";
    gotoxy(75,15);
    cout << "|                                                               |";
    gotoxy(95,15);
    cout << "CHON THAO TAC MUON THUC HIEN";
    gotoxy(75,16);    
    cout << "+---------------------------------------------------------------+";
    anConTro();
}

void xuatWarnOut() {
    gotoxy(80, 20);
    cout << "+---------------------------------------+\n";
    gotoxy(80, 21);
    cout << "| Ban co muon thoat khoi thao tac nhap? |\n";
    gotoxy(80, 22);
    cout << "+---------------------------------------+\n";
    gotoxy(80, 23);
    cout << "|      [Y] Dong Y / [N] Khong Dong Y    |\n";
    gotoxy(80, 24);
    cout << "+---------------------------------------+\n";
    anConTro();
}

bool luuDL(){
	while(true){
		gotoxy(80, 20);
	    cout << "+---------------------------------------+\n";
	    gotoxy(80, 21);
	    cout << "| Ban co muon luu du lieu vua nhap ?    |\n";
	    gotoxy(80, 22);
	    cout << "+---------------------------------------+\n";
	    gotoxy(80, 23);
	    cout << "|      [Y] Dong Y / [N] Khong Dong Y    |\n";
	    gotoxy(80, 24);
	    cout << "+---------------------------------------+\n";
	    anConTro();
	    
	    char luuDL=_getch();
	    
		if ((luuDL == 'Y') || (luuDL == 'y')) {          
	        gotoxy(80, 20);
	    	cout << "                                          \n";
	        gotoxy(80, 21);
	        cout << "                                          \n";
	        gotoxy(80, 22);
	        cout << "                                          \n";
	        gotoxy(80, 23);
	    	cout << "                                          \n";
	        gotoxy(80, 24);
	        cout << "                                          \n";
	        hienConTro();
	        return true;
	    }
	
    
		if((luuDL == 'N') || (luuDL == 'n')) {
	        gotoxy(80, 20);
	        cout << "                                          \n";
	        gotoxy(80, 21);
	        cout << "                                          \n";
	        gotoxy(80, 22);
	        cout << "                                          \n";
	        gotoxy(80, 23);
	        cout << "                                          \n";
	        gotoxy(80, 24);
	        cout << "                                          \n";
	        hienConTro();
	        return false;
	    }
	}
}

void xuatNhapMB() {

    cout << "Thong tin may bay:\n";
    cout << "+-------------------------------------------------+\n";
    cout << "| So hieu:         |                              |\n";
    cout << "| Loai may bay:    |                              |\n";
    cout << "| So day:          |                              |\n";
    cout << "| So hang:         |                              |\n";
    cout << "+-------------------------------------------------+\n";
}

void xuatNhapCB() {
    ChangeColor(15);
    gotoxy(100, 0);
    cout << "Thong tin chuyen bay";
    gotoxy(100, 1);
    cout << "+----------------------------------------------------+";
    gotoxy(100, 2);
    cout << "| Ma chuyen bay:   |                                 |";
    gotoxy(100, 3);
    cout << "|----------------------------------------------------|";
    gotoxy(100, 4);
    cout << "| Ngay khoi hanh:  |     |    | / |    | / |      |  |";
    gotoxy(127,4);
    ChangeColor(7);
    cout << "dd";
    gotoxy(136,4);
    cout << "mm";
    gotoxy(145,4);
    cout << "yyyy";
    ChangeColor(15);
    gotoxy(100, 5);
    cout << "|----------------------------------------------------|";
    gotoxy(100, 6);
    cout << "| Gio khoi hanh:   |          |    | : |    |        |";
    gotoxy(132,6);
    ChangeColor(7);
    cout << "hh";
    gotoxy(141,6);
	cout << "min";
	ChangeColor(15);
    gotoxy(100, 7);
    cout << "|----------------------------------------------------|";
    gotoxy(100, 8);
    cout << "| Dia diem den:    |                                 |";
    gotoxy(100, 9);
    cout << "|----------------------------------------------------|";
    gotoxy(100, 10);
    cout << "| So hieu may bay: |                                 |";
    gotoxy(100, 11);
    cout << "+----------------------------------------------------+";
}

void xuatNoiDen(){
	int x = 100, y = 27;
	int count = 0;
	string noiDen[21];
		noiDen[0] = "VUNG TAU";
		noiDen[1] = "BINH DINH";
		noiDen[2] = "CA MAU";
		noiDen[3] = "CAN THO";
		noiDen[4] = "DAK LAK";
		noiDen[5] = "DA NANG";
		noiDen[6] = "DIEN BIEN";
		noiDen[7] = "GIA LAI";
		noiDen[8] = "HAI PHONG";
		noiDen[9] = "HA NOI";
		noiDen[10] = "KHANH HOA";
		noiDen[11] = "RACH GIA";
		noiDen[12] = "PHU QUOC";
		noiDen[13] = "LAM DONG";
		noiDen[14] = "NGHE AN";
		noiDen[15] = "PHU YEN";
		noiDen[16] = "QUANG NGAI";
		noiDen[17] = "QUANG NAM";
		noiDen[18] = "HUE";
		noiDen[19] = "THANH HOA";
		noiDen[20] = "QUANG NINH";
	gotoxy(x,y);
	ChangeColor(6);
	cout << "+-----------------------------------------------------+";
	gotoxy(x,y+1);
	cout << "|                     Dia diem den                    |";
	gotoxy(x,y+2);
	cout << "|-----------------------------------------------------|";
	gotoxy(x,y + 3);
	cout << "|                                                     |";
	gotoxy(x,y + 4);
	cout << "|                                                     |";
	gotoxy(x,y + 5);
	cout << "|                                                     |";
	gotoxy(x,y + 6);
	cout << "|                                                     |";
	gotoxy(x,y + 7);
	cout << "|                                                     |";
	gotoxy(x,y + 8);
	cout << "|                                                     |";
	gotoxy(x,y + 9);
	cout << "|                                                     |";
	gotoxy(x, y + 10);
	cout << "+-----------------------------------------------------+";
	for(int i = 0; i < 21; i++){
		gotoxy(x + 3, y + 3 + count);
		cout << noiDen[i];
		count++;
		if(count == 7){
			x = wherex() + 9;
			count = 0;
		}
	}
}

void xoaNoiDen(){
	int x = 100, y = 27;
	gotoxy(x,y);
	cout << "                                                       ";
	gotoxy(x,y+1);
	cout << "                                                       ";
	gotoxy(x,y+2);
	cout << "                                                       ";
	gotoxy(x,y + 3);
	cout << "                                                       ";
	gotoxy(x,y + 4);
	cout << "                                                       ";
	gotoxy(x,y + 5);
	cout << "                                                       ";
	gotoxy(x,y + 6);
	cout << "                                                       ";
	gotoxy(x,y + 7);
	cout << "                                                       ";
	gotoxy(x,y + 8);
	cout << "                                                       ";
	gotoxy(x,y + 9);
	cout << "                                                       ";
	gotoxy(x, y + 10);
	cout << "                                                       ";
}

bool checkYearNhuan(int year)
{
    if (year % 4 == 0) {
		return true;
    }
    else
        return false;
}

void inThoiGian(){
		anConTro();
		gotoxy(180, 46);
		time_t hientai = time(0);
		tm *thoigian = localtime(&hientai);
		switch (thoigian->tm_wday)
		{
			case 1:
				{
					cout << "Monday";
					break;
				}
			case 2:
				{
					cout << "Tuesday";
					break;
				}
			case 3:
				{
					cout << "Wednesday";
					break;
				}
			case 4:
				{
					cout << "Thursday";
					break;
				}
			case 5:
				{
					cout << "Friday";
					break;
				}
			case 6:
				{
					cout << "Saturday";
					break;
				}
			case 0:
				{
					cout << "Sunday";
					break;
				}
		}
		gotoxy(189,46);
		cout <<  ", " << thoigian->tm_mday << "/" << thoigian->tm_mon + 1 << "/" << 1900 + thoigian->tm_year;
		gotoxy(wherex() - 11, wherey() + 2);
		cout << thoigian->tm_hour;
			cout << ":" ;
		if (thoigian->tm_min < 10)
		{
			cout << "0" << thoigian->tm_min;
		}
		else
		{
			cout << thoigian->tm_min;
		}		
}

bool checkTwoTime(int hh, int hhNhap, int min, int minNhap, int dd, int ddNhap){
	if(ddNhap - dd >= 2 || dd - ddNhap >= 2){
		return 0;
	}
	if(ddNhap == dd+1){
		if(((hhNhap+24)*60+minNhap) - (hh*60+min) < 12*60 ){
			return 1;
		}
		else return 0;
	}
	if(ddNhap + 1 == dd){
		if(((hh+24)*60 + min) - (hhNhap*60+minNhap) < 12*60){
			return 1;
		}
		else return 0;
	}
	if(dd == ddNhap){  
		if(hhNhap > hh){
			if((hhNhap*60+minNhap) - (hh*60+min) < 12*60){
				return 1;
			}
			else return 0;
		}
		else if(hh > hhNhap){
			if((hh*60+min) - (hhNhap*60+minNhap) < 12*60){
				return 1;
			}
			else return 0;
		}
		else return 1;
	}
}

bool checkThoiGianBay(int hh, int min, int dd, int mm, int yy){
	time_t hientai = time(0);
	tm *thoigian = localtime(&hientai);
	if(thoigian->tm_year + 1900 < yy){
		return true;
	}
	if(thoigian->tm_year + 1900 > yy){
		return false;
	}
	if(thoigian->tm_mon + 1 < mm){
		return true;
	}
	if(thoigian->tm_mon + 1 > mm){
		return false;
	}
	if(thoigian->tm_mday < dd){
		if(((hh+24)*60 + min) - (thoigian->tm_hour*60 + thoigian->tm_min) >= 1)
		return true;
	}
	if(thoigian->tm_mday > dd){
		return false;
	}
	if(thoigian->tm_mday == dd){ 
		if((hh*60 + min) - (thoigian->tm_hour *60 + thoigian->tm_min) >= 1)
			return true;
	}
	return false;
}

bool checkThoiGian(int hh, int min, int dd, int mm, int yy){
	time_t hientai = time(0);
	tm *thoigian = localtime(&hientai);
	if(thoigian->tm_year + 1900 < yy){
		return true;
	}
	if(thoigian->tm_year + 1900 > yy){
		return false;
	}
	if(thoigian->tm_mon + 1 < mm){
		return true;
	}
	if(thoigian->tm_mon + 1 > mm){
		return false;
	}
	if(thoigian->tm_mday < dd){
		if(((hh+24)*60 + min) - (thoigian->tm_hour*60 + thoigian->tm_min) >= 180)
		return true;
	}
	if(thoigian->tm_mday > dd){
		return false;
	}
	if(thoigian->tm_mday == dd){ 
		if((hh*60 + min) - (thoigian->tm_hour *60 + thoigian->tm_min) >= 180)
			return true;
	}
	return false;
}

int suaTrangThai(int trangThai){
	ChangeColor(3);
	if(trangThai == 3){
		ChangeColor(12);
		gotoxy(155, 0);
		cout << "Chuyen Bay da Hoan Thanh!";
		Sleep(1000);
		gotoxy(155,0);
		cout << "                         ";
		return -1;
	}
	if(trangThai == 0){
		ChangeColor(12);
		gotoxy(155, 0);
		cout << "Chuyen Bay da bi Huy!";
		Sleep(800);
		gotoxy(155,0);
		cout << "                     ";
		return -1;
	}
	int luaChon = trangThai;
	while(true){
		gotoxy(135,0);
		cout << "           ";
		if(luaChon == 0){
			gotoxy(135,0);
			cout << "Huy Chuyen";
		}
		else if(luaChon == 1){
			
			gotoxy(135,0);
			cout << "Con ve";
		}
		else if(luaChon == 2){
			gotoxy(135,0);
			cout << "Het ve";
		}
		else{
			gotoxy(135,0);
			cout << "Hoan Thanh";
		}
		int check = _getch();
		if(check == 224){
			check = _getch();
			if(check == 77){
				luaChon++;
				if(luaChon == 4){
					luaChon = 0;
				}
			}
			if(check == 75){
				luaChon--;
				if(luaChon == -1){
					luaChon = 3;
				}
			}
		}
		if(check == 13){
			ChangeColor(15);
			gotoxy(135,0);
			cout << "           ";
			if(luaChon == 0){
				gotoxy(135,0);
				cout << "Huy Chuyen";
				return luaChon;
			}
			else if(luaChon == 1){
				if(trangThai == 2){
					ChangeColor(12);
					gotoxy(155, 0);
					cout << "Chuyen Bay da Het Ve!";
					Sleep(800);
					gotoxy(155,0);
					cout << "                     ";
					return -2;
				}
				gotoxy(135,0);
				cout << "Con ve";
				return luaChon;
			}
			else if(luaChon == 2){
				gotoxy(135,0);
				cout << "Het ve";
				return luaChon;
			}
			else{
				gotoxy(135,0);
				cout << "Hoan Thanh";
				return luaChon;
			}
		}
		else if(check == 27){
			luaChon = -1;
			return luaChon;
		}		
	}

	return luaChon;	
}

int nhapSo() {
    int sum = 0;
    int key[3] = {};
    bool check = true;
    int i = 0, j = 0;
    while (check) {
        int x = 20, y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;
                }
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                break;
            }
            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        
            if (i > 2){
	            if (temp == 8) {
	                int toaDoX = wherex() - 1;
	                i--;
	                key[i] = NULL;
	                gotoxy(toaDoX, y);
	                cout << " ";
	                gotoxy(toaDoX, y);
	
	            }
	
	            else if (temp == 13) {
	                key[3] = '\0';
	
	                check = false;
	            }
	
	            else {
	                int toaDoX = wherex();
	                gotoxy(toaDoX + 55, y);
	                cout << "Qua Ky tu cho phep!";
	                Sleep(500);
	                gotoxy(toaDoX + 55, y);
	                cout << "                      ";
	                gotoxy(toaDoX, y);
	
	            }
        	}

		else{
	        if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
	        	int toaDoX = wherex();
	        	gotoxy(toaDoX + 55, y);
	            cout << "Vui long nhap du lieu dau vao!";
	            Sleep(800);
	            gotoxy(toaDoX + 55, y);
	            cout << "                              ";
	            gotoxy(x, y);
	        }
	
	        if (temp == 8 && key[0] != NULL)
	        {
	            int toaDoX = wherex() - 1;
	            i--;
	            key[i] = NULL;
	            gotoxy(toaDoX, y);
	            cout << " ";
	            gotoxy(toaDoX, y);
	        }
	
	        if (temp <= 57 && temp >= 48) {
	            key[i] = temp - 48;
	            if (key[0] == 0) {
	                key[0] = NULL;
	            }
	            else {
	                cout << key[i];
	                i++;
	            }
	        }
	
	        if (temp == 13 && key[0] != NULL) {
	            check = false;
	            break;
	        }
    	}
	}
    for (i; i > 0; i--)
    {
        sum = sum + key[j] * pow(10, i - 1);
        j++;
    }

    return sum;
}

int suaNhapSo(int a) {
	int a1, a2, a3, a4;
    int sum = -1;
    int key[4] = {};
    bool check = true;
    int i = 0, j = 0;
    if (a < 10) {
        key[i] = a;
        i++;
    }
    else if (a > 9 && a < 100){
        a1 = a / 10;
        a2 = a % 10;
        key[i] = a1;
        i++;
        key[i] = a2;
        i++;
    }//233
    else if(a >99 && a < 1000){
    	a1 = a / 100;
		a2 = (a - a1 * 100) / 10;
		a3 = a % 10;
		key[i] = a1;
		i++;
		key[i] = a2;
		i++;
		key[i] = a3;
		i++;
	}
	else if (a > 999 && a < 10000){
		//1234
		a1 = a / 1000;
		a2 = (a - a1 * 1000) / 100;
		a3 = (a % 100) / 10;
		a4 = a % 10;
		key[i] = a1;
		i++;
		key[i] = a2;
		i++;
		key[i] = a3;
		i++;
		key[i] = a4;
		i++;
	}

    while (check) {
        int x = wherex(), y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                return sum;
            }
            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x-i, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }
        
            if (i > 3){
	            if (temp == 8) {
	                int toaDoX = wherex() - 1;
	                i--;
	                key[i] = NULL;
	                gotoxy(toaDoX, y);
	                cout << " ";
	                gotoxy(toaDoX, y);
	
	            }
	
	            else if (temp == 13) {
	                key[4] = '\0';
	                check = false;
	            }
	
	            else {
	                int toaDoX = wherex();
	                gotoxy(x + 30, y);
	                cout << "Qua Ky tu cho phep!";
	                Sleep(500);
	                gotoxy(x + 30, y);
	                cout << "                      ";
	                gotoxy(toaDoX, y);
	
	            }
        	}

		else{
	        if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
	        	gotoxy(x+30,y);
	            cout << "Vui long nhap du lieu dau vao!";
	            Sleep(800);
	            gotoxy(x+30, y);
	            cout << "                              ";
	            gotoxy(x, y);
	        }
	
	        if (temp == 8 && key[0] != NULL)
	        {
	            int toaDoX = wherex() - 1;
	            i--;
	            key[i] = NULL;
	            gotoxy(toaDoX, y);
	            cout << " ";
	            gotoxy(toaDoX, y);
	        }
	
	        if (temp <= 57 && temp >= 48) {
	            key[i] = temp - 48;
	            if (key[0] == 0) {
	                key[0] = NULL;
	            }
	            else {
	                cout << key[i];
	                i++;
	            }
	        }
	
	        if (temp == 13 && key[0] != NULL) {
	            check = false;
	            break;
	        }
    	}
	}
	sum = 0;
    for (i; i > 0; i--)
    {
        sum = sum + key[j] * pow(10, i - 1);
        j++;
    }

    return sum;
}

int nhapSoCB(int a) {
	int a1, a2;
    int sum = -1;
    int key[2] = {};
    bool check = true;
    int i = 0, j = 0;
    if (a < 10) {
        key[i] = a;
		i++;
    }
    else if (a > 9 && a < 100){
        a1 = a / 10;
        a2 = a % 10;
        key[i] = a1;
        i++;
        key[i] = a2;
        i++;
    }

    while (check) {
        int x = wherex(), y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                return sum;
            }
            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x-i, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }
        
            if (i > 1){
	            if (temp == 8) {
	                int toaDoX = wherex() - 1;
	                i--;
	                key[i] = NULL;
	                gotoxy(toaDoX, y);
	                cout << " ";
	                gotoxy(toaDoX, y);
	
	            }
	
	            else if (temp == 13) {
	                key[2] = '\0';
	
	                check = false;
	            }
	
	            else {
	                int toaDoX = wherex();
	                gotoxy(155, y);
	                cout << "Qua Ky tu cho phep!";
	                Sleep(500);
	                gotoxy(155, y);
	                cout << "                      ";
	                gotoxy(toaDoX, y);
	
	            }
        	}

		else{
	        if ((temp == 13 && i == 0) || (temp == 8 && i == 0)){
	        	gotoxy(155,y);
	            cout << "Vui long nhap du lieu dau vao!";
	            Sleep(800);
	            gotoxy(155, y);
	            cout << "                              ";
	            gotoxy(x, y);
	        }
	
	        if (temp == 8 && i != 0)
	        {
	            int toaDoX = wherex() - 1;
	            i--;
	            key[i] = NULL;
	            gotoxy(toaDoX, y);
	            cout << " ";
	            gotoxy(toaDoX, y);
	        }
	
	        if (temp <= 57 && temp >= 48) {
	            key[i] = temp - 48;
	            cout << key[i];
	            i++;
	        }
	
	        if (temp == 13) {
	        	key[i] = '\0';
	            check = false;
	            break;
	        }
    	}
	}
	sum = 0;
    for (i; i > 0; i--)
    {
        sum = sum + key[j] * pow(10, i - 1);
        j++;
    }

    return sum;
}

string suaDLMB(string a) {
	char key[16] ={};
	char test[1] ={};
	int i = 0;
	for (i; i < a.length(); i++) {
    	key[i] = a[i]; // gán t?ng ký t? vào t?ng ph?n t? c?a m?ng char
	}
	a = "";
    bool check = true;
    while (check) {
        int x = wherex();
        int y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;

                }
                cout << "da thoat!";
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                return a;
                break;

            }

            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x - i , y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        if (i > 14)
        {
            if (temp == 8) {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);

            }

            else if (temp == 13) {
                key[15] = '\0';

                check = false;
            }

            else {
                int toaDoX = wherex();
                gotoxy(toaDoX + 55, y);
                cout << "Qua Ky tu cho phep!";
                Sleep(500);
                gotoxy(toaDoX+55, y);
                cout << "                      ";
                gotoxy(toaDoX, y);

            }
        }

        else {

            if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
                cout << "Vui long nhap du lieu dau vao!";
                Sleep(800);
                gotoxy(x, y);
                cout << "                              ";
                gotoxy(x, y);
            }

            if (temp >= 97 && temp <= 122) {
                key[i] = inHoa(temp);
                cout << key[i];
                i++;
            }

            if (temp == 8 && key[0] != NULL)
            {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);
            }

            if (temp >= 65 && temp <= 90) {
                key[i] = char(temp);
                cout << key[i];
                i++;
            }

            if (temp >= 48 && temp <= 57) {
                key[i] = temp;
                cout << key[i];
                i++;
            }

            if ((temp == 13) && (key[0] != NULL)) {
                key[i] = '\0';
                check = false;
            }
        }
    }
    a = strcpy(test,key);
    return a;
}

string nhapDatVe() {
    char key[3] = {};
    char key1[1] = {};
    bool check = true;
    int i = 0;
	string a = "";
    while (check) {
        int x = wherex();
        int y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;

                }
                cout << "da thoat!";
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                break;

            }

            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x - i, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        if (i > 2)
        {
            if (temp == 8) {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);

            }

            else if (temp == 13) {
                key[3] = '\0';
                check = false;
                break;
            }

            else {
                int toaDoX = wherex();
                gotoxy(toaDoX + 55, y);
                cout << "Qua Ky tu cho phep!";
                Sleep(500);
                gotoxy(toaDoX + 55, y);
                cout << "                      ";
                gotoxy(toaDoX, y);

            }
        }

        else {

            if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
                cout << "Vui long nhap du lieu dau vao!";
                Sleep(800);
                gotoxy(x, y);
                cout << "                              ";
                gotoxy(x, y);
            }

            if (temp >= 97 && temp <= 122) {
                key[i] = inHoa(temp);
                cout << key[i];
                i++;
            }

            if (temp == 8 && key[0] != NULL)
            {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);
            }

            if (temp >= 65 && temp <= 90) {
                key[i] = char(temp);
                cout << key[i];
                i++;
            }

            if (temp >= 48 && temp <= 57) {
                key[i] = temp;
                cout << key[i];
                i++;
            }

            if ((temp == 13) && (key[0] != NULL)) {
                key[i] = '\0';
                check = false;
            }
        }
    }
    a = strcpy(key1, key);
    return a;
}

string nhapCMND(string a) {
	char key[13] ={};
	char test[1] ={};
	int i = 0;
	for (i; i < a.length(); i++) {
    	key[i] = a[i]; // gán t?ng ký t? vào t?ng ph?n t? c?a m?ng char
    	cout << key[i];
	}
	a = "";
    bool check = true;
    while (check) {
        int x = wherex();
        int y = wherey();
        char temp = _getch();
		ChangeColor(15);
        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;

                }
                ChangeColor(12);
                cout << "da thoat!";
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                return a;
                break;

            }

            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x - i , y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        if (i > 12)
        {
            if (temp == 8) {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);

            }

            else if (temp == 13) {
                key[13] = '\0';

                check = false;
            }

            else {
            	ChangeColor(12);
                int toaDoX = wherex();
                gotoxy(toaDoX + 30, y);
                cout << "Qua Ky tu cho phep!";
                Sleep(500);
                gotoxy(toaDoX+30, y);
                cout << "                      ";
                gotoxy(toaDoX, y);

            }
        }

        else {

            if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
            	ChangeColor(12);
                cout << "Vui long nhap du lieu dau vao!";
                Sleep(800);
                gotoxy(x, y);
                cout << "                              ";
                gotoxy(x, y);
            }

            if (temp == 8 && key[0] != NULL)
            {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);
            }

            if (temp >= 48 && temp <= 57) {
                key[i] = temp;
                cout << key[i];
                i++;
            }

            if ((temp == 13) && (key[0] != NULL)) {
            	if(i >= 9){
            		key[i] = '\0';
                	check = false;
				}
                else{
                	ChangeColor(12);
                	int toaDoX = wherex();
	                gotoxy(toaDoX + 30, y);
	                cout << "CMND/CCCD khong dung";
	                Sleep(500);
	                gotoxy(toaDoX+30, y);
	                cout << "                      ";
	                gotoxy(toaDoX, y);
				}
            }
        }
    }
    a = strcpy(test,key);
    return a;
}

string nhapDLMB() {
    char key[16] = {};
    char key1[1] = {};
    bool check = true;
    int i = 0;
	string a = "";
    while (check) {
        int x = wherex();
        int y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;

                }
                cout << "da thoat!";
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                break;

            }

            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x - i, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        if (i > 15)
        {
            if (temp == 8) {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);

            }

            else if (temp == 13) {
                key[16] = '\0';
                check = false;
                break;
            }

            else {
                int toaDoX = wherex();
                gotoxy(toaDoX + 55, y);
                cout << "Qua Ky tu cho phep!";
                Sleep(500);
                gotoxy(toaDoX + 55, y);
                cout << "                      ";
                gotoxy(toaDoX, y);

            }
        }

        else {

            if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
                cout << "Vui long nhap du lieu dau vao!";
                Sleep(800);
                gotoxy(x, y);
                cout << "                              ";
                gotoxy(x, y);
            }

            if (temp >= 97 && temp <= 122) {
                key[i] = inHoa(temp);
                cout << key[i];
                i++;
            }

            if (temp == 8 && key[0] != NULL)
            {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);
            }

            if (temp >= 65 && temp <= 90) {
                key[i] = char(temp);
                cout << key[i];
                i++;
            }

            if (temp >= 48 && temp <= 57) {
                key[i] = temp;
                cout << key[i];
                i++;
            }

            if ((temp == 13) && (key[0] != NULL)) {
                key[i] = '\0';
                check = false;
            }
        }
    }
    a = strcpy(key1, key);
    return a;
}

string nhapTenKH() {
    char key[30] = {};
    char key1[1] = {};
    bool check = true;
    int i = 0;
	string a = "";
    while (check) {
        int x = wherex();
        int y = wherey();
        char temp = _getch();

        if (temp == 27) {
            xuatWarnOut();
            char tam = _getch();
            if ((tam == 'Y') || (tam == 'y')) {
                while (i >= 0) {
                    key[i] = NULL;
                    i--;

                }
                cout << "da thoat!";
                check = false;
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                break;

            }

            else {
                gotoxy(80, 20);
                cout << "                                          \n";
                gotoxy(80, 21);
                cout << "                                          \n";
                gotoxy(80, 22);
                cout << "                                          \n";
                gotoxy(80, 23);
                cout << "                                          \n";
                gotoxy(80, 24);
                cout << "                                          \n";
                hienConTro();
                gotoxy(x - i, y);
                for (int j = 0; j < i; j++)
                    cout << key[j];
            }
        }

        if (i > 29)
        {
            if (temp == 8) {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);

            }

            else if (temp == 13) {
                key[30] = '\0';
                check = false;
                break;
            }

            else {
                int toaDoX = wherex();
                gotoxy(toaDoX + 55, y);
                cout << "Qua Ky tu cho phep!";
                Sleep(500);
                gotoxy(toaDoX + 55, y);
                cout << "                      ";
                gotoxy(toaDoX, y);

            }
        }

        else {

            if ((temp == 13 && key[0] == NULL) || (temp == 8 && key[0] == NULL)) {
                cout << "Vui long nhap du lieu dau vao!";
                Sleep(800);
                gotoxy(x, y);
                cout << "                              ";
                gotoxy(x, y);
            }

			if(key[0] != NULL && temp == 32  && key[i-1] != '0'){
				key[i] = '0';
				cout << " ";
				i++;
			}

            if (temp >= 97 && temp <= 122) {
                key[i] = inHoa(temp);
                cout << key[i];
                i++;
            }

            if (temp == 8 && key[0] != NULL)
            {
                int toaDoX = wherex() - 1;
                i--;
                key[i] = NULL;
                gotoxy(toaDoX, y);
                cout << " ";
                gotoxy(toaDoX, y);
            }

            if (temp >= 65 && temp <= 90) {
                key[i] = char(temp);
                cout << key[i];
                i++;
            }

            if ((temp == 13) && (key[0] != NULL)) {
                key[i] = '\0';
                check = false;
            }
        }
    }
    a = strcpy(key1, key);
    return a;
}

int nhapLuaChon(int nhap, int soDau, int soCuoi) {
    int key;
    if (nhap <= 57 && nhap >= 48) {
        key = nhap - 48;
        if (key < soDau || key > soCuoi)
        {

            cout << " Lua chon cua ban khong ton tai!";
            Sleep(800);
            system("cls");
            return 0;
        }
    }
    else
    {
        system("cls");
        return 0;
    }
    return key;
}

string taoViTri(int soDay, int soHang){
	string a = "";
	int so1, so2;
	//12
	so1 = soHang /10;
	so2 = soHang %10;
	char key[3] = {};
	char temp[1] ={};
	if(soDay == 1){
		key[0] = 'A';
	}
	else if(soDay == 2){
		key[0] = 'B';
	}
	else if(soDay == 3){
		key[0] = 'C';
	}
	else if(soDay == 4){
		key[0] = 'D';
	}
	else if(soDay == 5){
		key[0] = 'E';
	}
	else{
		key[0] = 'F';
	}
	if(soHang <10){
		key[1] = '0';
		key[2] = so2 + 48;
	}
	else {
		key[1] = so1 + 48;
		key[2] = so2 + 48;
	}
	key[3] = '\0';
	a = strcpy(temp, key);
	return a; 
}

string num2str(int soCho, int soHang){
	string a = "";
	int so1;
	int soDay = soCho/soHang;

	char key[3] = {};
	char temp[1] ={};
	if(soDay == 0){
		key[0] = 'A';
	}
	else if(soDay == 1){
		key[0] = 'B';
	}
	else if(soDay == 2){
		key[0] = 'C';
	}
	else if(soDay == 3){
		key[0] = 'D';
	}
	else if(soDay == 4){
		key[0] = 'E';
	}
	else{
		key[0] = 'F';
	}
	
	so1 = soCho - soHang*(soDay);
	if(so1 < 10){
		key[1] = '0';
		key[2] = so1 + 48;
	}
	else {
		key[1]= so1/10 + 48;
		key[2] = so1%10 + 48;
	}
	key[3] = '\0';
	a = strcpy(temp, key);
	return a; 
}

int str2int(string maGhe, int soHang){
	int a;
	if(maGhe[0] == 'A'){
		a = 1;
	}
	else if(maGhe[0] == 'B'){
		a = 2;
	}
	else if(maGhe[0] == 'C'){
		a = 3;
	}
	else if(maGhe[0] == 'D'){
		a = 4;
	}
	else if(maGhe[0] == 'E'){
		a = 5;
	}
	else{
		a = 6;
	}
	int b = (maGhe[1] - 48)*10 + (maGhe[2] - 48);
	if(b > soHang - 1){
		return -1;
	}
	int result = b + soHang*(a-1);
	return result;
}

#endif
