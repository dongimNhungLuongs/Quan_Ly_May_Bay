#include <iostream>
#include "khoitao.h"
#include "mylib.h"
#include <conio.h>
#include<fstream>
#include <Windows.h>
#include<string>
using namespace std;

int main() {

    fullscreen();
    //=========================Doc Du Lieu Cac May Bay Tu file=================================
    CDanhSachMB danhSachMB;
    ListChuyenBay chuyenbay;
    treeKhachHang khachHang;
    khachHang.root = NULL;
    
    
	LoadDanhSachMB(danhSachMB);
	LoadDSChuyenBay(chuyenbay, danhSachMB);
	LoadFileKH(khachHang, "dsKhachHang.txt");
	LoadFileVE(chuyenbay, khachHang);
    bool check = true;
    while (check) {
    	cout << "Nhan ESC de Thoat chuong trinh QUAN LY MAY BAY!\n\t";
        xuatMenu();
        cout << "                     CHON THAO TAC MUON THUC HIEN";
        inThoiGian();
        char keyMenu = _getch();
        if (keyMenu == 27) {
            check = false;
            xoaManHinh();
            ChangeColor(12);
            LuuDSChuyenBay(chuyenbay, danhSachMB);
            SaveDanhSachMB(danhSachMB);
            cout << "          Nguyen Le Duy Khanh - N21DCDK014                                                                                                                        Dang Dinh Dong - N21DCDK005";
            gotoxy(50,17);
            cout << "------------------------------ DA THOAT KHOI CHUONG TRINH QUAN LY ----------------------------------";
            ChangeColor(5);
            gotoxy(50,19);
            cout << "-------------------------------- CAM ON DA DUNG QUAN LY MAY BAY ------------------------------------";
            ChangeColor(10);
            gotoxy(50,21);
            cout << "------------------------------------- HEN GAP LAI LAN SAU ------------------------------------------";
            ChangeColor(15);
            gotoxy(100,26);
        }
        else {
        	hienConTro();
            switch (nhapLuaChon(keyMenu, 1, 7)) {
            case 1: {
            	
            	bool Esc;
    			string xoa, chinh;
                bool check_1 = true;
                xoaManHinh();
                while (check_1) {
                	InDanhSachMB(danhSachMB);
                    xuatMuc_1();
                    char keyThem = _getch();
                    if (keyThem == 27)
                        check_1 = false;
                    else
                        switch (nhapLuaChon(keyThem, 1, 3)) {
                        case 1:
                            xoaManHinh();
                            int n;
                            cout << " Nhap so may bay:   ";
                            n = nhapSo();
                            xoaManHinh();
                            for(int k = 1; k <= n; k++){
                        		int x = themMayBay(danhSachMB);
                        		if(x != -1){
                            		SaveDanhSachMB(danhSachMB);
                            		gotoxy(15,7);
                            		cout << "Them thanh cong may bay thu: " << k ;
                            		Sleep(1000); 
                            		xoaManHinh();									                       			
								}
								else
									break;
							}
                            break;
                        case 2:
                        	xoaManHinh();
                        	while(1){
                        		ChangeColor(6);
                            	InDanhSachMB(danhSachMB);
                            	gotoxy(100,5);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(100,6);
                            	cout << "| Nhap so hieu muon xoa:                                   |";
                            	gotoxy(100,7);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(125,6);
                            	xoa = nhapDLMB();
                            	if(xoa == ""){
                            		xoaManHinh();
                            		break;
								}
                            	XoaMayBay(danhSachMB, chuyenbay, xoa);     
                            	Sleep(800);
                            	xoaManHinh();								                   		
							}
                            break;
                        case 3:
                        	xoaManHinh();
                        	while(1){
                        		ChangeColor(3);
                            	InDanhSachMB(danhSachMB);
                            	gotoxy(100,5);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(100,6);
                            	cout << "| Nhap so hieu muon sua:                                   |";
                            	gotoxy(100,7);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(125,6);
                            	chinh = nhapDLMB();
                            	if(chinh == ""){
                            		xoaManHinh();
                            		break;
								}
                            	Esc = suaMayBay(danhSachMB, chuyenbay, chinh);  
                            	if(Esc == true) {
                            		SaveDanhSachMB(danhSachMB); 
									xoaAllVe(chuyenbay, chinh); 
									SaveFileVe(chuyenbay, khachHang);
								}
                            	xoaManHinh();								                   		
							}
                            break;
                        }
                }
                xoaManHinh();
                break;
            }

            case 2: {
                bool check_2 = true, esc;
                string hieuChinh, huyCB;
                xoaManHinh();
                while (check_2) {
                	InDanhSachChuyenBay(chuyenbay);
                    xuatMuc_2();
                    char keyCB = _getch();
                    if (keyCB == 27) check_2 = false;
                    else
                        switch (nhapLuaChon(keyCB, 1, 3)) {
                        case 1:
                        	xoaManHinh();
                        	int a;
                        	cout << "So chuyen bay them: ";
							a = nhapSo();
							if(a == 0){
								xoaManHinh();
								break;
							}
							for(int i = 1; i <= a; i++){
								xoaManHinh();
								InDanhSachChuyenBay(chuyenbay);
								int x = ThemChuyenBay(chuyenbay, danhSachMB);
								if(x != -1){
									ChangeColor(12);
									gotoxy(121, 12);
								    cout << "Them thanh cong chuyen bay thu " << i;
								    ChangeColor(15);
									Sleep(800);
	                            	xoaManHinh();									
								}
								else break;
							}
							LuuDSChuyenBay(chuyenbay, danhSachMB);
                            break;
                        case 2:
                            xoaManHinh();
                            while(1){
                            	InDanhSachChuyenBay(chuyenbay);
                            	ChangeColor(3);
                            	gotoxy(100,5);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(100,6);
                            	cout << "| Nhap Ma CB muon sua:                                     |";
                            	gotoxy(100,7);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(125,6);
                            	hieuChinh = nhapDLMB();
                            	if(hieuChinh == ""){
                            		xoaManHinh();
                            		break;
								}
								esc = suaCB(danhSachMB, chuyenbay, hieuChinh);
								if(esc == true){
									LuuDSChuyenBay(chuyenbay, danhSachMB);
								}
								xoaManHinh();
							}
                            break;
                        case 3:
                            xoaManHinh();
                            while(1){
                            	InDanhSachChuyenBay(chuyenbay);
                            	ChangeColor(3);
                            	gotoxy(100,5);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(100,6);
                            	cout << "| Nhap Ma CB muon HUY:                                     |";
                            	gotoxy(100,7);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(125,6);
                            	huyCB = nhapDLMB();
                            	if(huyCB == ""){
                            		xoaManHinh();
                            		break;
								}
								esc = HuyCB(chuyenbay, huyCB);
								if(esc == true){
									LuuDSChuyenBay(chuyenbay, danhSachMB);
								}
								xoaManHinh();
							}
                               
                            break;
                        }
                }
                xoaManHinh();
                break;
            }

            case 3: {
                bool check_3 = true;
                string noiDen, maCB;
                xoaManHinh();
                while (check_3) {
                	bool kiemTra = true;
                    xuatMuc_3();
                    char keyVe = _getch();
                    if (keyVe == 27) check_3 = false;
                    else
                        switch (nhapLuaChon(keyVe,1 , 2)) {
                        case 1:
                        	while(true){
                        		xoaManHinh();
                        		hienConTro();
                        		xuatNoiDen();
                        		ChangeColor(2);
                        		gotoxy(75,10);
                        		cout << "------------------------------------------------------------";
                            	gotoxy(75,11);
                            	cout << "| Nhap Dia Diem den:                                        |";
                            	gotoxy(75,12);
                            	cout << "------------------------------------------------------------";
                            	gotoxy(96,11);
                        		noiDen = nhapDLMB();
                        		if(noiDen == ""){
                        			system("cls");
                        			break;
								}
								xoaNoiDen();
								kiemTra = InDSDatVe(chuyenbay, noiDen, danhSachMB);
								if(kiemTra == true){
									while(true){
										xoaManHinh();
										kiemTra = InDSDatVe(chuyenbay, noiDen, danhSachMB);
										ChangeColor(15);
	                        			gotoxy(100,10);
	             		           		cout << "------------------------------------------------------------";
	                	            	gotoxy(100,11);
	                    	        	cout << "| Nhap CB ban muon di:                                     |";
	                        	    	gotoxy(100,12);
	                            		cout << "------------------------------------------------------------";
	                            		gotoxy(125,11);
	                        			maCB = nhapDLMB();
	                	        		if(maCB == ""){
	            	            			system("cls");
	                    	    			break;
										}
										kiemTra = true;
										if(kiemTra == true ){
											kiemTra = datVe(chuyenbay, khachHang, maCB, noiDen);
											if(kiemTra == true){
												SaveFileVe(chuyenbay, khachHang);
												break;
											}
										}								
									}
								}
							}
                            xoaManHinh();
                            break;
                        case 2:
                        	while(kiemTra){
                        		xoaManHinh();
                        		kiemTra = InDSHuyVE(chuyenbay, danhSachMB, khachHang);
                        		if(kiemTra == false){
                        			break;
								}
								while (true){
									ChangeColor(10);
									gotoxy(100,10);
								    cout << "------------------------------------------------------------";
									gotoxy(100,11);
									cout << "| Nhap ma CB cua khach:                                    |";
									gotoxy(100,12);
									cout << "------------------------------------------------------------";
									gotoxy(125,11);
									maCB = nhapDLMB();
									if(maCB == ""){
										system("cls");
										kiemTra = false;
										break;
									}
									kiemTra = huyVe(chuyenbay, maCB);
									if(kiemTra == true){
										system("cls");
										kiemTra = false;
										SaveFileVe(chuyenbay, khachHang);
										break;
									}
									else{
										system("cls");
										break;
									}
								}
							}
                            xoaManHinh();
                            break;
                        }
                }
                xoaManHinh();
                break;
            }

            case 4: {
                xoaManHinh();
                anConTro();
                xuatDSHanhKhach(chuyenbay);

                if (_getch() == 27) xoaManHinh();
                hienConTro();
                break;
            }

            case 5: {
            	short dd = 1, mm = 1, yy = 2023;
				string diemDen = "";  	
            	while(true){
            		xoaManHinh();
            		dsCBNgay(dd, mm, yy, diemDen);
					anConTro();
					if ((dd == - 1 && mm == -1 && yy == -1) ||(diemDen == "")){
						hienConTro();               		
						break;
					}
					else if(dd != -1 && mm != -1 && yy != -1 && diemDen != ""){
						InDanhSachNgay(chuyenbay, diemDen, dd, mm, yy);
					}
				}               
                xoaManHinh();
                break;
            }

            case 6: {
                xoaManHinh();
                anConTro();
                xuatDanhSachVeTrong(chuyenbay);
                if (_getch()) xoaManHinh();
                hienConTro();
                break;
            }

            case 7:{
                xoaManHinh();
                anConTro();
                gotoxy(75,10);
                cout << "SO LUOT THUC HIEN CHUYEN BAY CUA CAC MAY BAY";
               	ChangeColor(10);
               	gotoxy(75,14); 
				cout << "+-----------------------------------------+";
			  	gotoxy(75,15);
			  	cout << "|                    |                    |";
			  	gotoxy(80,15);
			  	cout << "So Hieu MB";
			  	gotoxy(103,15);
			  	cout << "So Luot";
			  	gotoxy(75,16);
			  	cout << "+-----------------------------------------+";
			  	
			  	int swap[danhSachMB.slMB];
              	for(int  x = 0; x < danhSachMB.slMB; x++){            		
              		gotoxy(75,17 + x);   
					cout << "|                    |                    |";          	
				}
				
				for(int i = 0; i < danhSachMB.slMB; i++){
					swap[i] = thongKe(chuyenbay, danhSachMB.danhSachMB[i]->soHieu)*10+i;
				}
				
				for(int x = 0; x <  danhSachMB.slMB ; x++){
					for(int y = 0 ; y < danhSachMB.slMB; y++){
						if(swap[x]> swap[y]){
							int temp = swap[x];
							swap[x] = swap[y];
							swap[y] = temp;
						}
					}
				}
				int i = 0;
				for(i; i < danhSachMB.slMB; i++){
					int tam = swap[i];
					int soLuot = tam/10;
					int diaChi =  tam%10;
					gotoxy(83,17 + i);
					cout << danhSachMB.danhSachMB[diaChi]->soHieu ;
					gotoxy(105,17 + i);
					cout << soLuot;
				}					
				
				gotoxy(75, 17 + i);
				cout << "+-----------------------------------------+";  
                if (_getch() == 27) xoaManHinh();
                hienConTro();
                break;
            }
            }
        }
        
    }
    return 0;
}
