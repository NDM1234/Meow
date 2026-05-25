#include <stdio.h>
#include <string.h>
#include "mahoa.h"

int main() {
    int n;
    char a[1000];
    do{
        printf("1.Ma hoa ngay\n");
        printf("2.Ma hoa file\n");
        printf("3.Dich ngay\n");
        printf("4.Dich File\n");
        printf("5.Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &n);
        getchar();
        switch(n){
            case 1:
                printf("Nhap noi dung can ma hoa(<1000 ki tu):\n");
                fgets(a, sizeof(a), stdin);
                a[strcspn(a, "\n")] = '\0';
                meow(a,1);
                break;
            case 2:
                printf("Nhap ten file can ma hoa: ");
                fgets(a, sizeof(a), stdin);
                a[strcspn(a, "\n")] = '\0';
                meow(a,2);
                break;
            case 3:
                printf("Nhap noi dung can dich(<1000 ki tu):\n");
                fgets(a, sizeof(a), stdin);
                a[strcspn(a, "\n")] = '\0';
                dich(a,1);
                break;
            case 4:
                printf("Nhap ten file can dich: ");
                fgets(a, sizeof(a), stdin);
                a[strcspn(a, "\n")]= '\0';
                dich(a, 2);
                break;
            case 5:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }
    while(n!=5);
    return 0;
}