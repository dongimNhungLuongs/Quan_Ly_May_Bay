#ifndef _KHOITAO_H
#define _KHOITAO_H

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

#define MAX_SO_LUONG_MB 300
#define MAX_SO_HIEU_MB 15
#define MAX_LOAI_MB 15
#define MACDINH_TTCB 0
#define MACDINH 0
struct MayBay {
    string soHieu;
    string loaiMayBay;
    int soDay;
    int soHang;
    int soCho;
};

struct CDay
{
    int dd = 1, mm = 1, yy = 2022;
};
struct CTime {
    int gio = 0, phut = 0;
};

struct CDanhSachMB {
    int slMB;
    MayBay* danhSachMB[MAX_SO_LUONG_MB];
    MayBay* creatMB() {
        MayBay* mb = new MayBay;
        mb->soHieu = "";
        mb->loaiMayBay = "";
        mb->soDay = 0;
        mb->soHang = 0;
        mb->soCho = 0;
        return mb;
    }
};

struct TTkhachHang
{
    string CMND = "";
    string Name = "";
    short GioiTinh; // 1 la nam, 0 la nu	
};

struct nodeKhachHang
{
    TTkhachHang HanhKhach; // chua thong tin
    nodeKhachHang* left = NULL;
    nodeKhachHang* right = NULL;
};

struct treeKhachHang
{
	int SoLuong = 0;
	nodeKhachHang *root = NULL;
};

struct Ticket
{
    nodeKhachHang* HanhKhach = NULL;
};

struct ChuyenBay {
    string maChuyenBay = "";
    string soHieuMB = "";
    CDay day;
    CTime thoiGianKhoiHanh;
    string diemDen = "";
    Ticket* Ve;
    int soCho = 0;
    int soDay = 0;
    int soHang = 0;
    string loaiMayBay = "";
    int trangThai = 1; //0: Huy chuyen, 1: Con ve, 2: Het ve, 3: Hoan tat

    void TaoDanhSachVe() {
        Ve = new Ticket[soCho];
        for (int i = 0; i < soCho; i++) {
            Ve[i].HanhKhach = NULL; 
        }
    }
};

struct cacChuyenBay {
    ChuyenBay chuyenBay;
    cacChuyenBay* next = NULL;
};

struct ListChuyenBay
{
    int SoLuong = 0;
    cacChuyenBay* Head = NULL;
    cacChuyenBay* Last = NULL;
};

struct nameNoiDen{
	string noiDen[21] = {
	"VUNGTAU",
    "BINHDINH",
    "CAMAU",
    "CANTHO",
    "DAKLAK",
    "DANANG",
    "DIENBIEN",
    "GIALAI",
    "HAIPHONG",
    "HANOI",
    "KHANHHOA",
    "RACHGIA",
    "PHUQUOC",
    "LAMDONG",
    "NGHEAN",
    "PHUYEN",
    "QUANGNGAI",
    "QUANGNAM",
    "HUE",
    "THANHHOA",
    "QUANGNINH"		
	};
};
// ========================== TAO CHUYEN BAY ==========================================
cacChuyenBay* NewChuyenBay()
{
    cacChuyenBay* cb = new cacChuyenBay;
    cb->chuyenBay.loaiMayBay = "";
    cb->chuyenBay.diemDen = "";
    cb->chuyenBay.maChuyenBay = "";
    cb->chuyenBay.soCho = 0;
    cb->chuyenBay.soHieuMB = "";
    cb->chuyenBay.trangThai = 1;
    cb->chuyenBay.thoiGianKhoiHanh.gio = 0;
    cb->chuyenBay.thoiGianKhoiHanh.phut = 0;
    return cb;
}

void SaveFileKH(treeKhachHang &tree){
	ofstream outfile;
	outfile.open("dsKhachHang.txt",ios::out);
	if (outfile.is_open()){
		outfile << tree.SoLuong << endl;
		if(tree.root == NULL){
			outfile.close();
			return;
		}
		nodeKhachHang *p = tree.root;
			int STACKSIZE = tree.SoLuong ;
		   	treeKhachHang Stack[STACKSIZE];
		   	Stack[STACKSIZE].root = NULL;
		   	int sp =  -1;	// Khoi tao Stack rong   	
		    while (p!=NULL ){
				outfile << p->HanhKhach.CMND << " " << p->HanhKhach.Name << " " << p->HanhKhach.GioiTinh << endl;
		    	if (p->right != NULL){
					Stack[++sp].root = p->right;
				}
		    	if (p->left != NULL){
		    		p=p->left;	
				}
		      	else if(sp==-1) break;
			    else
					p = Stack[sp--].root;
			}		
	} 
	else{
		cout << "Khong the mo file danh sach Khach hang de luu!";
	}
	outfile.close();
	return;
}

int ThemVaoCayKhachHang(treeKhachHang &a, TTkhachHang HanhKhach){
	if (a.root == NULL) // Cay rong
	{
		a.root = new nodeKhachHang;
		a.root->HanhKhach.CMND = HanhKhach.CMND;
		string name = HanhKhach.Name;
		a.root->HanhKhach.Name = name;
		a.root->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		a.root->left = NULL;
		a.root->right = NULL;
		a.SoLuong++;
		ofstream outfile;
		outfile.open("dsKhachHang.txt",ios::app);
		outfile << a.SoLuong << endl;
		outfile << HanhKhach.CMND << " " << HanhKhach.Name << " " << HanhKhach.GioiTinh;
		outfile.close();
		return 1;
	}
	nodeKhachHang *p = a.root;
	while (1)
	{
		if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == 1) // Du lieu can nhap vao  nho hon data tai p
		{
			if (p->left == NULL)
			{
				break;
			}
			else
			{
				p = p->left;
			}
		}
		else
		{
			if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == -1)
			{
				if (p->right == NULL)
				{
					break;
				}
				else
				{
					p = p->right;
				}
			}
			else
			{
				break;
			}
		}
		
	}

	if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == 1 && p->left == NULL)
	{
		a.SoLuong++;
		p->left = new nodeKhachHang;
		p = p->left;
		p->HanhKhach.CMND = HanhKhach.CMND;
		p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		p->HanhKhach.Name = HanhKhach.Name;
		p->left = NULL;
		p->right = NULL;
		SaveFileKH(a);
		return 1;
	}
	if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == -1 && p->right == NULL)
	{
		a.SoLuong++;
		p->right = new nodeKhachHang;
		p = p->right;
		p->HanhKhach.CMND = HanhKhach.CMND;
		p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		p->HanhKhach.Name = HanhKhach.Name;
		p->left = NULL;
		p->right = NULL;
		SaveFileKH(a);
		return 1;
	}
	p->HanhKhach.CMND = HanhKhach.CMND;
	p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
	p->HanhKhach.Name = HanhKhach.Name;
	p->left = NULL;
	p->right = NULL;
	return 1;
}

void timKhachHang(treeKhachHang &Tree, string CMND, string &name, short &gioitinh) // tim kiem tra ve ten
{
	nodeKhachHang *p = Tree.root;
	while (p != NULL){
		
		if (SoSanhCMND(CMND,p->HanhKhach.CMND) == 1){
			p = p->right;
		}
		else{
			if (SoSanhCMND(CMND,p->HanhKhach.CMND) == -1)
			{
				p = p->left;
			}
			else if(SoSanhCMND(CMND,p->HanhKhach.CMND) == 0)
			{

				break;
			}
		}	
	}

	if (p != NULL){

		name = p->HanhKhach.Name;
		gioitinh = p->HanhKhach.GioiTinh;
	}
}

int XoaMayBay(CDanhSachMB & dsmb, ListChuyenBay& dscb, string soHieu) {
    int dem = 0;
    int x = wherex();
    int y = wherey();
    cacChuyenBay* p;
    for (p = dscb.Head; p != NULL; p = p->next)
    {
        if (p->chuyenBay.soHieuMB == soHieu)
        {
            dem++;
            break;
        }
    }
    if (dem > 0) { // n?u có chuy?n bay dang s? d?ng máy bay c?n xóa
    	gotoxy(x,y+2);
    	ChangeColor(12);
        cout << "Khong the xoa may bay nay vi co chuyen bay dang su dung!\n";
        Sleep(1000);
        return 0;
    }
    else { // n?u không có chuy?n bay s? d?ng máy bay c?n xóa
        int viTri = -1;
        for (int i = 0; i < dsmb.slMB; i++) { // tìm v? trí c?a máy bay c?n xóa trong danh sách
            if (dsmb.danhSachMB[i]->soHieu == soHieu) {
                viTri = i;
                break;
            }
        }
        if (viTri == -1) { // n?u không tìm th?y máy bay c?n xóa trong danh sách
        	gotoxy(x,y+2);
        	ChangeColor(12);
            cout << "Khong tim thay may bay co so hieu nay!\n";
            return 0;
        }
        else { // n?u tìm th?y máy bay c?n xóa
            delete dsmb.danhSachMB[viTri]; // thu h?i vùng nh? c?a máy bay
            for (int i = viTri; i < dsmb.slMB - 1; i++) {
                dsmb.danhSachMB[i] = dsmb.danhSachMB[i + 1]; // d?ch chuy?n các ph?n t? trong danh sách d? xóa máy bay c?n xóa
            }
            dsmb.slMB--;
            gotoxy(x,y+2);
            ChangeColor(12);
            cout << "Xoa thanh cong!\n";
            return 1;
        }
    }
}

bool checksoHieu(CDanhSachMB list,string SoHieu)
{
    for (int i = 0; i < list.slMB; i++)
    {
        if (list.danhSachMB[i]->soHieu == SoHieu)
        {
            return 1;
        }
    }
    return 0;
}

bool checksoHieuSua(CDanhSachMB list,string SoHieu)
{
    for (int i = 0; i < list.slMB; i++)
    {
        if (list.danhSachMB[i]->soHieu == SoHieu)
        {
            return 1;
        }
    }
    return 0;
}

bool checkMaChuyenBay(ListChuyenBay& list, string maChuyenBay){
	cacChuyenBay *p = list.Head;
	while (p != NULL)
	{
		if (p->chuyenBay.maChuyenBay == maChuyenBay)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

bool checkHanhKhachCB(cacChuyenBay *p, string CMND)
{
		for (int i = 0; i < p->chuyenBay.soCho; i++)
		{
			if (p->chuyenBay.Ve[i].HanhKhach != NULL)
			{
				if (p->chuyenBay.Ve[i].HanhKhach->HanhKhach.CMND == CMND)
				{
					return 1;
				}
			}
		}
		return 0;
}

void xuatSoHieu(CDanhSachMB& list){ 
	int x = 100, y = 27, count = 0, i;
	gotoxy(x,y);
	ChangeColor(6);
	cout << "+-----------------------------------------------------+";
	gotoxy(x,y+1);
	cout << "|                   Danh Sach So Hieu                 |";
	gotoxy(x,y+2);
	cout << "|-----------------------------------------------------|";
	if(list.slMB % 3 == 0){
		for(i = 1; i <= list.slMB / 3; i++){
			gotoxy(x,y + 2 + i);
			cout << "|                                                     |";			
		}
		gotoxy(x, y + 2 + i);
		cout << "+-----------------------------------------------------+";
		for(i = 0; i < list.slMB; i++){
			gotoxy(x + 3, y + 3 + count);
			cout << list.danhSachMB[i]->soHieu <<": ";
			cout << list.danhSachMB[i]->soCho;
			count++;
			if(count == list.slMB / 3){
				x = wherex() + 8;
				count = 0;
			}				
		} 		
	}
	if(list.slMB % 3 == 1){
		for(i = 1; i <= list.slMB / 3 + 1; i++){
			gotoxy(x,y + 2 + i);
			cout << "|                                                     |";			
		}	
		gotoxy(x, y + 2 + i);
		cout << "+-----------------------------------------------------+";
		for(i = 0; i < list.slMB; i++){
			gotoxy(x+3, y+3+count);
			cout << list.danhSachMB[i]->soHieu << ": ";
			cout << list.danhSachMB[i]->soCho;
			count++;
			if(count == list.slMB/3+1){
				x = wherex() + 8;
				count = 0;
			}
		}	
	}
	if(list.slMB % 3 == 2){
		for(i = 1; i <= list.slMB / 3 + 1; i++){
			gotoxy(x,y + 2 + i);
			cout << "|                                                     |";			
		}	
		gotoxy(x, y + 2 + i);
		cout << "+-----------------------------------------------------+";
		for(i = 0; i < list.slMB; i++){
			gotoxy(x+3, y+3+count);
			cout << list.danhSachMB[i]->soHieu << ": ";
			cout << list.danhSachMB[i]->soCho;
			count++;
			if(count == list.slMB/3+1){
				x = wherex() + 8;
				count = 0;
			}
		}	
	}	
}

bool xuatTTKhachHang(string maCB, string maGhe, string name, string cmnd, short gioiTinh, ListChuyenBay listCB){
	cacChuyenBay *p = listCB.Head;
	ChangeColor(6);
	gotoxy(100,10);
	cout << "------------------------------------------------------------";
	gotoxy(100,11);
	cout << "| CMND/CCCD:                                               |";
	gotoxy(100,12);
	cout << "------------------------------------------------------------";
	gotoxy(100,13);
	cout << "| Name:                                 | Gioi tinh:       |";
	gotoxy(100,14);
	cout << "------------------------------------------------------------";
	ChangeColor(15);
	gotoxy(120,11);
	for(int i = 0; i < name.length(); i++){
		if(name[i] == '0'){
			name[i] = ' ';
		}
	}
	cout << cmnd;
	gotoxy(108,13);
	cout << name;
	gotoxy(153,13);
	if(gioiTinh == 1){
		cout << "Nu";
	}
	else cout<< "Nam";
	while(p != NULL){
		if(p->chuyenBay.maChuyenBay == maCB){
			break;
		}
		p = p->next;
	}
	
	ChangeColor(15);
		gotoxy(100,18);
		cout << "------------------------------------------------------------";
		gotoxy(100,19);
		cout << "|                    Xac nhan Dat Ve                       |";
		gotoxy(100,20);
		cout << "------------------------------------------------------------";
		gotoxy(100,21);
		cout << "|        Dong Y Dat ve (Y)  |   Khong Dat Ve (N)           |";
		gotoxy(100,22);
		cout << "------------------------------------------------------------";
		gotoxy(100,23);
		cout << "| Ma CB:                    | Noi Den:                     |";
		gotoxy(100,24);
		cout << "------------------------------------------------------------";
		gotoxy(100,25);
		cout << "| Day:                      | Time:                        |";
		gotoxy(100,26);
		cout << "------------------------------------------------------------";
		ChangeColor(6);
		gotoxy(137,19);
		cout << maGhe;
		gotoxy(109, 23);
		cout << p->chuyenBay.maChuyenBay;
		gotoxy(139,23);
		cout << p->chuyenBay.diemDen;
		gotoxy(107,25);
		cout << p->chuyenBay.day.dd << "/" << p->chuyenBay.day.mm << "/" << p->chuyenBay.day.yy;
		gotoxy(136,25);
		if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.phut;
			
	char tam = _getch();
	if(tam == 'y' || tam == 'Y'){
		gotoxy(100,13);
		cout << "                                                            ";
		gotoxy(100,14);
		cout << "                                                            ";
		gotoxy(100,18);
		cout << "                                                            ";
		gotoxy(100,19);
		cout << "                                                            ";
		gotoxy(100,20);
		cout << "                                                            ";
		gotoxy(100,21);
		cout << "                                                            ";
		gotoxy(100,22);
		cout << "                                                            ";
		return true;
	}
	else if(tam == 'n' || tam == 'N'){
		gotoxy(100,13);
		cout << "                                                            ";
		gotoxy(100,14);
		cout << "                                                            ";
		gotoxy(100,18);
		cout << "                                                            ";
		gotoxy(100,19);
		cout << "                                                            ";
		gotoxy(100,20);
		cout << "                                                            ";
		gotoxy(100,21);
		cout << "                                                            ";
		gotoxy(100,22);
		cout << "                                                            ";
		return false;
	}
}

bool xuatTTKhachHangHuy(string maCB, string maGhe, string name, string cmnd, short gioiTinh, ListChuyenBay listCB){
	cacChuyenBay *p = listCB.Head;
	ChangeColor(6);
	gotoxy(100,10);
	cout << "------------------------------------------------------------";
	gotoxy(100,11);
	cout << "| CMND/CCCD:                                               |";
	gotoxy(100,12);
	cout << "------------------------------------------------------------";
	gotoxy(100,13);
	cout << "| Name:                                 | Gioi tinh:       |";
	gotoxy(100,14);
	cout << "------------------------------------------------------------";
	ChangeColor(15);
	gotoxy(120,11);
	for(int i = 0; i < name.length(); i++){
		if(name[i] == '0'){
			name[i] = ' ';
		}
	}
	cout << cmnd;
	gotoxy(108,13);
	cout << name;
	gotoxy(153,13);
	if(gioiTinh == 1){
		cout << "Nu";
	}
	else cout<< "Nam";
	while(p != NULL){
		if(p->chuyenBay.maChuyenBay == maCB){
			break;
		}
		p = p->next;
	}
	
	ChangeColor(15);
		gotoxy(100,18);
		cout << "------------------------------------------------------------";
		gotoxy(100,19);
		cout << "|                    Xac nhan Huy Ve                       |";
		gotoxy(100,20);
		cout << "------------------------------------------------------------";
		gotoxy(100,21);
		cout << "|        Dong Y Huy ve (Y)  |   Khong Huy Ve (N)           |";
		gotoxy(100,22);
		cout << "------------------------------------------------------------";
		gotoxy(100,23);
		cout << "| Ma CB:                    | Noi Den:                     |";
		gotoxy(100,24);
		cout << "------------------------------------------------------------";
		gotoxy(100,25);
		cout << "| Day:                      | Time:                        |";
		gotoxy(100,26);
		cout << "------------------------------------------------------------";
		ChangeColor(6);
		gotoxy(137,19);
		cout << maGhe;
		gotoxy(109, 23);
		cout << p->chuyenBay.maChuyenBay;
		gotoxy(139,23);
		cout << p->chuyenBay.diemDen;
		gotoxy(107,25);
		cout << p->chuyenBay.day.dd << "/" << p->chuyenBay.day.mm << "/" << p->chuyenBay.day.yy;
		gotoxy(136,25);
		if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.phut;
			
	char tam = _getch();
	if(tam == 'y' || tam == 'Y'){
		gotoxy(100,13);
		cout << "                                                            ";
		gotoxy(100,14);
		cout << "                                                            ";
		gotoxy(100,18);
		cout << "                                                            ";
		gotoxy(100,19);
		cout << "                                                            ";
		gotoxy(100,20);
		cout << "                                                            ";
		gotoxy(100,21);
		cout << "                                                            ";
		gotoxy(100,22);
		cout << "                                                            ";
		return true;
	}
	else if(tam == 'n' || tam == 'N'){
		gotoxy(100,13);
		cout << "                                                            ";
		gotoxy(100,14);
		cout << "                                                            ";
		gotoxy(100,18);
		cout << "                                                            ";
		gotoxy(100,19);
		cout << "                                                            ";
		gotoxy(100,20);
		cout << "                                                            ";
		gotoxy(100,21);
		cout << "                                                            ";
		gotoxy(100,22);
		cout << "                                                            ";
		return false;
	}
}

bool checkNoiDen(nameNoiDen &name, string check){
	for(int i = 0; i < 21; i++){
		if(name.noiDen[i] == check){
			return true;
		}
	}
	return false;
}

int veKhungNhapThongTin(MayBay* mayBay, CDanhSachMB& listMB) {
    int x = 0, y = 0;
    xuatNhapMB();
	string test;
    x = 20; y = 2;
    while (1) {
        gotoxy(x, y);
        test = nhapDLMB();
        if (test == "") {
        	system("cls");
        	return -1;
    	}
        if (checksoHieu(listMB, test) == 1) {
            gotoxy(x, y);
            cout << "So hieu da ton tai!";
            Sleep(800);
            gotoxy(x, y);
            cout << "                    ";
        }
        else{
        	mayBay->soHieu = test;
            break;       	
		}
    }

    x = 20; y = 3;
    gotoxy(x, y);
    mayBay->loaiMayBay = nhapDLMB();
    if (mayBay->loaiMayBay.length() == 0) {
        system("cls");
        return -1;
    }

    do {
        x = 20; y = 4;
        gotoxy(x, y);
        mayBay->soDay = nhapSo();
        if ((mayBay->soDay > 3 && mayBay->soDay < 7) || mayBay->soDay == NULL)
            break;
        else {
            gotoxy(x, y);
            cout << "So day trong pham vi [4;6]";
            Sleep(800);
            gotoxy(x, y);
            cout << "                           ";
        }

    } while (true);

    if (mayBay->soDay == 0) {
        system("cls");
        return -1;
    }
        int tempD = mayBay->soDay;

    do {
    	int ghHang = 300 / tempD;
        x = 20; y = 5;
        gotoxy(x, y);
        mayBay->soHang = nhapSo();
        if ((mayBay->soHang > 4 && mayBay->soHang <= ghHang) || mayBay->soHang == NULL)
            break;
        else {
            gotoxy(x, y);
            cout << "So hang trong pham vi [5;" << ghHang << "]";
            Sleep(800);
            gotoxy(x, y);
            cout << "                             ";
        }

    } while (true);
    if (mayBay->soHang == 0) {
        system("cls");
        return -1;
    }
    int tempH = mayBay->soHang;

    int tempC = tempH * tempD;
    mayBay->soCho =  tempC; 
    return 0;
}

int veKhungTTChuyenBay(ChuyenBay* chuyenbay, CDanhSachMB& listMB, ListChuyenBay& listCB) {
    int x = 0, y = 0;
    xuatNhapCB();
    //Machuyenbay
    x = 121; y = 2;
    while (1) {
        gotoxy(x, y);
        chuyenbay->maChuyenBay = nhapDLMB();
	    if(chuyenbay->maChuyenBay.length() == 0){
	    	system("cls");
	    	return -1;
		}
        if (checkMaChuyenBay(listCB, chuyenbay->maChuyenBay) == 1){
        	ChangeColor(12);
        	gotoxy(x,y);
        	cout << "Ma nay da ton tai!";
        	gotoxy(x,y);
        	Sleep(500);
        	cout << "                  ";
        	gotoxy(x,y);
        	cout << "Hay thu lai!";
        	gotoxy(x,y);
        	cout << "            ";
        	ChangeColor(15);
		}
		else break;
    }

	//Ngay_khoi_hanh
	checkThoiGian:
	x = 127, y = 4;
	int checkMonth = 1;
	bool checkYear = true;//nam nhuan 
	do {
		gotoxy(x,y);
		cout << "  ";
		loopday:
		ChangeColor(15);
		gotoxy(136,4);
		cout << "  ";
		gotoxy(136,4);
		cout << chuyenbay->day.mm;//in lai thang
		gotoxy(145,4);
		cout << chuyenbay->day.yy;//in lai nam
		gotoxy(127,4);
		cout << chuyenbay->day.dd;
		chuyenbay->day.dd = nhapSoCB(chuyenbay->day.dd);
		if(chuyenbay->day.dd == -1){
			system("cls");
			return -1;
		}
		if(checkMonth != 2){
				if(chuyenbay->day.dd < 1 || chuyenbay->day.dd >31) {
					gotoxy(155,4);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;31]";
					Sleep(500);
					gotoxy(155,4);
					cout << "                         ";
					gotoxy(x,y);
				}
				if(chuyenbay->day.dd >= 1 && chuyenbay->day.dd <= 31) break;						
		}
		else{
			if(checkYear == false){
				if(chuyenbay->day.dd < 1 || chuyenbay->day.dd >28) {
					gotoxy(155,4);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;28]";
					Sleep(500);
					gotoxy(155,4);
					cout << "                         ";
					gotoxy(x,y);
					checkMonth = 2;
				}
				if(chuyenbay->day.dd >= 1 && chuyenbay->day.dd <= 28) break;
			}
			if(checkYear == true){
				if(chuyenbay->day.dd < 1 || chuyenbay->day.dd >29) {
					gotoxy(155,4);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;29]";
					Sleep(500);
					gotoxy(155,4);
					cout << "                         ";
					gotoxy(x,y);
					checkMonth = 2;
				}
				if(chuyenbay->day.dd >= 1 && chuyenbay->day.dd <= 29) break;			
			} 			
		}
	}while(true);

	//nhap_Thang
	x = 136, y = 4; 
	while(checkMonth != 2){
		ChangeColor(15);
		gotoxy(x,y);
		cout << "  ";
		gotoxy(x,y);
		cout << chuyenbay->day.mm;
		chuyenbay->day.mm = nhapSoCB(chuyenbay->day.mm);
		if(chuyenbay->day.mm == -1){
			system("cls");
			return -1;		
		}
		if(chuyenbay->day.mm < 1 || chuyenbay->day.mm > 12){
			gotoxy(155,4);
				ChangeColor(12);
				cout << "Nhap trong pham vi [1;12]";
				Sleep(500);
				gotoxy(155,4);
				cout << "                         ";
				gotoxy(x,y);
		}
		if(chuyenbay->day.mm >= 1 && chuyenbay->day.mm <= 12){
			if(chuyenbay->day.dd > 29 && chuyenbay->day.mm == 2 && checkYear == true){
				ChangeColor(12);
				gotoxy(155,4);
				cout << "Thang 2 chi co 29 ngay";
				gotoxy(155,4);
				Sleep(500);
				cout << "                      ";
				gotoxy(155,4);
				cout << "Vui long nhap lai ngay khoi hanh!";
				gotoxy(155,4);
				Sleep(500);
				cout << "                                 ";
				checkMonth = 2;
				goto loopday;
			}
			break;
		}
	}
	//Nam khoi hanh
	x = 145, y = 4;
	do{
		ChangeColor(15);
		gotoxy(x,y);
		cout << "    ";
		gotoxy(x,y);
		cout << chuyenbay->day.yy;
		chuyenbay->day.yy = suaNhapSo(chuyenbay->day.yy);
		if(chuyenbay->day.yy == -1){
			system("cls"); 
			return -1;
		}
		if(chuyenbay->day.yy < 2023 || chuyenbay->day.yy > 2027){
			ChangeColor(12);
			gotoxy(155,4);
			cout << "Nhap trong pham vi [2023;2027]";// 5 nam
			gotoxy(155,4);
			Sleep(500);
			cout << "                              ";
		}
		if(chuyenbay->day.yy >= 2023 && chuyenbay->day.yy <= 2027){
			checkYear = checkYearNhuan(chuyenbay->day.yy);
			if(chuyenbay->day.mm == 2){
				if(checkYear == true){
					if(chuyenbay->day.dd > 29){
						ChangeColor(12);
						gotoxy(155,4);
						cout << "Thang 2 chi co 29 ngay";
						gotoxy(155,4);
						Sleep(500);
						cout << "                      ";
						gotoxy(155,4);
						cout << "Vui long nhap lai ngay khoi hanh!";
						gotoxy(155,4);
						Sleep(500);
						cout << "                                 ";
						checkMonth = 2;
						goto loopday;				
					}
					else break;					
				}
				else{
					if(chuyenbay->day.dd > 28){
						ChangeColor(12);
						gotoxy(155,4);
						cout << "Thang 2 chi co 28 ngay";
						gotoxy(155,4);
						Sleep(500);
						cout << "                      ";
						gotoxy(155,4);
						cout << "Vui long nhap lai ngay khoi hanh!";
						gotoxy(155,4);
						Sleep(500);
						cout << "                                 ";
						checkMonth = 2;
						checkYear = false;
						goto loopday;				
					}				
					else break;	
				}		
			}
			else break;
		}	
	}while(true);
	/// thoi gian bay
	x = 132, y = 6;
	
	do{
		ChangeColor(15);
		gotoxy(x,y);
		cout << "  ";
		gotoxy(x,y);
		cout << chuyenbay->thoiGianKhoiHanh.gio;			
		chuyenbay->thoiGianKhoiHanh.gio = nhapSoCB(chuyenbay->thoiGianKhoiHanh.gio);
		if(chuyenbay->thoiGianKhoiHanh.gio == -1){
			system("cls");
			return -1;
		}
		if(chuyenbay->thoiGianKhoiHanh.gio > 23 || chuyenbay->thoiGianKhoiHanh.gio < 0){
			ChangeColor(12);
			gotoxy(155, 6);
			cout << "Vui long nhap trong [00;23]";
			Sleep(800);
			gotoxy(155,6);
			cout << "                           ";
		}
		if(chuyenbay->thoiGianKhoiHanh.gio <= 23 && chuyenbay->thoiGianKhoiHanh.gio >=0){
			if(chuyenbay->thoiGianKhoiHanh.gio >= 0 && chuyenbay->thoiGianKhoiHanh.gio <= 9){
				gotoxy(x,y);
				cout << "0";
				cout << chuyenbay->thoiGianKhoiHanh.gio;
				break;
			}
			break;
		}	
	} while(true);
	//Phut_khoi_hanh
	x = 141, y = 6;
	do{
		ChangeColor(15);
		gotoxy(x,y);
		cout << "   ";
		gotoxy(x,y);
		cout << chuyenbay->thoiGianKhoiHanh.phut;
		chuyenbay->thoiGianKhoiHanh.phut = nhapSoCB(chuyenbay->thoiGianKhoiHanh.phut);
		if(chuyenbay->thoiGianKhoiHanh.phut == -1){
			system("cls");
			return -1;
		}
		if(chuyenbay->thoiGianKhoiHanh.phut > 59 || chuyenbay->thoiGianKhoiHanh.phut < 0){
			ChangeColor(12);
			gotoxy(155, 6);
			cout << "Vui long nhap trong [00;59]";
			Sleep(800);
			gotoxy(155, 6);
			cout << "                           ";
		}
		if(chuyenbay->thoiGianKhoiHanh.phut <= 59 && chuyenbay->thoiGianKhoiHanh.phut >= 0){
			if(chuyenbay->thoiGianKhoiHanh.phut >= 0 && chuyenbay->thoiGianKhoiHanh.phut <= 9){
				gotoxy(x,y);
				cout << "0";
				cout << chuyenbay->thoiGianKhoiHanh.phut;
				break;
			}
			break;
		}
	}while(true);
	if(checkThoiGian(chuyenbay->thoiGianKhoiHanh.gio, chuyenbay->thoiGianKhoiHanh.phut, chuyenbay->day.dd,chuyenbay->day.mm, chuyenbay->day.yy) == false){

		ChangeColor(12);
		gotoxy(155, 6);
		cout << "Thoi gian khoi hanh toi thieu sau 3 gio!";
		Sleep(1000);
		gotoxy(155, 6);
		cout << "                                        ";
		gotoxy(155, 6);
		cout << "Hay nhap lai thoi gian!";
		Sleep(800);
		gotoxy(155, 6);
		cout << "                       ";
		goto checkThoiGian;
	}
	// Noi_den 
	x = 121, y = 8;
	xuatNoiDen();
	nameNoiDen name;
	while(true){
		if(chuyenbay->diemDen != ""){
			cout << chuyenbay->diemDen;
		}
		ChangeColor(15);
		gotoxy(x, y);
		chuyenbay->diemDen = suaDLMB(chuyenbay->diemDen);
		if(chuyenbay->diemDen.length() == 0){
	    	system("cls");
	    	return -1;
		}
		if(checkNoiDen(name, chuyenbay->diemDen) == false){
			ChangeColor(12);
			gotoxy(155, 8);
			cout << "Noi nay hien chua cap nhat!";
			Sleep(1000);
			gotoxy(155,8);
			cout << "                           ";
			gotoxy(x,y);
			cout << "                           ";
			chuyenbay->diemDen = "";
		}
		else break;
	}
	xoaNoiDen();
	//Nhap_soHieu_mayBay
	x = 121, y = 10;
	xuatSoHieu(listMB);
	while(true){
		ChangeColor(15);
		gotoxy(x,y);
		if(chuyenbay->soHieuMB != ""){
			cout << chuyenbay->soHieuMB;
		}
		chuyenbay->soHieuMB = suaDLMB(chuyenbay->soHieuMB);
		if(chuyenbay->soHieuMB.length() == 0){
	    	system("cls");
	    	return -1;
		}
		if(checksoHieu(listMB, chuyenbay->soHieuMB) != 1){
			ChangeColor(12);
			gotoxy(155, 10);
			cout << "So hieu nay khong ton tai!";
			Sleep(900);
			gotoxy(155,10);
			cout << "                          ";
			gotoxy(x,y);
			cout << "                           ";
		}
		else{
			int ddNhap = chuyenbay->day.dd;
			int hhNhap = chuyenbay->thoiGianKhoiHanh.gio;
			int minNhap = chuyenbay->thoiGianKhoiHanh.phut;
			cacChuyenBay *p = listCB.Head;
			while(p != NULL){
				if(p->chuyenBay.soHieuMB == chuyenbay->soHieuMB){
					if(p->chuyenBay.trangThai == 1 || p->chuyenBay.trangThai == 2){
						if(p->chuyenBay.day.yy == chuyenbay->day.yy && p->chuyenBay.day.mm == chuyenbay->day.mm){
							if(checkTwoTime(p->chuyenBay.thoiGianKhoiHanh.gio, hhNhap, p->chuyenBay.thoiGianKhoiHanh.phut, minNhap, p->chuyenBay.day.dd, ddNhap) == 1){
								ChangeColor(12);
								gotoxy(155,10);
								cout << "Ma so nay dang co chuyen bay!";
								Sleep(1000);
								gotoxy(155, 10);
								cout << "                             ";
								gotoxy(80, 20);
							    cout << "+---------------------------------------+";
							    gotoxy(80, 21);
							    cout << "| Ban co muon nhap lai Ma so hieu khac? |";
							    gotoxy(80, 22);
							    cout << "+---------------------------------------+";
							    gotoxy(80, 23);
							    cout << "|      [1] Dong Y / [0] Khong Dong Y    |";
							    gotoxy(80, 24);
							    cout << "+---------------------------------------+";
							    anConTro();
							    char dapAn;
							    while(true){
							    	dapAn = _getch();
							    	if(dapAn == 49 || dapAn == 48) break;
								}
							    if(nhapLuaChon(dapAn, 0, 1) == 0){
									gotoxy(80, 20);
							    	cout << "                                         ";
								    gotoxy(80, 21);
								    cout << "                                         ";
								    gotoxy(80, 22);
								    cout << "                                         ";
								    gotoxy(80, 23);
							    	cout << "                                         ";
								    gotoxy(80, 24);
								    cout << "                                         ";
								    hienConTro();
								    gotoxy(155,10);
								    cout << "Vui long nhap lai thoi gian cach 12 tieng!";
								    Sleep(1100);
								    gotoxy(155,10);
								    cout << "                                          ";
								    ChangeColor(15);
									chuyenbay->thoiGianKhoiHanh.gio = 0;
									chuyenbay->thoiGianKhoiHanh.phut = 0;
									chuyenbay->day.dd = 1;
									chuyenbay->day.mm = 1;
									chuyenbay->day.yy = 2022;
								    goto checkThoiGian;
								}
							    else{
									gotoxy(80, 20);
							    	cout << "                                         ";
								    gotoxy(80, 21);
								    cout << "                                         ";
								    gotoxy(80, 22);
								    cout << "                                         ";
								    gotoxy(80, 23);
							    	cout << "                                         ";
								    gotoxy(80, 24);
								    cout << "                                         ";
								    hienConTro();
								    ChangeColor(15);
							    	break;
								}
							}
						}
					}
				}
				p = p->next;
			}
			if(p == NULL)
			break;
		}
	}
	for( int j = 0; j < listMB.slMB; j++){
        if (chuyenbay->soHieuMB == listMB.danhSachMB[j]->soHieu) {
	        chuyenbay->loaiMayBay = listMB.danhSachMB[j]->loaiMayBay;
	        chuyenbay->soCho = listMB.danhSachMB[j]->soCho;
	        chuyenbay->soDay = listMB.danhSachMB[j]->soDay;
	        chuyenbay->soHang = listMB.danhSachMB[j]->soHang;
	        chuyenbay->TaoDanhSachVe();
       	}	
	}
    return 0;
}

void InDanhSachChuyenBay(ListChuyenBay &chuyenbay) {
	ChangeColor(2);
	int n = 1, x = 1;
    cout << "+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                   DANH SACH CHUYEN BAY                                      |" << endl;
    cout << "+---------------------------------------------------------------------------------------------+" << endl;
	cout << "| STT |  Ma Chuyen Bay | Thoi Gian | Ngay Khoi Hanh |    Den    | Trang Thai |   So Hieu MB   |" << endl;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		n++;
	}
	for(int i = 1; i < n; i ++){
		cout << "|-----+----------------+-----------+----------------+-----------+------------+----------------|" << endl;
		cout << "|     |                |           |                |           |            |                |" << endl;
	}
	cout << "+---------------------------------------------------------------------------------------------+";
	n = 1;
	for (cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next) {
		int i = p->chuyenBay.maChuyenBay.length();
		int b = (15 - i)/2; 
		gotoxy(7 + b, 4 + x);
		cout << p->chuyenBay.maChuyenBay;
		x += 2;
		n++;
	}
	x = 1;
	for(int i = 1; i < n; i++){
		gotoxy(3, 4 + x);
		cout << i;
		x += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		gotoxy(27, 4 + n);
		if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		}
		else cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
		}
		else cout << p->chuyenBay.thoiGianKhoiHanh.phut;
		
		
		if(checkThoiGianBay(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == false){
        	p->chuyenBay.trangThai = 3;
		}
		n += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		gotoxy(39, 4 + n);
		if(p->chuyenBay.day.dd < 10)
			cout << "0" << p->chuyenBay.day.dd << "/";
		else
			cout << p->chuyenBay.day.dd << "/";
		if(p->chuyenBay.day.mm < 10)
			cout << "0" << p->chuyenBay.day.mm << "/";
		else
			cout << p->chuyenBay.day.mm << "/";
		cout << p->chuyenBay.day.yy;
		n += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		gotoxy(54, 4 + n);
		cout << p->chuyenBay.diemDen;
		n += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(p->chuyenBay.trangThai == 2 || p->chuyenBay.trangThai == 1)
		for(int i = 0; i < p->chuyenBay.soCho; i++){
			if(p->chuyenBay.Ve[i].HanhKhach == NULL){
				p->chuyenBay.trangThai = 1;
				break;
			}
			if(i == p->chuyenBay.soCho-1){
				p->chuyenBay.trangThai = 2;
			}
			
		}
		if(p->chuyenBay.trangThai == 1){
			gotoxy(66, 4 + n);
			cout << "Con Ve";
		}
		if(p->chuyenBay.trangThai == 0){
			gotoxy(66, 4 + n);
			cout << "Huy chuyen";
		}
		if(p->chuyenBay.trangThai == 2){
			gotoxy(66, 4 + n);
			cout << "Het Ve";
		}
		if(p->chuyenBay.trangThai == 3){
			gotoxy(66, 4 + n);
			cout << "Hoan Thanh";
		}
		n += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		int i = p->chuyenBay.soHieuMB.length();
		int b = (15 - i)/2; 
		gotoxy(78 + b, 4 + n);
		cout << p->chuyenBay.soHieuMB;
		n += 2;
	}
}

void xoaAllVe(ListChuyenBay &listCB, string soHieu){
	cacChuyenBay *p = listCB.Head;
	for(p; p != NULL; p = p->next){
		if(p->chuyenBay.soHieuMB ==  soHieu){
			int n = 0;
			for(n; n < p->chuyenBay.soCho; n++){
				p->chuyenBay.Ve[n].HanhKhach = NULL;
			} 
		}
	}
}

int SoLuongKHTrenCB(cacChuyenBay *p)
{
	int SoLuong = 0;
	for (int i = 0; i < p->chuyenBay.soCho ; i++)
	{
		if (p->chuyenBay.Ve[i].HanhKhach != NULL)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}

int soLuongCBHuyVe(ListChuyenBay &a)
{
	int SoLuong = 0;
	for (cacChuyenBay *p = a.Head; p != NULL; p = p->next)
	{
		int hh = p->chuyenBay.thoiGianKhoiHanh.gio;
		int min = p->chuyenBay.thoiGianKhoiHanh.phut;
		int dd = p->chuyenBay.day.dd;
		int mm = p->chuyenBay.day.mm;
		int yy = p->chuyenBay.day.yy;
		if (SoLuongKHTrenCB(p) != 0 && checkThoiGianBay(hh, min, dd, mm, yy) == true)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}

void LayDanhSachHuyVe(ListChuyenBay &a, string *q){
	int dem = 0;

	cacChuyenBay *p;
	for (p = a.Head; p != NULL; p = p->next){
		int hh = p->chuyenBay.thoiGianKhoiHanh.gio;
		int min = p->chuyenBay.thoiGianKhoiHanh.phut;
		int dd = p->chuyenBay.day.dd;
		int mm = p->chuyenBay.day.mm;
		int yy = p->chuyenBay.day.yy;
		if (SoLuongKHTrenCB(p) != 0 && checkThoiGianBay(hh,min,dd,mm,yy)){
			q[dem] = p->chuyenBay.maChuyenBay;
			dem++;
		}
	}
	return;
}

bool InDSHuyVE(ListChuyenBay &chuyenbay, CDanhSachMB &listMB, treeKhachHang &tree){
	string *cbHuyVe;
	int SoLuong = soLuongCBHuyVe(chuyenbay);

	if (SoLuong != 0){
		cbHuyVe = new string[SoLuong];
		for (int i = 0; i < SoLuong; i++) {
        	cbHuyVe[i] = ""; // Xóa n?i dung c?a m?ng
    	}
		LayDanhSachHuyVe(chuyenbay,cbHuyVe);
		ChangeColor(2);
		int n = 1, x = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true)
					n++;	
				}
				if(cbHuyVe[k] == ""){
					break;
				}				
			}
		}
			
	    cout << "+---------------------------------------------------------------------------------------------+" << endl;
	    cout << "|                                   DANH SACH CHUYEN BAY                                      |" << endl;
	    cout << "+---------------------------------------------------------------------------------------------+" << endl;
		cout << "| STT |  Ma Chuyen Bay | Thoi Gian | Ngay Khoi Hanh |    Den    | Trang Thai |   So Hieu MB   |" << endl;
	
		for(int i = 1; i < n; i ++){
			cout << "|-----+----------------+-----------+----------------+-----------+------------+----------------|" << endl;
			cout << "|     |                |           |                |           |            |                |" << endl;
		}
		cout << "+---------------------------------------------------------------------------------------------+";
		n = 1;
		for (cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next) {
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						int i = p->chuyenBay.maChuyenBay.length();
						int b = (15 - i)/2; 
						gotoxy(7 + b, 4 + x);
						cout << p->chuyenBay.maChuyenBay;
						x += 2;
						n++;				
					}
				}
				if(cbHuyVe[k] == ""){
					break;
				}			
			}
		}
		x = 1;
		for(int i = 1; i < n; i++){
			gotoxy(3, 4 + x);
			cout << i;
			x += 2;
		}
		n = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						gotoxy(27, 4 + n);
						if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
							cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
						}
						else cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
						if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
							cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
						}
						else cout << p->chuyenBay.thoiGianKhoiHanh.phut;
						
						n += 2;					
					}	
				}
				if(cbHuyVe[k] == ""){
					break;
				}				
			}
		}
		n = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						gotoxy(39, 4 + n);
						if(p->chuyenBay.day.dd < 10)
							cout << "0" << p->chuyenBay.day.dd << "/";
						else
							cout << p->chuyenBay.day.dd << "/";
						if(p->chuyenBay.day.mm < 10)
							cout << "0" << p->chuyenBay.day.mm << "/";
						else
							cout << p->chuyenBay.day.mm << "/";
						cout << p->chuyenBay.day.yy;
						n += 2;					
					}
				}
				if(cbHuyVe[k] == ""){
					break;
				}				
			}
		}
		n = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						gotoxy(54, 4 + n);
						cout << p->chuyenBay.diemDen;
						n += 2;				
					}	
				}
				if(cbHuyVe[k] == ""){
					break;
				}				
			}
		}
		n = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						gotoxy(66, 4 + n);
						if(p->chuyenBay.trangThai == 1)
							cout << "Con Ve";
						else if(p->chuyenBay.trangThai == 2)
							cout << "Het Ve";
						n += 2;					
					}
				}
				if(cbHuyVe[k] == ""){
					break;
				}			
			}
		}
		n = 1;
		for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
			int k = 0;
			for(k; k < SoLuong; k++){
				if(cbHuyVe[k] ==  p->chuyenBay.maChuyenBay){
					if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
						int i = p->chuyenBay.soHieuMB.length();
						int b = (15 - i)/2; 
						gotoxy(78 + b, 4 + n);
						cout << p->chuyenBay.soHieuMB;
						n += 2;	
						for( int j = 0; j < listMB.slMB; j++){
					        if (p->chuyenBay.soHieuMB == listMB.danhSachMB[j]->soHieu) {
						        p->chuyenBay.loaiMayBay = listMB.danhSachMB[j]->loaiMayBay;
						        p->chuyenBay.soCho = listMB.danhSachMB[j]->soCho;
						        p->chuyenBay.soDay = listMB.danhSachMB[j]->soDay;
						        p->chuyenBay.soHang = listMB.danhSachMB[j]->soHang;
					        }
		    			}					
					}
				}
				if(cbHuyVe[k] == ""){
					break;
				}				
			}	
		}
		return true; 
	}
	else{
		gotoxy(100,20);
		ChangeColor(12);
		cout << "Khong co ve de huy!";
		gotoxy(100, 25);
		ChangeColor(15);
		system("pause");
		return false;
	}
}

bool huyVe(ListChuyenBay& chuyenbay, string maCB){
	int soHang, soCho, soDay;
	bool checkMaCB =true;
	string *cbHuyVe;
	int SoLuong = soLuongCBHuyVe(chuyenbay);
	
	if (SoLuong != 0){
		cbHuyVe = new string[SoLuong];
		for (int i = 0; i < SoLuong; i++) {
        	cbHuyVe[i] = ""; // Xóa n?i dung c?a m?ng
    	}
    }
	LayDanhSachHuyVe(chuyenbay,cbHuyVe);
	
	cacChuyenBay *q = chuyenbay.Head;
	while(q != NULL && checkMaCB){
		if(maCB == q->chuyenBay.maChuyenBay)
		for(int k = 0; k < SoLuong; k++){
			if(cbHuyVe[k] == maCB){
				checkMaCB = false;
				break;
			}
		}
		if(checkMaCB){
			q = q->next;
		}
	}
	if(q == NULL){
		gotoxy(125, 9);
		ChangeColor(12);
		cout << "Khong co ma CB ton tai!";
		Sleep(700);
		return false;
	}
	string name = "";
	string CMND = "";
	short gioiTinh ;
	soCho = q->chuyenBay.soCho;
	soDay = q->chuyenBay.soDay;
	soHang = q->chuyenBay.soHang;
	string dsVeDaDat[soCho] = {};
	int count = 0;
	xoaManHinh();
	ChangeColor(15);
	gotoxy(4,4);
	cout << "+";
	for(int i = 1; i <= 7*soDay-2;i++){
		cout <<"-";
	}
	
	cout << "+";
	
	
	for(int i = 1; i <= soHang; i++){
		gotoxy(4,4+i);
		cout << "|";
		for(int j = 1; j <= 7*soDay-2;j++){
			cout <<" ";
		}
		cout<<"|";
	}
	gotoxy(4,4 +soHang+1);
	cout << "+";
	for(int i = 1; i <= 7*soDay-2;i++){
		cout <<"-";
	}	
	cout << "+";

	int x = 7; 
	for(int i = 1; i <= soDay; i++){
		for(int j = 0;  j < soHang; j++){
			string viTri = taoViTri(i,j);
			if (q->chuyenBay.Ve[j + soHang*(i-1)].HanhKhach != NULL ){
					ChangeColor(12);
					gotoxy(x,5+j);
					cout << viTri;
					ChangeColor(15);
					dsVeDaDat[count] = viTri;
					count++;
			}
			else{
				gotoxy(x,5+j);
				cout << viTri;				
			}	
		}
		x = wherex();
		x = x + 3;
	}
	bool kiemTra = true;
	string maGhe = "";
	int viTriSo = -1;
	bool check = true;
	while (check){
		ChangeColor(10);
		gotoxy(100,10);
	    cout << "------------------------------------------------------------";
		gotoxy(100,11);
		cout << "| Nhap ma ghe muon huy:                                    |";
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(125,11);
		maGhe = nhapDatVe();
		viTriSo = str2int(maGhe,soHang);
		if(maGhe == ""){
			system("cls");
			return false;
		}
		if(viTriSo <= soCho - 1 && viTriSo >= 0){
			for(int i = 0; i <= count; i++){
				if(maGhe == dsVeDaDat[i]){
					name = q->chuyenBay.Ve[viTriSo].HanhKhach->HanhKhach.Name;
					CMND = q->chuyenBay.Ve[viTriSo].HanhKhach->HanhKhach.CMND;
					gioiTinh = q->chuyenBay.Ve[viTriSo].HanhKhach->HanhKhach.GioiTinh;
					kiemTra = xuatTTKhachHangHuy(maCB, maGhe, name, CMND, gioiTinh, chuyenbay);
					
					if(kiemTra == true){
						q->chuyenBay.Ve[viTriSo].HanhKhach = NULL;
						return true;
					}
					else {
						system("cls");
						return false;
					}	
				}
				if(i == count){
					ChangeColor(12);
					gotoxy(125,9);
					cout << "Ma ghe nay khong co nguoi dat!";
					Sleep(800);
					gotoxy(125,9);
					cout << "                              ";
					break;
				}
			}			
		}
		else if(viTriSo > soCho - 1 || viTriSo < 0){
			ChangeColor(12);
			gotoxy(125,9);
			cout << "Ghe ban nhap khong ton tai";
			Sleep(600);
			gotoxy(125,9);
			cout << "                          ";
			viTriSo = -1;
		}		
	}
	return true;
}

void InDanhSachNgay(ListChuyenBay &chuyenbay, string diemDen, short dd, short mm, short yy){
	ChangeColor(6);
	int n = 0;
	gotoxy(75,9);
	cout << "Danh Sach chuyen bay vao:" ; 
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(diemDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1 && dd == p->chuyenBay.day.dd && mm == p->chuyenBay.day.mm && yy == p->chuyenBay.day.yy){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true)
			n++;		
		}
	}
	
	if(n == 0){
		ChangeColor(12);
		gotoxy(75,15);
		cout << "Khong co chuyen bay nao hoat dong!";
		Sleep(1000);
		gotoxy(75,15);
		cout << "                                  ";
		if(_getch()) system("cls");
		return;
	}
	gotoxy(50,14);
	short y = wherey();
	for(int i = 0; i < n; i++){
		gotoxy(50,y);
		cout << "-------------------------------------------------------------";
		gotoxy(50,y+1);
		cout << "| Ma CB:                 | Thoi gian:       | Ve Trong:     |";
		y = wherey()+1;		
	}	
	gotoxy(50,y);
	cout << "-------------------------------------------------------------";

	int x = 0, k = 0, dem = 0;
	for (cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next) {
		if(diemDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1 && dd == p->chuyenBay.day.dd && mm == p->chuyenBay.day.mm && yy == p->chuyenBay.day.yy){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				int i = p->chuyenBay.maChuyenBay.length();
				int b = (15 - i)/2; 
				gotoxy(58 + b, 15 + x);
				cout << p->chuyenBay.maChuyenBay;
				gotoxy(88, 15 + x);
				if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
					cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
				}
				else cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
				if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
					cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
				}
				else cout << p->chuyenBay.thoiGianKhoiHanh.phut;
				for(int i = 0; i < p->chuyenBay.soCho; i++){
					if(p->chuyenBay.Ve[i].HanhKhach != NULL){
						dem++;
					}
				}
				gotoxy(106, 15 + x);
				cout << p->chuyenBay.soCho - dem;
				dem = 0;				
				x += 2;				
			}
		}
	}

	if(_getch()) system("cls");
}

bool InDSDatVe(ListChuyenBay& chuyenbay, string noiDen, CDanhSachMB& listMB){
	ChangeColor(2);
	int n = 1, x = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true)
			n++;	
		}
	}
	if(n == 1){
		ChangeColor(12);
		gotoxy(85,8);
		cout << "Khong co chuyen bay nao hoat dong!";
		Sleep(1000);
		gotoxy(85,8);
		cout << "                                  ";
		return false;
	}
		
    cout << "+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                   DANH SACH CHUYEN BAY                                      |" << endl;
    cout << "+---------------------------------------------------------------------------------------------+" << endl;
	cout << "| STT |  Ma Chuyen Bay | Thoi Gian | Ngay Khoi Hanh |    Den    | Trang Thai |   So Hieu MB   |" << endl;

	for(int i = 1; i < n; i ++){
		cout << "|-----+----------------+-----------+----------------+-----------+------------+----------------|" << endl;
		cout << "|     |                |           |                |           |            |                |" << endl;
	}
	cout << "+---------------------------------------------------------------------------------------------+";
	n = 1;
	for (cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next) {
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				int i = p->chuyenBay.maChuyenBay.length();
				int b = (15 - i)/2; 
				gotoxy(7 + b, 4 + x);
				cout << p->chuyenBay.maChuyenBay;
				x += 2;
				n++;				
			}
		}
	}
	x = 1;
	for(int i = 1; i < n; i++){
		gotoxy(3, 4 + x);
		cout << i;
		x += 2;
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				gotoxy(27, 4 + n);
				if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
					cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
				}
				else cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
				if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
					cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
				}
				else cout << p->chuyenBay.thoiGianKhoiHanh.phut;
				
				n += 2;					
			}	
		}
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				gotoxy(39, 4 + n);
				if(p->chuyenBay.day.dd < 10)
					cout << "0" << p->chuyenBay.day.dd << "/";
				else
					cout << p->chuyenBay.day.dd << "/";
				if(p->chuyenBay.day.mm < 10)
					cout << "0" << p->chuyenBay.day.mm << "/";
				else
					cout << p->chuyenBay.day.mm << "/";
				cout << p->chuyenBay.day.yy;
				n += 2;					
			}
		}
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				gotoxy(54, 4 + n);
				cout << p->chuyenBay.diemDen;
				n += 2;				
			}	
		}
	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				gotoxy(66, 4 + n);
				cout << "Con Ve";
				n += 2;					
			}
		}

	}
	n = 1;
	for(cacChuyenBay* p = chuyenbay.Head; p != NULL; p = p->next){
		if(noiDen ==  p->chuyenBay.diemDen && p->chuyenBay.trangThai == 1){
			if(checkThoiGian(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == true){
				int i = p->chuyenBay.soHieuMB.length();
				int b = (15 - i)/2; 
				gotoxy(78 + b, 4 + n);
				cout << p->chuyenBay.soHieuMB;
				n += 2;	
				for( int j = 0; j < listMB.slMB; j++){
			        if (p->chuyenBay.soHieuMB == listMB.danhSachMB[j]->soHieu) {
				        p->chuyenBay.loaiMayBay = listMB.danhSachMB[j]->loaiMayBay;
				        p->chuyenBay.soCho = listMB.danhSachMB[j]->soCho;
				        p->chuyenBay.soDay = listMB.danhSachMB[j]->soDay;
				        p->chuyenBay.soHang = listMB.danhSachMB[j]->soHang;
			        }
    			}					
			}
		}
	}

	return true;
}

bool checkCB(ListChuyenBay& listCB, string maCB){
	cacChuyenBay *p =listCB.Head;
	int doDai, b;
	while(p != NULL){
		if(p->chuyenBay.maChuyenBay == maCB){
			return true;
		}
		p = p->next;
	}
	if(p == NULL){
		ChangeColor(12);
		gotoxy(121, 14);
		cout << "Ma Chuyen Bay khong ton tai!";
		Sleep(800);
		gotoxy(121,14);
		cout << "                            ";
		return false;
	}
}

bool datVe(ListChuyenBay& ListCB, treeKhachHang& tree, string maCB, string diemDen){
	xoaManHinh();
	ChangeColor(15);
	cacChuyenBay *p = ListCB.Head;
	int soCho, soDay, soHang;
	int doDai;
	while(p != NULL){
		if(p->chuyenBay.maChuyenBay == maCB && p->chuyenBay.diemDen == diemDen && p->chuyenBay.trangThai == 1){   
			
			break;
		}
		p = p->next;
	}
	if(p == NULL){
		gotoxy(85,8);
		ChangeColor(12);
		cout << "Khong co ma CB ton tai!";
		Sleep(700);
		return false;
	}
	
	soCho = p->chuyenBay.soCho;
	soDay = p->chuyenBay.soDay;
	soHang = p->chuyenBay.soHang;
	string dsVeDaDat[soCho] = {};

	int count = 0;

	gotoxy(4,4);
	cout << "+";
	for(int i = 1; i <= 7*soDay-2;i++){
		cout <<"-";
	}
	
	cout << "+";
	
	
	for(int i = 1; i <= soHang; i++){
		gotoxy(4,4+i);
		cout << "|";
		for(int j = 1; j <= 7*soDay-2;j++){
			cout <<" ";
		}
		cout<<"|";
	}
	gotoxy(4,4 +soHang+1);
	cout << "+";
	for(int i = 1; i <= 7*soDay-2;i++){
		cout <<"-";
	}	
	cout << "+";

	int x = 7, k = 0; 
	for(int j = 0;  j < soCho; j++){
		string viTri = num2str(j, soHang);
		if (p->chuyenBay.Ve[j].HanhKhach != NULL ){
				ChangeColor(12);
				gotoxy(x,5+k);
				cout << viTri;
				ChangeColor(15);
				dsVeDaDat[count] = viTri;
				count++;
				k++;
		}
		else{
			gotoxy(x,5+k);
			k++;
			cout << viTri;				
		}
		if(k == soHang){
			k = 0;
			x = wherex();
			x = x + 3;	
		}	
	}
		
	string maGhe = "";
	int viTriSo = -1;
	bool check = true;
	while (check){
		ChangeColor(10);
		gotoxy(100,10);
	    cout << "------------------------------------------------------------";
		gotoxy(100,11);
		cout << "| Nhap ma ghe ban muon:                                    |";
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(125,11);
		maGhe = nhapDatVe();
		viTriSo = str2int(maGhe,soHang);
		if(maGhe == ""){
			system("cls");
			check = false;
			return false;
		}
		if(viTriSo <= soCho - 1 && viTriSo >= 0){
			for(int i = 0; i <= count; i++){
				if(maGhe == dsVeDaDat[i]){
					ChangeColor(12);
					gotoxy(125,9);
					cout << "Da co nguoi dat! Chon Lai!";
					Sleep(600);
					gotoxy(125,9);
					cout << "                          ";
					break;	
				}
				else{
					check = false;
				}
			}			
		}
		else if(viTriSo > soCho - 1 || viTriSo < 0){
			ChangeColor(12);
			gotoxy(125,9);
			cout << "Ghe ban nhap khong ton tai";
			Sleep(600);
			gotoxy(125,9);
			cout << "                          ";
			viTriSo = -1;
		}
	}
	string cmnd = "";
	string name = "";
	short gioiTinh = 1;//1 la gai, 0 la trai
	while(true){
		ChangeColor(10);
		gotoxy(100,10);
		cout << "------------------------------------------------------------";
		gotoxy(100,11);
		cout << "| Nhap ma CMND cua ban:                                    |";
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(125,11);
		ChangeColor(15);
		cmnd = nhapCMND(cmnd);	
		if(cmnd == ""){
			system("cls");
			return false;
		}	

		timKhachHang(tree, cmnd, name, gioiTinh);

		if(name != ""){

			bool xacNhan = true;
			for(int k = 0; k <= count; k++){

				if(dsVeDaDat[0] == ""){
					break;
				}
				cout << count;
				if(dsVeDaDat[k] != ""){
					int n = str2int(dsVeDaDat[k], soHang);
					if(p->chuyenBay.Ve[n].HanhKhach != NULL){
						if(p->chuyenBay.Ve[n].HanhKhach->HanhKhach.CMND == cmnd){
							ChangeColor(12);
							gotoxy(125,9);
							cout << "Khach Hang nay da dat ve cua chuyen bay nay!";
							Sleep(1000);
							gotoxy(125,9);
							cout << "                                            ";
							xacNhan = false;
							break;
						}					
					}
				}		
			}

			if(xacNhan == true){

				xacNhan = xuatTTKhachHang(maCB, maGhe, name, cmnd, gioiTinh, ListCB);

				if(xacNhan == true){
					break;
				}
				if(xacNhan == false){
					system("cls");
					return false;
				}				
			}
			name = "";
		}
		else {
			name = "";
			break;
		}
	}
	while(true){
		if(name != ""){
			break;
		}
		ChangeColor(10);
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(100,13);
		cout << "| Name:                                 | Gioi tinh:       |";
		gotoxy(100,14);
		cout << "------------------------------------------------------------";
		ChangeColor(15);
		gotoxy(108,13);
		name = nhapTenKH();
		if(name == ""){
			system("cls");
			return false;
		}
		ChangeColor(3);

		while(true){
			gotoxy(153,13);
			cout << "      ";
			if(gioiTinh == 0){
				gotoxy(153,13);
				cout << "Nam";
			}
			else if(gioiTinh == 1){
				gotoxy(153,13);
				cout << "Nu";
			}
	
			int check = _getch();
			if(check == 224){
				check = _getch();
				if(check == 77){
					gioiTinh++;
					if(gioiTinh == 2){
						gioiTinh = 0;
					}
				}
				if(check == 75){
					gioiTinh--;
					if(gioiTinh == -1){
						gioiTinh = 1;
					}
				}
			}
			if(check == 13){
				ChangeColor(15);
				gotoxy(153,13);
				cout << "      ";
				if(gioiTinh == 0){
					gotoxy(153,13);
					cout << "Nam";
					break;
				}
				else if(gioiTinh == 1){
					gotoxy(153,13);
					cout << "Nu";
					break;
				}
			}
			else if(check == 27){
				gioiTinh = -1;
				break;
			}		
		}
		if(gioiTinh == -1){
			system("cls");
			return false;
		}
		
		//----------------------------------------
		ChangeColor(15);
		gotoxy(100,18);
		cout << "------------------------------------------------------------";
		gotoxy(100,19);
		cout << "|                    Xac nhan Dat Ve                       |";
		gotoxy(100,20);
		cout << "------------------------------------------------------------";
		gotoxy(100,21);
		cout << "|        Dong Y Dat ve (Y)  |   Khong Dat Ve (N)           |";
		gotoxy(100,22);
		cout << "------------------------------------------------------------";
		gotoxy(100,23);
		cout << "| Ma CB:                    | Noi Den:                     |";
		gotoxy(100,24);
		cout << "------------------------------------------------------------";
		gotoxy(100,25);
		cout << "| Day:                      | Time:                        |";
		gotoxy(100,26);
		cout << "------------------------------------------------------------";
		ChangeColor(6);
		gotoxy(137,19);
		cout << maGhe;
		gotoxy(109, 23);
		cout << p->chuyenBay.maChuyenBay;
		gotoxy(139,23);
		cout << p->chuyenBay.diemDen;
		gotoxy(107,25);
		cout << p->chuyenBay.day.dd << "/" << p->chuyenBay.day.mm << "/" << p->chuyenBay.day.yy;
		gotoxy(136,25);
		if(p->chuyenBay.thoiGianKhoiHanh.gio < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.gio << ":";
		if(p->chuyenBay.thoiGianKhoiHanh.phut < 10){
			cout << "0" << p->chuyenBay.thoiGianKhoiHanh.phut;
		}
		else
			cout << p->chuyenBay.thoiGianKhoiHanh.phut;
		char temp = _getch();
		if(temp == 'y' || temp == 'Y'){
			system("cls");
			break;
		}
		else if(temp == 'n' || temp == 'N'){
			system("cls");
			return false;
		}
	}
	TTkhachHang hanhkhach;
	hanhkhach.CMND = cmnd;
	hanhkhach.GioiTinh = gioiTinh;
	hanhkhach.Name = name;
	ThemVaoCayKhachHang(tree, hanhkhach); 
	nodeKhachHang *h = tree.root;

	while (h != NULL){

		cout << h->HanhKhach.CMND;
		if (SoSanhCMND(h->HanhKhach.CMND, cmnd) == 1){
			h = h->left;
		}
		else{
			if (SoSanhCMND(h->HanhKhach.CMND, cmnd) == -1){ 
				h = h->right; // Du lieu can nhap vao lon hon data tai p
			}
			else{
				break;
			}
		}							
	}

	cacChuyenBay *q = ListCB.Head;
	while(q!= NULL){
		if (q->chuyenBay.maChuyenBay == maCB){
			q->chuyenBay.Ve[viTriSo].HanhKhach = h;
			break;
		}
		q = q->next;
	}
	for(int i = 0; i < q->chuyenBay.soCho; i++){
		if(q->chuyenBay.Ve[i].HanhKhach == NULL){
			break;
		}
		if(i == q->chuyenBay.soCho-1){
			q->chuyenBay.trangThai = 2;
		}
	}
	return true;
}

bool suaCB(CDanhSachMB& listMB, ListChuyenBay& listCB, string maCB){
	cacChuyenBay *p = listCB.Head;
	string tempMaCB = "";
	int tempDay = 1, tempMonth = 1, tempYear = 1, tempHour = 1, tempMin = 1, trangThai = 1;
	string noiDen = "";
	string soHieu = "";
	int viTri = 0;
	short x = wherex();
	short y = wherey();
	while(p != NULL){
		if(p->chuyenBay.maChuyenBay == maCB){
			tempMaCB = p->chuyenBay.maChuyenBay;
			tempDay = p->chuyenBay.day.dd;
			tempMonth = p->chuyenBay.day.mm;
			tempYear = p->chuyenBay.day.yy;
			tempHour = p->chuyenBay.thoiGianKhoiHanh.gio;
			tempMin = p->chuyenBay.thoiGianKhoiHanh.phut;
			noiDen = p->chuyenBay.diemDen;
			soHieu = p->chuyenBay.soHieuMB;
			trangThai = p->chuyenBay.trangThai;
			break;
		}
		p = p->next;
	}
	if(p == NULL){
		ChangeColor(12);
		gotoxy(x, y+2);
		cout << "Ma chuyen bay khong ton tai!";
		Sleep(800);
		gotoxy(x,y+2);
		cout << "                            ";
		return false;
	}
	xoaManHinh();
	InDanhSachChuyenBay(listCB);
	xuatNhapCB();
	gotoxy(121,0);
	cout << "| Trang Thai:                   |";
	ChangeColor(15);
	if(trangThai == 1){
		gotoxy(135,0);
		cout << "Con ve";		
	}
	if(trangThai == 2){
		gotoxy(135,0);
		cout << "Het Ve";
	}
	if(trangThai == 0){
		gotoxy(135,0);
		cout << "Huy Chuyen";
	}
	if(trangThai == 3){
		gotoxy(135,0);
		cout << "Hoan Thanh";
	}
	
	gotoxy(121, 2);
	cout << tempMaCB;
	gotoxy(127,4);
	if(tempDay < 10){
		cout << "0" << tempDay;
	}
	else cout << tempDay;
	
	gotoxy(136,4);
	if(tempMonth < 10){
		cout << "0" << tempMonth;
	}
	else cout << tempMonth;
	
	gotoxy(145,4);
	cout << tempYear;
	gotoxy(132,6);
	if(tempHour < 10){
		cout << "0" << tempHour;
	}
	else cout << tempHour;
	
	gotoxy(141,6);
	if(tempMin < 10){
		cout << "0" << tempMin << " ";
	}
	else cout << tempMin << " ";
	
	gotoxy(121,8);
	cout << noiDen;
	
	gotoxy(121,10);
	cout << soHieu; 
	
	//hieuChinh_TrangThai
	checkCB:
	int trangThai1 = trangThai;
	while(true){
		ChangeColor(15);
		gotoxy(135,0);
		cout << "           ";
		gotoxy(135,0);
		trangThai1 = suaTrangThai(trangThai1);
		if(trangThai1 == -1){
			system("cls");
			return false;
		}
		if(trangThai1 == trangThai){
			trangThai = trangThai1;
			break;
		}
		if(trangThai1 == -2){
			trangThai1 = trangThai;
		}
		else{
			trangThai = trangThai1;
			break;
		}	
	}
	
//hieuChinh_ngay
	bool checkMonth = false, checkYear = true;
	int tempDay1 = tempDay;
	day:
	while (true){
		ChangeColor(15);
		gotoxy(127,4);
		cout << "  ";
		gotoxy(127,4);
		cout << tempDay1;
		tempDay1 = nhapSoCB(tempDay1);	
		if(tempDay1 == -1){
			cout << "1 ";
			if(luuDL()==true){
				cout << "2 ";
				if(trangThai==1||trangThai==2){
					if(checkThoiGian(tempHour, tempMin, tempDay,tempMonth,tempYear)==false){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						tempDay1=tempDay;
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						system("cls");
						return true;
					}
				}
				else if(trangThai==3){
					if(checkThoiGianBay(tempHour, tempMin, tempDay,tempMonth,tempYear)==true){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Chua den gio khoi hanh!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						system("cls");
						return true;
					}
				}
				else{
					p->chuyenBay.trangThai=trangThai;
					system("cls");
					return true;
				}				
			}	
			else{
				system("cls");
				return false;
			}
		}
		if(tempDay1 == tempDay){
			break;
		}
		if(tempDay1 > 31 || tempDay1 < 1){
			if(tempDay1 == 0){
				gotoxy(127,4);
				cout << "0" << tempDay1;
			}
			ChangeColor(12);
			gotoxy(155,4);
			cout << "Vui long nhap tu [01;31]";
			Sleep(800);
			gotoxy(155,4);
			cout << "                        ";
		}
		if(tempDay1 <= 31 && tempDay1 >=1){
			if(tempDay1 < 10 && tempDay >= 1){
				gotoxy(127,4);
				cout << "0" << tempDay1;
			}
			tempDay = tempDay1;
			break;
		}
	}
	//hieuChinh_thang
	int tempMonth1 = tempMonth;
	while(true){
		ChangeColor(15);
		gotoxy(136,4);
		cout << "  ";
		gotoxy(136,4);
		cout << tempMonth1;
		tempMonth1 = nhapSoCB(tempMonth1);
		if(tempMonth1 == -1){
			if(luuDL()==true){
				if(trangThai==1||trangThai==2){
					if(checkThoiGian(tempHour, tempMin, tempDay1,tempMonth,tempYear)==false){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						tempMonth1=tempMonth;
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						system("cls");
						return true;
					}
				}
				else if(trangThai==3){
					
					if(checkThoiGianBay(tempHour, tempMin, tempDay1,tempMonth,tempYear)==true){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Chua den gio khoi hanh!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						system("cls");
						return true;
					}
				}
				else{
					p->chuyenBay.trangThai=trangThai;
					p->chuyenBay.day.dd = tempDay1;
					system("cls");
					return true;
				}				
			}	
			else{
				system("cls");
				return false;
			}
		}
		if(tempMonth1 > 12 || tempMonth1 < 1){
			ChangeColor(12);
			gotoxy(155,4);
			cout << "Vui long nhap trong [01;12]";
			Sleep(800);
			gotoxy(155,4);
			cout << "                              ";			
		}
		if(tempMonth1 <= 12 && tempMonth1 >= 1){
			if(tempMonth1 == 2 && checkYear == true){
				if(tempDay1 > 29){
					ChangeColor(12);
					gotoxy(155,4);
					cout << "Ngay khong hop le!";
					Sleep(800);
					gotoxy(155,4);
					cout << "                  ";
					gotoxy(155,4);
					cout << "Nhap ngay trong khoang [01;29]";
					Sleep(800);
					gotoxy(155,4);
					cout << "                              ";
					tempMonth = tempMonth1;
					goto day;
				}
				else{
					if(tempMonth1 < 10 && tempMonth >= 1){
						gotoxy(136,4);
						cout << "0" << tempMonth1;
					}
					tempMonth = tempMonth1;
					break;
				}
			}
			if(tempMonth1 == 2 && checkYear == false){
				if(tempDay1 > 28){
					ChangeColor(12);
					gotoxy(155,4);
					cout << "Ngay khong hop le!";
					Sleep(800);
					gotoxy(155,4);
					cout << "                  ";
					gotoxy(155,4);
					cout << "Nhap ngay trong khoang [01;28]";
					Sleep(800);
					gotoxy(155,4);
					cout << "                              ";
					tempMonth = tempMonth1;
					goto day;
				}
				else{
					if(tempMonth1 < 10 && tempMonth >= 1){
						gotoxy(136,4);
						cout << "0" << tempMonth1;
					}
					tempMonth = tempMonth1;
					break;
				}
			}
			if(tempMonth1 != 2){
				if(tempMonth1 < 10 && tempMonth >= 1){
					gotoxy(136,4);
					cout << "0" << tempMonth1;
				}
				tempMonth = tempMonth1;
				break;				
			}			
		}	
	}
	//Nhap_nam
	int tempYear1 = tempYear;
	while(true){
		ChangeColor(15);
		gotoxy(145,4);
		cout << "    ";
		gotoxy(145,4);
		cout << tempYear1;
		tempYear1 = suaNhapSo(tempYear1);
		if(tempYear1 == -1){
			if(luuDL()==true){
				if(trangThai==1||trangThai==2){
					if(checkThoiGian(tempHour, tempMin, tempDay1,tempMonth1,tempYear)==false){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						tempYear1=tempYear;
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						system("cls");
						return true;
					}
				}
				else if(trangThai==3){
					
					if(checkThoiGianBay(tempHour, tempMin, tempDay1,tempMonth1,tempYear)==true){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Chua den gio khoi hanh!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						system("cls");
						return true;
					}
				}
				else{
					p->chuyenBay.trangThai=trangThai;
					p->chuyenBay.day.dd = tempDay1;
					p->chuyenBay.day.mm = tempMonth1;
					system("cls");
					return true;
				}				
			}	
			else{
				system("cls");
				return false;
			}
		}
		if(tempYear1 > 2027 || tempYear1 < 2023){
			ChangeColor(12);
			gotoxy(155,4);
			cout << "Vui long nhap trong [2023;2027]";
			Sleep(900);
			gotoxy(155,4);
			cout << "                               ";
		}
		if(tempYear1 >= 2023 && tempYear1 <= 2027){
			if(checkYearNhuan(tempYear1) == false && tempMonth1 == 2 && tempDay1 == 29){
				ChangeColor(12);
				gotoxy(155,4);
				cout << "Nam nay thang 2 co 28 ngay!";
				Sleep(900);
				gotoxy(155,4);
				cout << "                           ";
				checkYear = false;
				tempYear = tempYear1;
				goto day;
			}
			tempYear = tempYear1;
			break;			
		}
	}
//hieuChinh_Hour
	int tempHour1 = tempHour;
	while(true){
		ChangeColor(15);
		gotoxy(132,6);
		cout << "  ";
		gotoxy(132,6);
		cout << tempHour1;
		tempHour1 = nhapSoCB(tempHour1);
		if(tempHour1 == -1){
			if(luuDL()==true){
				if(trangThai==1||trangThai==2){
					if(checkThoiGian(tempHour, tempMin, tempDay1,tempMonth1,tempYear1)==false){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						tempYear1=tempYear;
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						p->chuyenBay.day.yy = tempYear1;
						system("cls");
						return true;
					}
				}
				else if(trangThai==3){
					
					if(checkThoiGianBay(tempHour, tempMin, tempDay1,tempMonth,tempYear1)==true){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Chua den gio khoi hanh!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						p->chuyenBay.day.yy = tempYear1;
						system("cls");
						return true;
					}
				}
				else{
					p->chuyenBay.trangThai=trangThai;
					p->chuyenBay.day.dd = tempDay1;
					p->chuyenBay.day.mm = tempMonth1;
					p->chuyenBay.day.yy = tempYear1;
					system("cls");
					return true;	
				}				
			}	
			else{
				system("cls");
				return false;
			}
		}
		if(tempHour1 > 23 || tempHour1 < 0){
			ChangeColor(12);
			gotoxy(155,6);
			cout << "Vui long nhap trong [00;23]";
			Sleep(800);
			gotoxy(155,6);
			cout << "                           ";
		}
		else if(tempHour1 <= 23 && tempHour1 >= 0){
			if(tempHour1>=0 && tempHour1<=9){
				gotoxy(132,6);
				cout << "0" << tempHour1;
				tempHour=tempHour1;
				break;
			}
			else if(tempHour1 > 9){
				tempHour=tempHour1;
				break;
			}
		}
	}
//hieuChinh_phut
	int tempMin1 = tempMin;
	while(true){
		ChangeColor(15);
		gotoxy(141,6);
		cout << "  ";
		gotoxy(141,6);
		cout << tempMin1;
		tempMin1 = nhapSoCB(tempMin1);
		if(tempMin1 == -1){
			if(luuDL()==true){
				if(trangThai==1||trangThai==2){
					if(checkThoiGian(tempHour1, tempMin, tempDay1,tempMonth1,tempYear1)==false){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						tempYear1=tempYear;
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						p->chuyenBay.day.yy = tempYear1;
						p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
						system("cls");
						return true;
					}
				}
				else if(trangThai==3){
					
					if(checkThoiGianBay(tempHour1, tempMin, tempDay1,tempMonth1,tempYear1)==true){
						ChangeColor(12);
						gotoxy(155,6);
						cout<<"Chua den gio khoi hanh!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                                        ";
						gotoxy(155,6);
						cout<<"Vui long nhap lai thoi gian!";
						Sleep(1000);
						gotoxy(155,6);
						cout<<"                            ";
						goto checkCB;
					}
					else{
						p->chuyenBay.trangThai=trangThai;
						p->chuyenBay.day.dd = tempDay1;
						p->chuyenBay.day.mm = tempMonth1;
						p->chuyenBay.day.yy = tempYear1;
						p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
						system("cls");
						return true;
					}
				}
				else{
					p->chuyenBay.trangThai=trangThai;
					p->chuyenBay.day.dd = tempDay1;
					p->chuyenBay.day.mm = tempMonth1;
					p->chuyenBay.day.yy = tempYear1;
					p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
					system("cls");
					return true;	
				}				
			}	
			else{
				system("cls");
				return false;
			}
		}
		if(tempMin1 < 0 || tempMin1 >59){
			ChangeColor(12);
			gotoxy(155,6);
			cout << "Vui long nhap trong [00;59]";
			Sleep(800);
			gotoxy(155,6);
			cout << "                           ";			
		}
		else if(tempMin1 <= 59 && tempMin1 >= 0){
			if(tempMin1 <=9 && tempMin1 >= 0){
				gotoxy(141,6);
				cout << "0" << tempMin1;
				tempMin=tempMin1;
				break;
			}
			else if(tempMin1 > 9){
				tempMin=tempMin1;
				break;
			}
		}
	}
	if(trangThai1==1||trangThai1==2){
		if(checkThoiGian(tempHour1, tempMin1, tempDay1,tempMonth1,tempYear1)==false){
			ChangeColor(12);
			gotoxy(155,6);
			cout<<"Thoi gian khoi hanh toi thieu sau 3 gio!";
			Sleep(1000);
			gotoxy(155,6);
			cout<<"                                        ";
			gotoxy(155,6);
			cout<<"Vui long nhap lai thoi gian!";
			Sleep(1000);
			gotoxy(155,6);
			cout<<"                            ";
			goto checkCB;
		}
	}
	if(trangThai1==3){
		if(checkThoiGianBay(tempHour1, tempMin1, tempDay1,tempMonth1,tempYear1)==true){
			ChangeColor(12);
			gotoxy(155,6);
			cout<<"Chua den gio khoi hanh!";
			Sleep(1000);
			gotoxy(155,6);
			cout<<"                                        ";
			gotoxy(155,6);
			cout<<"Vui long nhap lai thoi gian!";
			Sleep(1000);
			gotoxy(155,6);
			cout<<"                            ";
			goto checkCB;
		}
	}	

	//chinh noi den
	string noiDen1= noiDen;
	nameNoiDen diaDiem;
	while(true){
		xuatNoiDen();
		ChangeColor(15);
		gotoxy(121,8);
		cout<<"           ";
		gotoxy(121,8);
		cout<<noiDen1;
		noiDen1= suaDLMB(noiDen1);
		if(noiDen1==""){
			if(luuDL() == true){
				p->chuyenBay.trangThai=trangThai;
				p->chuyenBay.day.dd = tempDay1;
				p->chuyenBay.day.mm = tempMonth1;
				p->chuyenBay.day.yy = tempYear1;
				p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
				p->chuyenBay.thoiGianKhoiHanh.phut = tempMin1;
				system("cls");
				return true;
			}
			else {
				system("cls");
				return false;
			}
		}
		if(checkNoiDen(diaDiem, noiDen1)==false){
			ChangeColor(12);
			gotoxy(155,8);
			cout<<"Dia diem hien chua cap nhat!";
			Sleep(800);
			cout<<"                            ";
		}
		else{
			noiDen = noiDen1;
			xoaNoiDen();
			break;
		}
	}
	
	//chinh so hieu 
	string soHieu1 = soHieu;
	while(true){
		xuatSoHieu(listMB);
		ChangeColor(15);
		gotoxy(121,10);
		cout<<"           ";
		gotoxy(121,10);
		cout<<soHieu1;
		soHieu1=suaDLMB(soHieu1);
		if(soHieu1==""){
			if(luuDL() == true){
				p->chuyenBay.trangThai=trangThai;
				p->chuyenBay.day.dd = tempDay1;
				p->chuyenBay.day.mm = tempMonth1;
				p->chuyenBay.day.yy = tempYear1;
				p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
				p->chuyenBay.thoiGianKhoiHanh.phut = tempMin1;
				p->chuyenBay.diemDen = noiDen1;
				system("cls");
				return true;
			}
			else {
				system("cls");
				return false;
			}
		}
		if(checksoHieu(listMB,soHieu1)!=1)	{
			ChangeColor(12);
			gotoxy(155,10);
			cout<<"Ma so hieu khong ton tai!";
			Sleep(800);
			gotoxy(155,10);
			cout<<"                         ";
		}
		else {
			cacChuyenBay *q = listCB.Head;
			while(q != NULL){
				if(q->chuyenBay.soHieuMB == soHieu1 && q->chuyenBay.maChuyenBay != maCB){
					if(trangThai == 1 || trangThai == 2){
						if(q->chuyenBay.day.yy == tempYear1 && q->chuyenBay.day.mm == tempMonth1){
							if(checkTwoTime(q->chuyenBay.thoiGianKhoiHanh.gio, tempHour1, q->chuyenBay.thoiGianKhoiHanh.phut, tempMin1, q->chuyenBay.day.dd, tempDay1) == 1){
								ChangeColor(12);
								gotoxy(155,10);
								cout << "Ma so nay dang co chuyen bay!";
								Sleep(1000);
								gotoxy(155, 10);
								cout << "                             ";
								gotoxy(80, 20);
							    cout << "+---------------------------------------+";
							    gotoxy(80, 21);
							    cout << "| Ban co muon nhap lai Ma so hieu khac? |";
							    gotoxy(80, 22);
							    cout << "+---------------------------------------+";
							    gotoxy(80, 23);
							    cout << "|      [1] Dong Y / [0] Khong Dong Y    |";
							    gotoxy(80, 24);
							    cout << "+---------------------------------------+";
							    anConTro();
							    char dapAn;
							    while(true){
							    	dapAn = _getch();
							    	if(dapAn == 49 || dapAn == 48) break;
								}
							    if(nhapLuaChon(dapAn, 0, 1) == 0){
									gotoxy(80, 20);
							    	cout << "                                         ";
								    gotoxy(80, 21);
								    cout << "                                         ";
								    gotoxy(80, 22);
								    cout << "                                         ";
								    gotoxy(80, 23);
							    	cout << "                                         ";
								    gotoxy(80, 24);
								    cout << "                                         ";
								    hienConTro();
								    gotoxy(155,10);
								    cout << "Vui long nhap lai thoi gian cach 12 tieng!";
								    Sleep(1100);
								    gotoxy(155,10);
								    cout << "                                          ";
								    ChangeColor(15);
									soHieu = soHieu1;
								    goto checkCB;
								}
							    else{
									gotoxy(80, 20);
							    	cout << "                                         ";
								    gotoxy(80, 21);
								    cout << "                                         ";
								    gotoxy(80, 22);
								    cout << "                                         ";
								    gotoxy(80, 23);
							    	cout << "                                         ";
								    gotoxy(80, 24);
								    cout << "                                         ";
								    hienConTro();
								    ChangeColor(15);
							    	break;
								}
							}
						}
					}					
				}
				q = q->next;
			}
			if(q == NULL){
				p->chuyenBay.trangThai=trangThai;
				p->chuyenBay.day.dd = tempDay1;
				p->chuyenBay.day.mm = tempMonth1;
				p->chuyenBay.day.yy = tempYear1;
				p->chuyenBay.thoiGianKhoiHanh.gio = tempHour1;
				p->chuyenBay.thoiGianKhoiHanh.phut = tempMin1;
				p->chuyenBay.diemDen = noiDen1;
				p->chuyenBay.soHieuMB=soHieu1;
				break;			
			}
		}
	}
	return true;
}

bool HuyCB(ListChuyenBay & listCB, string maCB){
	cacChuyenBay *p = listCB.Head;
	while(p!=NULL){
		if(p->chuyenBay.maChuyenBay == maCB){
			if(p->chuyenBay.trangThai == 3){
				ChangeColor(12);
				gotoxy(125,8);
				cout << "Chuyen Bay da hoan thanh!";
				Sleep(800);
				gotoxy(125,8);
				cout << "                         ";
				return false;
			}
			else if(p->chuyenBay.trangThai == 0){
				ChangeColor(12);
				gotoxy(125,8);
				cout << "Chuyen Bay da bi huy truoc do!";
				Sleep(800);
				gotoxy(125,8);
				cout << "                              ";
				return false;				
			}
			else{
				while(true){
					gotoxy(80, 20);
				    cout << "+---------------------------------------+\n";
				    gotoxy(80, 21);
				    cout << "| Ban co muon HUY Chuyen Bay khong ?    |\n";
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
				        p->chuyenBay.trangThai = 0;
						ChangeColor(12);
						gotoxy(125,8);
						cout << "Da Huy Chuyen Bay Thanh Cong! ";
						Sleep(800);
						gotoxy(125,8);
						cout << "                              ";
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
				        ChangeColor(12);
						gotoxy(125,8);
						cout << "Chuyen Bay chua duoc huy! ";
						Sleep(800);
						gotoxy(125,8);
						cout << "                          ";
				        return false;
				    }
				}									
			}
		}
		p = p->next;
	}
	if(p==NULL){
		ChangeColor(12);
		gotoxy(125,8);
		cout << "Ma Chuyen Bay khong ton tai!";
		Sleep(800);
		gotoxy(125,8);
		cout << "                              ";
		return false;		
	}
}

bool suaMayBay(CDanhSachMB& dsMayBay, ListChuyenBay& list, string soHieu) {
	xoaManHinh();
	short x = wherex();
    short y = wherey();
	cacChuyenBay *q = list.Head;
	for(q; q != NULL; q = q->next){
		if(q->chuyenBay.soHieuMB == soHieu){
			if (q->chuyenBay.trangThai == 1 || q->chuyenBay.trangThai == 2){
	        	gotoxy(50,20);
	    		ChangeColor(12);
	        	cout << "Khong the xoa may bay nay dang co chuyen!";
	        	Sleep(900);
	        	return false;
	        }	
			break;		
		}

	}
    string tempSoHieu;
    string tempLoaiMB;
    int tempSoDay;
    int tempSoHang;
    int tempSoCho;
    int viTri = -1;

    for (int i = 0; i < dsMayBay.slMB; i++){
        if (dsMayBay.danhSachMB[i]->soHieu == soHieu) {
            tempSoHieu = dsMayBay.danhSachMB[i]->soHieu;
            tempLoaiMB = dsMayBay.danhSachMB[i]->loaiMayBay;
            tempSoDay = dsMayBay.danhSachMB[i]->soDay;
            tempSoHang = dsMayBay.danhSachMB[i]->soHang;
            tempSoCho = dsMayBay.danhSachMB[i]->soCho;
            viTri = i;
            break;
        }
    }
	if(viTri == -1){
        gotoxy(x, y + 2);
        ChangeColor(12);
        cout << "Khong tim thay may bay can thay doi!!";
        return false;
	}
	//In thong tin 
    gotoxy(0, 0);
    xuatNhapMB();
    gotoxy(20, 2);
    cout << tempSoHieu;
    short xSoHieu = wherex();

    gotoxy(20, 3);
    cout << tempLoaiMB;
    short xLoaiMB = wherex();

    gotoxy(20, 4);
    cout << tempSoDay;
    short xSoDay = wherex();

    gotoxy(20, 5);
    cout << tempSoHang;
    short xSoHang = wherex();
    //----------------------------------------  
    gotoxy(xLoaiMB,3);
    string tempLoaiMB1 = suaDLMB(tempLoaiMB);
    if(tempLoaiMB1 == ""){
    	dsMayBay.danhSachMB[viTri]->loaiMayBay = tempLoaiMB;
		dsMayBay.danhSachMB[viTri]->soDay = tempSoDay;
		dsMayBay.danhSachMB[viTri]->soHang =tempSoHang;  
    	return true;
	}
    dsMayBay.danhSachMB[viTri]->loaiMayBay = tempLoaiMB1;
    
	int tempSoDay1 = tempSoDay;
    while(1){
	    gotoxy(xSoDay,4);
	    tempSoDay1 = suaNhapSo(tempSoDay1);
	    xSoDay = wherex();
	    if(tempSoDay1 == -1){
			dsMayBay.danhSachMB[viTri]->soDay = tempSoDay;
			dsMayBay.danhSachMB[viTri]->soHang =tempSoHang;	
			return true;
		}
		if(tempSoDay1 > 6 || tempSoDay1 < 4){
			gotoxy(xSoDay + 35, 4);
			ChangeColor(12);
			cout << "Vui long nhap trong [4;6]";
			Sleep(800);
			gotoxy(xSoDay + 35, 4);
			cout << "                         ";
			gotoxy(xSoDay, 4);
			ChangeColor(2);
		}   
		if (tempSoDay1 >= 4 && tempSoDay1 <= 6) break;	
	}
    dsMayBay.danhSachMB[viTri]->soDay = tempSoDay1;
    tempSoCho = tempSoDay1 * tempSoHang;

	int tempSoHang1  = tempSoHang;  
    while(1){
	    gotoxy(xSoHang, 5);
	    tempSoHang1 = suaNhapSo(tempSoHang1);
	    xSoHang = wherex();
	    if(tempSoHang1 == -1){
			dsMayBay.danhSachMB[viTri]->soHang =tempSoHang; 
			dsMayBay.danhSachMB[viTri]->soCho = tempSoCho;
			return true;   	
		}
		if(tempSoHang1 < 5 || tempSoHang1 > 300 / tempSoDay1){
			gotoxy(xSoDay + 35, 5);
			ChangeColor(12);
			cout << "Vui long nhap trong [5;" << 300 / tempSoDay1 << "]" ;
			Sleep(800);
			gotoxy(xSoDay + 35, 5);
			cout << "                           ";
			gotoxy(xSoDay, 5);
			ChangeColor(2);			
		} 
		if(tempSoHang1 > 4 && tempSoHang1 <= 300 / tempSoDay1)	break;
	}
    dsMayBay.danhSachMB[viTri]->soHang =tempSoHang1;  
	tempSoCho = tempSoDay1 * tempSoHang1;
	dsMayBay.danhSachMB[viTri]->soCho = tempSoCho;
    return true;
}

int themMayBay( CDanhSachMB& DanhSachMB) {
    if (DanhSachMB.slMB >= MAX_SO_LUONG_MB) {
        cout << "Danh sach may bay da day. Khong the them may bay moi." << endl;
        return -1;
    }
    else {
        DanhSachMB.slMB++;
        DanhSachMB.danhSachMB[DanhSachMB.slMB - 1] = DanhSachMB.creatMB();
        
        if (veKhungNhapThongTin(DanhSachMB.danhSachMB[DanhSachMB.slMB -1], DanhSachMB) == -1) {
            delete DanhSachMB.danhSachMB[DanhSachMB.slMB - 1];
            DanhSachMB.slMB--;
            gotoxy(15, 7);
            cout << "Da huy bo qua trinh nhap!" << endl;
            Sleep(500);
            system("cls");
            return -1;
        }
    }
    return 0;
}

void InDanhSachMB(CDanhSachMB danhSachMB) {
    cout << "   --------------------------------------------------------------------" << endl;
    cout << "                       DANH SACH MAY BAY" << endl;
    cout << "   --------------------------------------------------------------------" << endl;
    cout << "   STT  So hieu\t\tLoai may bay\t\tSo day\tSo hang\tSo cho" << endl;
	for(int i = 1; i <= danhSachMB.slMB; i++){
		gotoxy(4,i+3);
		cout << i;
	}
	for(int i = 0; i < danhSachMB.slMB; i++){
		gotoxy(8,i+4);
		cout << danhSachMB.danhSachMB[i]->soHieu;
	}
	for(int i = 0; i < danhSachMB.slMB; i++){
		gotoxy(24,i+4);
		cout << danhSachMB.danhSachMB[i]->loaiMayBay;
	}
	for(int i = 0; i < danhSachMB.slMB; i++){
		gotoxy(50,i+4);
		cout << danhSachMB.danhSachMB[i]->soDay;
	}
	for(int i = 0; i < danhSachMB.slMB; i++){
		gotoxy(59,i+4);
		cout << danhSachMB.danhSachMB[i]->soHang;
	}
	for(int i = 0; i < danhSachMB.slMB; i++){
		gotoxy(66,i+4);
		cout << danhSachMB.danhSachMB[i]->soCho;
	}
    cout << "\n   --------------------------------------------------------------------" << endl;
}

bool dsCBNgay(short &dd, short &mm, short &yy, string &diemDen){
	ChangeColor(10);
    gotoxy(50,10);
    cout << "------------------------------------------------------------------------";
    gotoxy(50,11);
    cout << "| Ngay:       | Thang:       | Nam:         | Noi den:                 |";
    gotoxy(50,12);
    cout << "------------------------------------------------------------------------";
   	ChangeColor(7);
	gotoxy(59,11);
    cout << "dd";
    gotoxy(74,11);
    cout << "mm";
    gotoxy(87,11);
    cout << "yyyy";
    gotoxy(106,11);
    cout << "XXXXXXXXXX";
    ChangeColor(15);
    short x , y;
	//Ngay_khoi_hanh
	loopday:
	x = 59, y = 11;
	int checkMonth = 1;
	bool checkYear = true;//nam nhuan 
	do {
		gotoxy(x,y);
		cout << "  ";
		ChangeColor(15);
		gotoxy(x,y);
		cout << dd;
		dd = nhapSoCB(dd);
		if(dd == -1){
			system("cls");
			mm = -1, yy = -1;
			return false;
		}
		if(checkMonth != 2){
				if(dd < 1 || dd >31) {
					gotoxy(50,9);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;31]";
					Sleep(500);
					gotoxy(50,9);
					cout << "                         ";
					gotoxy(x,y);
				}
				if(dd >= 1 && dd <= 31) break;						
		}
		else{
			if(checkYear == false){
				if(dd < 1 || dd >28) {
					gotoxy(50,9);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;28]";
					Sleep(500);
					gotoxy(50,9);
					cout << "                         ";
					gotoxy(x,y);
					checkMonth = 2;
				}
				if(dd >= 1 && dd <= 28) break;
			}
			if(checkYear == true){
				if(dd < 1 || dd >29) {
					gotoxy(50,9);
					ChangeColor(12);
					cout << "Nhap trong pham vi [1;29]";
					Sleep(500);
					gotoxy(50,9);
					cout << "                         ";
					gotoxy(x,y);
					checkMonth = 2;
				}
				if(dd >= 1 && dd <= 29) break;			
			} 			
		}
	}while(true);

	//nhap_Thang
	x = 74, y = 11; 
	while(checkMonth != 2){
		ChangeColor(15);
		gotoxy(x,y);
		cout << "  ";
		gotoxy(x,y);
		cout << mm;
		mm = nhapSoCB(mm);
		if(mm == -1){
			system("cls");
			dd = -1, yy = -1;
			return false;		
		}
		if(mm < 1 || mm > 12){
			gotoxy(74,9);
				ChangeColor(12);
				cout << "Nhap trong pham vi [1;12]";
				Sleep(500);
				gotoxy(74,9);
				cout << "                         ";
				gotoxy(x,y);
		}
		if(mm >= 1 && mm <= 12){
			if(dd > 29 && mm == 2 && checkYear == true){
				ChangeColor(12);
				gotoxy(74,9);
				cout << "Thang 2 chi co 29 ngay";
				gotoxy(74,9);
				Sleep(500);
				cout << "                      ";
				gotoxy(74,9);
				cout << "Vui long nhap lai ngay khoi hanh!";
				gotoxy(74,9);
				Sleep(500);
				cout << "                                 ";
				checkMonth = 2;
				goto loopday;
			}
			break;
		}
	}
	//Nam khoi hanh
	x = 87, y = 11;
	do{
		ChangeColor(15);
		gotoxy(x,y);
		cout << "    ";
		gotoxy(x,y);
		cout << yy;
		yy = suaNhapSo(yy);
		if(yy == -1){
			system("cls"); 
			dd = -1, mm = -1;
			return false;
		}
		if(yy < 2023 || yy > 2027){
			ChangeColor(12);
			gotoxy(87,9);
			cout << "Nhap trong pham vi [2023;2027]";// 5 nam
			gotoxy(87,9);
			Sleep(500);
			cout << "                              ";
		}
		if(yy >= 2023 && yy <= 2027){
			checkYear = checkYearNhuan(yy);
			if(mm == 2){
				if(checkYear == true){
					if(dd > 29){
						ChangeColor(12);
						gotoxy(87,9);
						cout << "Thang 2 chi co 29 ngay";
						gotoxy(87,9);
						Sleep(500);
						cout << "                      ";
						gotoxy(87,9);
						cout << "Vui long nhap lai ngay khoi hanh!";
						gotoxy(87,9);
						Sleep(500);
						cout << "                                 ";
						checkMonth = 2;
						goto loopday;				
					}
					else break;					
				}
				else{
					if(dd > 28){
						ChangeColor(12);
						gotoxy(87,9);
						cout << "Thang 2 chi co 28 ngay";
						gotoxy(87,9);
						Sleep(500);
						cout << "                      ";
						gotoxy(87,9);
						cout << "Vui long nhap lai ngay khoi hanh!";
						gotoxy(87,9);
						Sleep(500);
						cout << "                                 ";
						checkMonth = 2;
						checkYear = false;
						goto loopday;				
					}				
					else break;	
				}		
			}
			else break;
		}	
	}while(true);
	/// noi den	
	x = 106, y = 11;
	xuatNoiDen();
	nameNoiDen name;
	while(true){
		gotoxy(x,y);
		cout << "          ";
		gotoxy(x,y);
		if(diemDen != ""){
			cout << diemDen;
		}
		ChangeColor(15);
		diemDen = suaDLMB(diemDen);
		if(diemDen.length() == 0){
	    	system("cls");
	    	return false;
		}
		if(checkNoiDen(name, diemDen) == false){
			ChangeColor(12);
			gotoxy(106, 9);
			cout << "Noi nay hien chua cap nhat!";
			Sleep(1000);
			gotoxy(106,9);
			cout << "                           ";
			gotoxy(x,y);
			cout << "                           ";
			diemDen = "";
		}
		else break;
	}
	xoaNoiDen();
	return true;	
}

void xuatDSHanhKhach(ListChuyenBay &ListCB ){
	cacChuyenBay* p = ListCB.Head;
	
	string maCb = "";
	bool check = true;
	while(check){
		InDanhSachChuyenBay(ListCB);
		ChangeColor(10);
		gotoxy(100,10);
	    cout << "------------------------------------------------------------";
		gotoxy(100,11);
		cout << "| Nhap ma chuyen bay :                                     |";
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(125,11);
		maCb = nhapDLMB();
		if(maCb == ""){
			system("cls");
			return;
		}
		while(p != NULL){
			if( p->chuyenBay.maChuyenBay == maCb){
				check = false;
				break;
			}
			p = p->next;
		}
		if(p == NULL){
			ChangeColor(12);
			short x = wherex();
			cout << "Ma chuyen bay khong ton tai!";
		}		
	}
	
	system("cls");
	ChangeColor(10);
	gotoxy(75,10);
	cout << "DANH SACH HANH KHACH CUNG MOT CHUYEN BAY : " ;
	ChangeColor(15);
	cout << maCb;
	ChangeColor(10);
	gotoxy(75,11);
	cout << "Ngay khoi hanh: ";
	ChangeColor(15);
	if(p->chuyenBay.day.dd < 10){
		cout << "0" << p->chuyenBay.day.dd << "/";
	}
	else 
		cout << p->chuyenBay.day.dd << "/";
	if(p->chuyenBay.day.mm < 10){
		cout << "0" << p->chuyenBay.day.mm << "/";
	}
	else
		cout << p->chuyenBay.day.mm << "/";
	cout << p->chuyenBay.day.yy<<" " ;
	ChangeColor(10);
	cout << "Noi den: "; 
	ChangeColor(15);
	cout << p->chuyenBay.diemDen;
	int sl = 0, soCho = p->chuyenBay.soCho ;
	int soHang = p->chuyenBay.soHang;
	int soDay = p->chuyenBay.soDay;
	string dsVEdadat[soCho] ={};
	string cmnd[soCho];
	string hoten[soCho];
	string doiName ="";
	short gioiTinh[soCho];
	for(int i = 0; i < soCho; i++){
		if(p->chuyenBay.Ve[i].HanhKhach != NULL){
			dsVEdadat[sl] = num2str(i,soHang);
			doiName = p->chuyenBay.Ve[i].HanhKhach->HanhKhach.Name; 
			for(int n = 0;n < doiName.length(); n++){
				if(doiName[n] == '0'){
					doiName[n] = ' ';
				}
			}
			cmnd[sl] = p->chuyenBay.Ve[i].HanhKhach->HanhKhach.CMND;
			hoten[sl] = doiName;
			gioiTinh[sl] = p->chuyenBay.Ve[i].HanhKhach->HanhKhach.GioiTinh;
			sl++;	
		}
			
	}
	
	if(sl == 0){
		gotoxy(75,25);
		cout << "Chuyen bay khong co khach!";
		return;
	}
	ChangeColor(10);
	gotoxy(50,13);
	cout << "+----------------------------------------------------------------------------------------+";
	gotoxy(50,14);
	cout << "|  STT  |    SO VE    |       CMND       |           HO VA TEN           |   GIOI TINH   |";
	gotoxy(50,15);
	cout << "|----------------------------------------------------------------------------------------|";
	int k = 0;
	for(k ; k < sl ; k++){
		gotoxy(50,16 + k);
		ChangeColor(10);
		cout << "|       |             |                  |                               |               |";
		gotoxy(54, 16 + k);
		ChangeColor(15);
		cout << k + 1;
		gotoxy(64, 16 + k);
		cout << dsVEdadat[k];
		gotoxy(75, 16+k);
		cout << cmnd[k];
		gotoxy(95,16+k);
		cout << hoten[k];
		gotoxy(130,16+k);
		if(gioiTinh[k] == 1)
			cout << "Nu";
		else	
			cout << "Nam";

	}
	ChangeColor(10);
	gotoxy(50,16 + k);
	cout << "+----------------------------------------------------------------------------------------+";
	
	
}

int thongKe(ListChuyenBay &ListCB, string soHieu){
	cacChuyenBay *p = ListCB.Head;
	int sl=0;
	while(p!=NULL){
		if(p->chuyenBay.soHieuMB == soHieu && p->chuyenBay.trangThai == 3){
			sl++;
		}
		p=p->next;
	}
	return sl;
}

void xuatDanhSachVeTrong(ListChuyenBay &ListCB)	{
	cacChuyenBay* p = ListCB.Head;
	string maCb = "";
	bool check = true;
	while(check){
		xoaManHinh();
		InDanhSachChuyenBay(ListCB);
		ChangeColor(10);
		gotoxy(100,10);
	    cout << "------------------------------------------------------------";
		gotoxy(100,11);
		cout << "| Nhap ma chuyen bay :                                     |";
		gotoxy(100,12);
		cout << "------------------------------------------------------------";
		gotoxy(125,11);
		maCb = nhapDLMB();
		if(maCb == ""){
			system("cls");
			return;
		}
		else{
			while(p != NULL){
				if(p->chuyenBay.maChuyenBay == maCb && p->chuyenBay.trangThai == 1){ 
				
					break;
				}
				p = p->next;
			}
			if(p == NULL){
				gotoxy(100,9);
				ChangeColor(12);
				cout << "Khong co ma CB ton tai!";
				Sleep(700);
			}
			else check = false;			
		}
					
	}

	int soCho, soDay, soHang;

	system("cls");
	ChangeColor(10);
	gotoxy(75,10);
	cout << "DANH SACH VE CON TRONG CUA CHUYEN BAY: " << maCb;
	soCho = p->chuyenBay.soCho;
	soDay = p->chuyenBay.soDay;
	soHang = p->chuyenBay.soHang;

	gotoxy(75,12);
	cout << "+";
	for(int i = 1; i < 7*soDay - 2;i++){
		cout <<"-";
	}
	cout << "+";
	
	
	for(int i = 1; i <= soHang; i++){
		gotoxy(75,12+i);
		cout << "|";
		for(int j = 1; j < 7*soDay-2;j++){
			cout <<" ";
		}
		cout<<"|";
	}
	gotoxy(75, 13 +soHang);
	cout << "+";
	for(int i = 1; i < 7*soDay - 2;i++){
		cout <<"-";
	}	
	cout << "+";
	gotoxy(75, 14 + soHang);
	ChangeColor(12);
	cout << "Ve Da Dat";
	gotoxy(75, 15 + soHang);
	ChangeColor(15);
	cout << "Ve Con Trong";
	
	ChangeColor(15);
	int x = 78; int tam = 0;
	for(int i = 0; i < soCho; i++){
		string viTri = num2str(i, soHang);
		if (p->chuyenBay.Ve[i].HanhKhach != NULL ){
			ChangeColor(12);
			gotoxy(x,13+tam);
			cout << viTri;
			ChangeColor(15);
			tam++;
		}
		else{
			gotoxy(x,13+tam);
			cout << viTri;	
			tam++;			
		}	
		if(tam == soHang){
			x = wherex();
			x = x + 3;
			tam = 0;
		}		
	}
	gotoxy(100, 50);
}

void SaveDanhSachMB(CDanhSachMB danhSachMB) {
    ofstream outfile("dsmaybay.txt");//, ios::out | ios::app); // m? file ? ch? d? ghi và thêm vào cu?i file
    if (outfile.is_open()) {
        outfile << danhSachMB.slMB << endl;
        for (int i = 0; i < danhSachMB.slMB - 1; i++) {
            outfile << danhSachMB.danhSachMB[i]->soHieu << " " << danhSachMB.danhSachMB[i]->loaiMayBay << " " 
                << danhSachMB.danhSachMB[i]->soDay << " " << danhSachMB.danhSachMB[i]->soHang << " " << danhSachMB.danhSachMB[i]->soCho << endl;
        }
        outfile << danhSachMB.danhSachMB[danhSachMB.slMB - 1]->soHieu << " " << danhSachMB.danhSachMB[danhSachMB.slMB - 1]->loaiMayBay << " " 
                << danhSachMB.danhSachMB[danhSachMB.slMB - 1]->soDay << " " << danhSachMB.danhSachMB[danhSachMB.slMB - 1]->soHang << " " 
				<< danhSachMB.danhSachMB[danhSachMB.slMB - 1]->soCho;
        outfile.close();
    }
    else {
        cout << "Khong the mo file de ghi du lieu." << endl;
    }
}

void LoadDanhSachMB(CDanhSachMB& danhSachMB) {
    ifstream infile("dsmaybay.txt");
    if (infile.is_open()) {
        int slMB;
        infile >> slMB;
        danhSachMB.slMB = slMB;

        // Ð?c thông tin c?a t?ng máy bay
        for (int i = 0; i < danhSachMB.slMB; i++) {
            MayBay* mb = danhSachMB.creatMB();
            if (mb != NULL) {
                infile >> mb->soHieu >> mb->loaiMayBay >> mb->soDay >> mb->soHang >> mb->soCho;
                danhSachMB.danhSachMB[i] = mb;
            }
        }
        infile.close();
		cout << "Doc Du Lieu Danh Sach May Bay Thanh Cong!!";
		Sleep(800);
		system("cls");
        
    }
    else {
        cout << "Khong the mo file de doc du lieu." << endl;
    }
}

void InsertOrderCB(ListChuyenBay& listCB, ChuyenBay cb) {
    cacChuyenBay* node = new cacChuyenBay;
    node->chuyenBay = cb;
    node->next = NULL;

    // N?u danh sách chua có ph?n t? nào
    if (listCB.Head == NULL) {
        listCB.Head = node;
        listCB.SoLuong++;
        return;
    }
	
    // N?u ph?n t? c?n chèn có mã s? hi?u nh? hon ph?n t? d?u danh sách
    if (cb.maChuyenBay < listCB.Head->chuyenBay.maChuyenBay) {
        node->next = listCB.Head;
        listCB.Head = node;
        listCB.SoLuong++;
        return;	
    }

    // Tìm v? trí chèn
    cacChuyenBay* p = listCB.Head;
    while (p->next != NULL && p->next->chuyenBay.maChuyenBay < cb.maChuyenBay) {
        p = p->next;
    }

    node->next = p->next;
    p->next = node;
    listCB.SoLuong++;
}

int ThemChuyenBay(ListChuyenBay& listCB, CDanhSachMB& listMB) {
    ChuyenBay cb;
    
    if (veKhungTTChuyenBay(&cb, listMB, listCB) == -1) {
        gotoxy(15, 7);
        ChangeColor(12);
        cout << "Da huy bo qua trinh nhap!" << endl;
        Sleep(500);
        system("cls");
        return -1;
    }
    
    else {
    	InsertOrderCB(listCB, cb);
	}
    
    return 0;
}

void LuuDSChuyenBay(ListChuyenBay& chuyenbay, CDanhSachMB &danhsach) {
    ofstream outfile;
    outfile.open("dsChuyenBay.txt");
    cacChuyenBay* q;
    outfile << chuyenbay.SoLuong << endl;
    if(chuyenbay.SoLuong == 0){
    	return;
	}
    for (q = chuyenbay.Head; q->next != NULL; q = q->next)
    {
        outfile << q->chuyenBay.maChuyenBay << " " << q->chuyenBay.soHieuMB << " " << q->chuyenBay.diemDen << " " 
            << q->chuyenBay.thoiGianKhoiHanh.gio << " " << q->chuyenBay.thoiGianKhoiHanh.phut << " " 
            << q->chuyenBay.day.dd << " " << q->chuyenBay.day.mm << " " << q->chuyenBay.day.yy << " " << q->chuyenBay.trangThai << endl;
    }
    outfile << q->chuyenBay.maChuyenBay << " " << q->chuyenBay.soHieuMB << " " << q->chuyenBay.diemDen << " " 
        << q->chuyenBay.thoiGianKhoiHanh.gio << " " << q->chuyenBay.thoiGianKhoiHanh.phut << " " 
        << q->chuyenBay.day.dd << " " << q->chuyenBay.day.mm << " " << q->chuyenBay.day.yy << " " << q->chuyenBay.trangThai;
    outfile.close();
}

void LoadDSChuyenBay(ListChuyenBay& chuyenbay, CDanhSachMB& danhsach) {
    ifstream infile;
    infile.open("dsChuyenBay.txt");
    if (!infile.is_open()) {
        cout << "Khong the mo file dsChuyenBay.txt\n";
        return;
    }
    int n;
    infile >> n;
    chuyenbay.SoLuong = n;
    infile.ignore();
    chuyenbay.Head = chuyenbay.Last = NULL;
    for (int i = 0; i < n; i++) {
        // C?p phát b? nh? cho node m?i
        cacChuyenBay *p = new cacChuyenBay;
        // Ð?c d? li?u vào node m?i
        getline(infile, p->chuyenBay.maChuyenBay, ' ');
        getline(infile, p->chuyenBay.soHieuMB, ' ');
        getline(infile, p->chuyenBay.diemDen, ' ');
        for( int j = 0; j < danhsach.slMB; j++){
        	if (p->chuyenBay.soHieuMB == danhsach.danhSachMB[j]->soHieu) {
	            p->chuyenBay.loaiMayBay = danhsach.danhSachMB[j]->loaiMayBay;
	            p->chuyenBay.soCho = danhsach.danhSachMB[j]->soCho;
	            p->chuyenBay.soDay = danhsach.danhSachMB[j]->soDay;
	            p->chuyenBay.soHang = danhsach.danhSachMB[j]->soHang;
	            p->chuyenBay.TaoDanhSachVe();
       		}	
		}
        infile >> p->chuyenBay.thoiGianKhoiHanh.gio >> p->chuyenBay.thoiGianKhoiHanh.phut >> 
		p->chuyenBay.day.dd >> p->chuyenBay.day.mm >> p->chuyenBay.day.yy >> p->chuyenBay.trangThai;
		
        p->next = NULL;
        // Thêm node m?i vào danh sách liên k?t
        if (chuyenbay.Head == NULL) {
            chuyenbay.Head = chuyenbay.Last = p;
        } else {
            chuyenbay.Last->next = p;
            chuyenbay.Last = p;
        }
        if(checkThoiGianBay(p->chuyenBay.thoiGianKhoiHanh.gio,p->chuyenBay.thoiGianKhoiHanh.phut,p->chuyenBay.day.dd,p->chuyenBay.day.mm,p->chuyenBay.day.yy) == false){
        	p->chuyenBay.trangThai = 3;
		}
        infile.ignore();
    }

    infile.close();
    ChangeColor(12);
    cout << "Doc Du Lieu Danh Sach Chuyen Bay Thanh Cong!!";
    Sleep(800);
    system("cls");
}

void LoadFileKH(treeKhachHang& khachhang, const string& fileName) {
    ifstream infile(fileName);

    if (!infile) {
        cout << "Khong the mo file!" << endl;
        return;
    }
	int soLuong;
    khachhang.root = NULL; // Kh?i t?o cây tìm ki?m nh? phân
	infile >> soLuong;
	khachhang.SoLuong = soLuong;
    for(int i = 1; i <= soLuong; i++){
        string CMND;
        string name;
        short gioiTinh;
		
        infile >> CMND >> name >> gioiTinh;

        // T?o nút m?i ch?a thông tin khách hàng
        nodeKhachHang* newNode = new nodeKhachHang;
        newNode->HanhKhach.CMND = CMND;
        newNode->HanhKhach.Name = name;
        newNode->HanhKhach.GioiTinh = gioiTinh;
        newNode->left = NULL;
        newNode->right = NULL;

        // N?u cây tìm ki?m nh? phân chua có nút nào
        if (i == 1) {
            khachhang.root = newNode;
        }
        else {
            nodeKhachHang* p = khachhang.root;

            while (true) {
                if (SoSanhChuoiSo(CMND, p->HanhKhach.CMND) == 1) { // L?n hon
                    if (p->right == NULL) {
                        p->right = newNode;
                        break;
                    }
                    else {
                        p = p->right;
                    }
                }
                else { // Không c?n tru?ng h?p trùng CMND vì d?c t? file
                    if (p->left == NULL) {
                        p->left = newNode;
                        break;
                    }
                    else {
                        p = p->left;
                    }
                }
            }
        }
    }

    infile.close();
}

void SaveFileVe(ListChuyenBay& chuyenbay, treeKhachHang& khachhang){
	ofstream outfile;
	outfile.open("ve.txt", ios::out);
	for (cacChuyenBay *h = chuyenbay.Head; h != NULL; h = h->next){
		if (h != chuyenbay.Head)
		{
			outfile << "@" << endl;
		}
		
		for (int i = 0; i < h->chuyenBay.soCho; i++)
		{
			if (h->chuyenBay.Ve[i].HanhKhach != NULL)
			{
				string CMND = h->chuyenBay.Ve[i].HanhKhach->HanhKhach.CMND;

				string duongdan = "";
				nodeKhachHang *k = khachhang.root;
				while (k != NULL)
				{
					if (SoSanhCMND(k->HanhKhach.CMND,CMND) == 1)
					{
						k = k->left;
						duongdan = duongdan + '0';
					}
					else
					{
						if (SoSanhCMND(k->HanhKhach.CMND,CMND) == -1)
						{
							k = k->right;
							duongdan = duongdan + '1';
						}
						else
						{
							duongdan = duongdan + '2';
							break;
						}
					}
				}
				outfile << "- " << i+1 << " " << duongdan << endl;
			}
		}
	}
	outfile << "@";
	outfile.close();
}

void LoadFileVE(ListChuyenBay& listCB, treeKhachHang& khachhang){
	ifstream infile; 
	infile.open("ve.txt");
    if (!infile.is_open()) {
        cout << "Khong the mo file ve.txt\n";
        return;
    }	
	cacChuyenBay *t = listCB.Head;
	while (t != NULL)
	{
		char thu;
		infile >> thu;
		if (thu == '-'){
			int soghe;
			string duongdan;
			infile >> soghe;
			infile >> duongdan;
			if(soghe <= t->chuyenBay.soCho){
				nodeKhachHang *kh = khachhang.root;
				for (int i = 0; i < duongdan.length(); i++)
				{
					if (duongdan[i] == '0')
					{
						kh = kh->left;
					}
					else
					{
						if (duongdan[i] == '1')
						{
							kh = kh->right;
						}
						else
						{
							t->chuyenBay.Ve[soghe-1].HanhKhach = kh;
							break;
						}
					}
				}				
			}
		}
		else
		{
			t = t->next;
		}
	}
	infile.close();
	ChangeColor(12);
    cout << "Doc Du Lieu Ve may bay Thanh Cong!!";
    Sleep(800);
    system("cls");
}
#endif
