#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct DaiLy{
	char tenDL[20];
	char soDienThoai[20];
	double doanhThu;
};
struct ThanhPho{
	char tenTP[20];//Dùng khi có nhiều dữ liệu hơn cho thành phô
};
struct Node_DL{
	DaiLy data;
	Node_DL* tiep;
};
struct Node_TP{
	ThanhPho data;
	Node_TP* next;
	Node_DL* down;
};

struct List_DL{
	Node_DL* head;
};

struct List_TP{
	Node_TP* head;
};


Node_TP* taoNode_TP(ThanhPho ten){
	Node_TP* newNode = (Node_TP*)malloc(sizeof(Node_TP));
	newNode->data = ten;
	newNode->next = NULL;
	newNode->down = NULL;
	return newNode;
}
Node_DL* taoNode_DL(DaiLy dl){
	Node_DL* newNode = (Node_DL*)malloc(sizeof(Node_DL));
	newNode->data = dl;
	newNode->tiep = NULL;
	return newNode;
}

void iNit_DL(List_DL &l){
	l.head = NULL;
}
void iNit_TP(List_TP &l){
	l.head = NULL;
}

ThanhPho nhapDuLieuTP(){
	ThanhPho ten;
	fflush(stdin);
	printf("\nTen thanh pho : ");gets(ten.tenTP);
	return ten;
}

void themDauTP(List_TP &l, ThanhPho ten){
	Node_TP* p = taoNode_TP(ten);
	if(l.head == NULL)
		l.head = p;
	else{
		p->next = l.head;
		l.head = p;
	}	
}

void nhapDSThanhPho(List_TP &l, int soThanhPho){
	for(int i = 0; i< soThanhPho; i++){
		themDauTP(l,nhapDuLieuTP());
	}	
}
void swap( ThanhPho &a, ThanhPho &b){
	ThanhPho tmp = a;
	a = b;
	b = tmp;
}
void sapxepTangTheoTen_TP(List_TP &l){
	for(Node_TP *i = l.head; i != NULL; i = i->next){
		for(Node_TP *j = i->next; j != NULL; j = j->next){
			if(strcmp(i->data.tenTP, j->data.tenTP) == 1)
					swap(i->data,j->data);
				
		}
	}
}
void xuat1ThanhPho( ThanhPho tp){
	printf(" %-20s\n", tp.tenTP);
}
void xuatDSThanhPho(List_TP l){
	printf("\n\tDANH SACH THANH PHO \n\n");
	printf("\t%-5s %-20s\n", "STT","Ten thanh pho");
	Node_TP* p = l.head;
	int thuTu = 1;
	while(p != NULL){
		printf("\t%-5d",thuTu);
		xuat1ThanhPho(p->data);
		p=p->next;
		thuTu++;
	}
}
DaiLy nhapDuLieuDL(){
	DaiLy dl;
	fflush(stdin);
	printf("\nTen dai ly : ");gets(dl.tenDL);
	fflush(stdin);
	printf("So dien thoai: ");gets(dl.soDienThoai);
	printf("Doanh thu: ");scanf("%lf",&dl.doanhThu);
	return dl;
}

void themDauDL(List_DL &l, DaiLy dl){
	Node_DL* p = taoNode_DL(dl);
	if(l.head == NULL)
		l.head = p;
	else{
		p->tiep = l.head;
		l.head = p;
	}	
}

void themDSTDaiLy(List_DL &l){
	int soDaiLy;
	printf("\nNhap so dai ly:  ");scanf("%d",&soDaiLy);
	for(int i = 0; i< soDaiLy; i++){
		themDauDL(l,nhapDuLieuDL());
	}	
}
void sapxepTangTheoDoanhThu_DL(Node_DL *head){
	for(Node_DL *i = head; i != NULL; i = i->tiep){
		for(Node_DL *j = i->tiep; j != NULL; j = j->tiep){
			if(i->data.doanhThu > j->data.doanhThu){
				DaiLy tmp = i->data;
				i->data = j->data;
				j->data = tmp;
			}		
		}
	}
}
void them1_DL_TP(Node_TP* tp, DaiLy dl){
	Node_DL* p = taoNode_DL(dl);
	if(tp->down == NULL)
		tp->down = p;
	else{
		p->tiep = tp->down;
		tp->down = p;
	}	
}

void nhapdaiLyCho_TP(List_TP l_TP){
	for(Node_TP* p = l_TP.head; p!= NULL; p= p->next){
		printf("\n\n\t Thanh pho: %s",p->data.tenTP);
		List_DL l_DL;
		iNit_DL(l_DL);
		themDSTDaiLy(l_DL);
		p->down = l_DL.head;
	}
	
}
void sapxepTangTheoDoanhThu_ALL_DL(List_TP &l){
	Node_DL* p = l.head->down;
	while(p != NULL){
		sapxepTangTheoDoanhThu_DL(p);
		p=p->tiep;
	}
}
Node_TP* tim_TP(List_TP l, ThanhPho tp_tim){
	Node_TP *p = l.head;
	while( p !=NULL){
		if(stricmp(tp_tim.tenTP, p->data.tenTP) == 0)
			return p;
		p = p->next;	
	}
	return NULL;
}
Node_DL* tim_DL(Node_TP *tp, DaiLy dl_tim){
	Node_DL *p = tp->down;
	while( p !=NULL){
		if(stricmp(dl_tim.tenDL, p->data.tenDL) == 0)
			return p;
		p = p->tiep;	
	} 
	return NULL;
}
Node_DL* timTruocDL(Node_TP *tp, Node_DL *dl_canXoa){
	Node_DL *truocDL_CanXoa = tp->down;
	if(dl_canXoa == truocDL_CanXoa)
		return dl_canXoa;
	else{
		while(truocDL_CanXoa->tiep != dl_canXoa){
			truocDL_CanXoa = truocDL_CanXoa->tiep;
		}
		return truocDL_CanXoa;
	}	
}
void capNhat_DL(Node_DL *dl){
	DaiLy dl_new;
	fflush(stdin);
	printf("Ten dai ly cap nhat : "); gets(dl_new.tenDL);
	fflush(stdin);
	printf("So dien thoai cap nhat:"); gets(dl_new.soDienThoai);
	printf("Doanh thu cap nhat: "); scanf("%lf",&dl_new.doanhThu);
	dl->data = dl_new;
		
}
void xoa1_DL(Node_TP *tp, Node_DL *dl_canXoa){
	Node_DL *dl_Truoc = timTruocDL(tp,dl_canXoa);
	if(dl_Truoc == dl_canXoa){
		Node_DL* tmp = tp->down;
		tp->down = tp->down->tiep;
		free(tmp);
	}
	else{
		Node_DL* tmp = dl_canXoa;
		dl_Truoc->tiep = dl_canXoa->tiep;
		free(tmp);
		
	}	

}

void xuat1_DL(DaiLy dl, int i){
	printf("\n%-10d|%-20s|%-20s|%-20lf",i, dl.tenDL, dl.soDienThoai,dl.doanhThu);
}


void xuatDS_DL_1TP(Node_DL *head){
	printf("\n%-10s|%-20s|%-20s|%-20s","STT","Ten dai ly","So Dien Thoai","Doanh thu");
	printf("\n-------------------------------------------------------------------");
	Node_DL* p = head;
	int thuTu = 1;
	if(p==NULL)
		printf("\nKhong co dai ly nao trong thanh pho");
	while(p != NULL){
		xuat1_DL(p->data, thuTu);
		p=p->tiep;
		thuTu++;
	}
}

void xuatThongTin_DSThanhPho(List_TP l){
	Node_TP* p = l.head;
	while(p != NULL){
		printf("\n\n\n\tDANH SACH DAI LY THANH PHO %s: ",p->data.tenTP);
		xuatDS_DL_1TP(p->down);
		p=p->next;
	}
}
int tongSoDL_1_TP(Node_TP *tp){
	Node_DL *p = tp->down;
	int count = 0;
	while(p!= NULL){
		++count;
		p = p->tiep;
	}
	return count;
}
double tongDoanhThuCacDL_1_TP(Node_TP *tp){
	Node_DL *p = tp->down;
	double sum =0;
	while(p!= NULL){
		sum+=p->data.doanhThu;
		p = p->tiep;
	}
	return sum;
}
void thongKe_SL_DT(List_TP l){
	Node_TP *p =l.head;
	if(p == NULL){
		printf("Khong du du lieu");
	}
	else{
		printf("\n\t|%-5s|%-25s|%-25s|%-25s|","STT","Thanh Pho","So Luong Dai Ly","Doanh thu");
		int soThuTu = 1;
		while(p!= NULL){
			printf("\n\t|%-5d|%-25s|%-25d|%-25lf|",soThuTu,p->data.tenTP,tongSoDL_1_TP(p),tongDoanhThuCacDL_1_TP(p));
			soThuTu++;
			p=p->next;
		}
	}
}
Node_DL* timDLDoanhThuMax_1TP(Node_DL *head){
	Node_DL *p = head;
	Node_DL *max = head;
	while(p!=NULL){
		if(p->data.doanhThu>max->data.doanhThu)
			max =p;
		p = p->tiep;
	}
	return max;
	
}
void timDLDoanhThuMax_ALL(List_TP l){
	Node_TP *p = l.head;
	Node_DL *max = timDLDoanhThuMax_1TP(l.head->down);
	while(p!=NULL){
		Node_DL *tmp = timDLDoanhThuMax_1TP(p->down);
		if(tmp>max)
			max = tmp;
		p = p->next;
	}
	printf("Dai ly co doanh thu lon nhat la %s thuoc thanh pho %s",max->data.tenDL, p->data.tenTP );
	xuat1_DL(max->data,1);
}
int clean_stdin() {
    while (getchar() != '\n') {
    }
    return 1;
}
void menu(){
	printf("\n*********MENU***********");
	printf("\n1. Nhap danh sach thanh pho");
	printf("\n2. Xuat danh sach thanh pho");
	printf("\n3. Nhap danh sach dai ly cho tung thanh pho ");
	printf("\n4. Xuat danh sach dai ly cua mot thanh pho bat ky");
	printf("\n5. Xuat danh sach dai ly cua tat ca cac thanh pho");
	printf("\n6. Them dai ly cho mot thanh pho bat ky");
	printf("\n7. Sua dai ly cho mot thanh pho bat ky");
	printf("\n8. Xoa 1 dai ly cua 1 thanh pho bat ky");
	printf("\n9. Tim kiem dai ly cua 1 thanh pho bat ky");
	printf("\n10.Thong ke so luong va doanh thu cac dai ly cua cac thanh pho");
	printf("\n0. Thoat");
}
int main(){
	List_TP l_TP;
	iNit_TP(l_TP);
	int choice;
	do{
		menu();
		printf("\n\nMoi nhap :"); scanf("%d",&choice);
		switch(choice){
			case 1:{
				int soThanhPho;
				char c;
				do{
					printf("Nhap so thanh pho : ");
				}while (((scanf("%d%c", &soThanhPho, &c) != 2 || c != '\n') && clean_stdin()));
				nhapDSThanhPho(l_TP, soThanhPho);
				break;
			}
			case 2:{
				sapxepTangTheoTen_TP(l_TP);
				xuatDSThanhPho(l_TP);
				break;
			}
			case 3:{
				printf("Nhap du lieu dai ly cho tung thanh pho");
				nhapdaiLyCho_TP(l_TP);
				break;
			}
			case 4:{
				ThanhPho tp_tim;
				printf("Ban muon xuat danh sach dai ly cua thanh pho: ");fflush(stdin);gets(tp_tim.tenTP);
				Node_TP * tmp = tim_TP(l_TP,tp_tim);
				if(tmp == NULL){
					printf("Khong co thanh pho %s trong danh sach", tp_tim.tenTP);
				}
				else{
					sapxepTangTheoDoanhThu_DL(tmp->down);
					xuatDS_DL_1TP(tmp->down);
				}
		
				break;
			}
			case 5:{
				sapxepTangTheoDoanhThu_ALL_DL(l_TP);
				xuatThongTin_DSThanhPho(l_TP);
				break;
			}
			case 6:{
				ThanhPho tp_tim;
				printf("Ban muon them dai ly cho thanh pho: ");fflush(stdin);gets(tp_tim.tenTP);
				Node_TP * tmp = tim_TP(l_TP,tp_tim);
				if(tmp == NULL)
					printf("\nKhong co thanh pho %s trong danh sach", tp_tim.tenTP);
				else
					them1_DL_TP(tmp,nhapDuLieuDL());
				break;
			}
			case 7:{
				ThanhPho tp_tim;
				printf("Ban muon sua dai ly cho thanh pho: ");fflush(stdin);gets(tp_tim.tenTP);
				Node_TP * tmp_TP = tim_TP(l_TP,tp_tim);
				if(tmp_TP == NULL)
					printf("Khong co thanh pho %s trong danh sach", tp_tim.tenTP);
				else{
					DaiLy dl_tim;
					printf("Ban muon sua thong tin cho dai ly nao ?");fflush(stdin);gets(dl_tim.tenDL);	
					Node_DL* tmp_Dl = tim_DL(tmp_TP,dl_tim);
					if(tmp_Dl == NULL)
						printf("\nKhong co dai ly %s trong thanh pho %s", dl_tim, tp_tim.tenTP);
					else
						capNhat_DL(tmp_Dl);
				}			
				break;
			}
			case 8:{
				ThanhPho tp_tim;
				printf("Ban muon xoa dai ly cua thanh pho: ");fflush(stdin);gets(tp_tim.tenTP);
				Node_TP * tmp_TP = tim_TP(l_TP,tp_tim);
				if(tmp_TP == NULL)
					printf("Khong co thanh pho %s trong danh sach", tp_tim.tenTP);
				else{
					DaiLy dl_tim;
					printf("Ban muon xoa dai ly co ten: ");fflush(stdin);gets(dl_tim.tenDL);	
					Node_DL* tmp_Dl = tim_DL(tmp_TP,dl_tim);
					if(tmp_Dl == NULL)
						printf("\nKhong co dai ly %s trong thanh pho %s", tp_tim.tenTP, dl_tim);
					else
						xoa1_DL(tmp_TP,tmp_Dl);
				}
				break;
			}
			case 9:{
				ThanhPho tp_tim;
				printf("Ban muon tim dai ly trong thanh pho: ");fflush(stdin);gets(tp_tim.tenTP);
				Node_TP * tmp_TP = tim_TP(l_TP,tp_tim);
				if(tmp_TP == NULL)
					printf("Khong co thanh pho %s trong danh sach", tp_tim.tenTP);
				else{
					DaiLy dl_tim;
					printf("Nhap ten dai ly ban muon tim: ");fflush(stdin);gets(dl_tim.tenDL);	
					Node_DL* tmp_Dl = tim_DL(tmp_TP,dl_tim);
					if(tmp_Dl == NULL)
						printf("Khong co dai ly %s trong thanh pho %s", dl_tim.tenDL,tp_tim.tenTP);
					else{
						printf("Co dai ly %s trong thanh pho %s",dl_tim.tenDL,tp_tim.tenTP);
						printf("\n%-10s|%-20s|%-20s|%-20s","STT","Ten dai ly","So Dien Thoai","Doanh thu");
						xuat1_DL(tmp_Dl->data,1);
					}	
				}
				break;
			}
			case 10:{
				thongKe_SL_DT(l_TP);
				break;
			}
			case 0:{
				printf("\n\t\tEXIT");
				break;
			}
			default: {
				printf("Vui long nhap theo danh sach");
				break;
			}
		}
	}while(choice !=0);

}
