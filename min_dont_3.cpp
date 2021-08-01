#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<iostream>
using namespace std;

#define line printf("\n===================\n");
void doinhiphan(int x,int n,int dont,int minterm[],int nhiphan[][100]);
void nhap(int n,int minterm[]);
void insert_dontcare(int n,int dont[]);
void Merge(int minterm[], int dontcare[], int n, int dont,int merege[]);
void sosanh(int x,int n,int nhiphan[][100],int &a,int &b);
void hienthi(int x,int nhiphan[][100],int b);
void ketqua(int x,int n,int nhiphan[][100],int a,int b,int &d, int &d1);
void inraFILEhamnhap(int merge[],int x,int n,int dont);
void inraFILErutgon(int nhiphan[][100],int b,int x);
void inraFILECACNHOM(int nhiphan[][100],int a,int b,int x,int d,int d1);
void inraFILEkq(int nhiphan[][100],int a,int b,int x,int d, int d1);
void In_bang(int nhiphan[][100],int merge[],int n,int x, int a, int b);

int main(){
     int x,n,dont;
     printf("Nhap vao so bien cua ham: ");
     scanf("%d",&x);
     printf("Nhap vao so minterm cua ham: ");
     scanf("%d",&n);
     printf("Nhap vao so dontcare cua ham: ");
     scanf("%d",&dont);
     int dontcare[dont];
     int minterm[n],nhiphan[1000][100],a=0,b=n+dont;//2 bien a,b danh dau lai khoang dau va cuoi mang sau 1 lan sosanh
     int d=0;//dem so thu tu cac NHOM TUY CHON co the dai dien het cac phan tu con sot lai.
     int merge[n+dont];
     int d1=0;
     if(n==0) {
	     goto khongMinterm;}
     nhap(n,minterm);
     insert_dontcare(dont,dontcare);
     Merge(minterm,dontcare,n,dont,merge);
     inraFILEhamnhap(merge,x,n,dont);
     doinhiphan(x,n,dont,merge,nhiphan);
     line;
     sosanh(x,n,nhiphan,a,b);
     hienthi(x,nhiphan,b);
     line;
     inraFILErutgon(nhiphan,b,x);
     line;
     ketqua(x,n,nhiphan,a,b,d,d1);
     Merge(minterm,dontcare,n,dont,merge);
     In_bang( nhiphan,merge, n, x,a,b);
     inraFILECACNHOM(nhiphan,a,b,x,d,d1);
     inraFILEkq(nhiphan,a,b,x,d,d1);
     return 0;
     // getch(); 
     khongMinterm:
	      printf("\n\nF(");
     for(int i=0;i<x;i++)
     {
          if(i>0) printf(",");
          printf("%c",65+i);
     }
     printf(")= 0");
     return 0;
}


void doinhiphan(int x,int n,int dont,int merge[],int nhiphan[][100]){
     for(int i=0;i<n+dont;i++)
          for(int j=0;j<x+1;j++){
               nhiphan[i][j]=0;
          }
     for(int i=0;i<n+dont;i++)
          for(int j=0;merge[i]>0;j++){
               nhiphan[i][x-1-j]=merge[i]%2;
               merge[i]=merge[i]/2;       
          }
}


void nhap(int n,int minterm[]){
     for(int i=0;i<n;i++){
          printf("Nhap minterm %d: ",i+1);
          scanf("%d",&minterm[i]);
     }
}
void insert_dontcare(int n,int dont[]){
     for(int i=0;i<n;i++){
          printf("Nhap dontcare %d: ",i+1);
          scanf("%d",&dont[i]);
     }
}

void Merge(int minterm[], int dontcare[], int n, int dont,int merege[]){
     for(int i=0;i<n;i++){
          merege[i] = minterm[i];
     }
     int k=0;
     for(int i=n;i<n+dont;i++){
          merege[i]=dontcare[k++];
     }
}


void hienthi(int x,int nhiphan[][100],int b){
     for(int i=0;i<b;i++){
          for(int j=0;j<x+1;j++){
               printf("%d ",nhiphan[i][j]);
          }
          printf("\n");
          if(nhiphan[i][x]==3) printf("\n----\n");
    } 
}


void sosanh(int x,int n,int nhiphan[][100],int &a,int &b)
{
     int g,count2,kt=0,i,count2B/*khai bao o day de dung dc cho while*/;
     do
     {
          count2B=0;//chi dung trong 1 chu ky cua vong for(i),neu count2B>0 tuc la van phai rut gon tiep
          count2=0;//de dem so luot ghi lai 2minterm chi #nhau 1bit,sau do thay b=b+count2;
          for(i=a;i<b;i++)
          {
               int count4=0;//kt minterm sot hay ko
               for(int j=a;j<b;j++){
                    int count=0;//kiem tra 2 day minterm khac nhau 1 hay nhieu bit.      
                    for(int k=0;k<x;k++){
                         if(nhiphan[i][k]!=nhiphan[j][k]){
                              g=k;//danh dau k bang g, g chi co y nghia trong TH count==1.
                              count++;
                         }
                    }

                    if(count>1) count4++;
                         
                         //truong hop # nhau 1 bit:             
                    if(count==1)//lenh if trong vong for cua 'j'.
                    {    
                         for(int k=0;k<x;k++){//coppy minterm da rut gon vao cuoi mang nhiphan[][].
                         
                              if(k!=g)
                                   nhiphan[b+count2][k]=nhiphan[i][k]; 
                              else nhiphan[b+count2][g]=2;//=2 thay cho dau '-', nhiphan[j][g] ko can phai =2.
                         }
               
                                        //kiem tra xem da ton tai minterm nao giong no chua:
                         for(int m=b;m<b+count2;m++)
                         {
                              int count3=0;//kt ton tai minterm giong nhau ko.
                              for(int n=0;n<x;n++){
                                   if(nhiphan[m][n]==nhiphan[b+count2][n])
                                   count3++;
                              }
                              if(count3==x)
                                   nhiphan[b+count2][g]=3;
                         }
                         if(nhiphan[b+count2][g]!=3)//neu ko co cai nao giong thi tang cac chi so len<=>luu no.
                         {
                              count2++;
                              count2B++;
                              nhiphan[b-1][x]=3;/*chu y trong vai TH*/   //danh dau cho~ cuoi cua 1 chu trinh ss de ham deplay chia khoang cho dep^^.
                         }
                    }//ket thuc TH #1. 
               }//ket thuc for(j)
       
               //TH con sot minterm trong luot ss dau tien vi sai # >1 bit voi tat ca cac minterm con lai:        
               if(count4==b-a-1) //de dam bao: minterm nay #>2bit voi tat ca.
               {
                    for(int k=0;k<x;k++)
                    {
                         nhiphan[b+count2][k]=nhiphan[i][k];//coppy minterm (#nhau 2bit tro len)nay vao cuoi mang nhiphan[][].
                    }
                    count2++;
               }
          }//ket thuc for(i)
   
          if(count2!=0&&count2B>0)//dam bao luc ket thuc chu trinh (tuc count2==0&&count2B==0) thi ko can thay doi a,b
          {
               a=b;//2 bien a,b danh dau lai khoang dau va cuoi mang sau 1 lan sosanh
               b=b+count2;
          }
     }while(count2B>0);//neu sau 1 chu ky sosanh ma count2B van =0 => ket thuc.
}
// hienthi(x,nhiphan,b);
//      line;

void ketqua(int x,int n,int nhiphan[][100],int a,int b,int &d, int &d1)
{
     int i,j,k,count;
     printf("%d_%d_%d\n",n,a,b);

     //1.reset cac minterm nhiphan[0->b][x]=0:
     for(i=0;i<b;i++){
          nhiphan[i][x]=0;
     }

     //2.danh dau cac cot chi chua 1 dau X:
     for(i=a;i<b;i++)
     {
          for(j=0;j<n;j++)
          {
               count=0;
               for(k=0;k<x;k++)
               {
                    if(nhiphan[i][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                    count++;
               }
               if(count==0)
               nhiphan[j][x]++;//DANH DAU = SO LAN LAP LAI PHAN TU DO
               // printf("%2d",nhiphan[j][x]);
          }
     }
     hienthi(x,nhiphan,b);
     line;

     //3.tu cac cot chi chua 1 dau X tim lai cac minterm tao ra dau X do:
     for(i=0;i<n;i++)
     {
          if(nhiphan[i][x]==1)
          for(j=a;j<b;j++)
          {
               count=0;
               for(k=0;k<x;k++)
               {
                    if(nhiphan[j][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                    count++;
               }
               if(count==0)
               nhiphan[j][x]=3;//DANH DAU (=3)
          }
     }
     hienthi(x,nhiphan,b);
     line;

     //4.DANH DAU CAC PHAN TU XUAT HIEN >1 LAN, NHUNG DA NAM TRONG CAC NHOM BAT BUOC:
     for(i=a;i<b;i++){
          if(nhiphan[i][x]==3)
          for(j=0;j<n;j++) {
               count=0;
               for(k=0;k<x;k++){
                   if(nhiphan[i][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                   count++;
               }
               if(count==0)
                   nhiphan[j][x]=77;//DANH DAU: THUOC NHOM BAT BUOC (=77)
          }
      }   
      hienthi(x,nhiphan,b);
     line;
      //5.TU CAC PHAN TU CON SOT LAI - CHUA NAM TRONG NHOM BAT BUOC(#77), DANH DAU TAM THOI CAC NHOM CO THE DAI DIEN CHO NO(=4):
      for(i=0;i<n;i++)
      {
           if(nhiphan[i][x]!=77)
           for(j=a;j<b;j++)
           {
                count=0;
                for(k=0;k<x;k++)
                {
                     if(nhiphan[j][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                     count++;
                }
                if(count==0)
                nhiphan[j][x]=4;//DANH DAU TAM THOI(=4), DE KT TIEP XEM CO DU DK DAI DIEN KO!
           }
      }
      hienthi(x,nhiphan,b);
     line;

      //6.KIEM TRA LAI CAC NHOM VUA DANH DAU (=4) XEM CO DAI DIEN HET CHO CAC PHAN TU CON SOT LAI KO:  
     for(i=a;i<b;i++)
     {
          if(nhiphan[i][x]==4)
          {
               count=0;
               int count3=0;

               for(j=0;j<n;j++)
               {
                    if(nhiphan[j][x]!=77){
                         int count2=0;
                         for(k=0;k<x;k++)
                         {
                              if(nhiphan[i][k]==2||nhiphan[i][k]==nhiphan[j][k])
                                   count2++;
                         }
                         if(count2==x) count3++;
                    }
               }

               if(count3>=2 ){
                    d1++;
                    nhiphan[i][x]=41+d1;
               }
          }
     }
     hienthi(x,nhiphan,b);
     line;

     //6.1
     for(i=a;i<b;i++){
          if(nhiphan[i][x]>41)
          for( j=0;j<n;j++) {
               if(nhiphan[j][x]>=2&&nhiphan[j][x]<10){
                    count=0;
                    for(k=0;k<x;k++){
                    if(nhiphan[i][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                    count++;
                    }
                    if(count==0)
                    nhiphan[j][x]=66;
               }
          }
      }   
     hienthi(x,nhiphan,b);
     line;

      //6.2
      for(i=a;i<b;i++)
     {
          if(nhiphan[i][x]==4)
          {
               count=0;

               for(j=0;j<n;j++)
               {
                    if(nhiphan[j][x]!=77 && nhiphan[j][x]!=66)
                         for(k=0;k<x;k++)
                         {
                              if(nhiphan[i][k]!=2&&nhiphan[i][k]!=nhiphan[j][k])
                              count++;
                         }
               }
               if(count==0 )
               {
                    for(j=0;j<n;j++){
                         if(nhiphan[j][x]!=77 && nhiphan[j][x]!=66){
                              d=d+1;
                              nhiphan[i][x]=30+d;//neu NHOM do dai dien dc het, thi danh dau (=3X) de tien sau nay in ra het cac TH KQ co the co.
                         }
                    }
               }
          }
     }
     hienthi(x,nhiphan,b);
     line;
}

void inraFILEhamnhap(int merge[],int x,int n,int dont)
{
     printf("\nHam duoc cho:");
          printf("\n\nF(");
          for(int i=0;i<x;i++)
          {
                if(i>0) printf(",");
                  printf("%c",65+i);
          }
          printf(")= m{");
          for(int i=0;i<n;i++)
          {   
                if(i>0) printf(",");
                  printf("%d",merge[i]);
          }
          printf("}");
          if(dont>0) {
               printf("+ D{");
               for(int i=n;i<n+dont;i++){
                    if(i>n) printf(",");
                    printf("%d",merge[i]);
               }
               printf("}\n");
          }  
}


void inraFILErutgon(int nhiphan[][100],int b,int x)
{
     for(int i=0;i<b;i++){
          if(i+1<10) printf("0%d  ",i+1);
          if(i+1>=10) printf("%d  ",i+1);
          for(int j=0;j<x;j++){
               if(nhiphan[i][j]==2) printf("-");
               else
                    printf("%d",nhiphan[i][j]);
          }
          printf("\n");
          if(nhiphan[i][x]==3) printf("----\n");
     }
}



void In_bang(int nhiphan[][100],int merge[],int n,int x,int a, int b){
     printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~Bang Prime Implicant~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
     printf("\nCac nhom\t|");
     for(int i=0;i<n;i++){
          printf("\t%d",merge[i]);
     }
     printf("\n======================================================================================================================================\n");
     for(int i=a;i<b;i++){
          for(int h=0;h<x;h++){
               if(nhiphan[i][h]==1) printf("%c",65+h);              
               if(nhiphan[i][h]==0) printf("%c'",65+h); 
          }
    printf("\t\t");
          for(int j=0;j<n;j++){
               int count =0;
               for(int k=0;k<x;k++){
                    if(nhiphan[i][k]==2||nhiphan[i][k]==nhiphan[j][k]) ++count;
               }
               if(count==x) {
                    printf("\tx");
               }
               else printf("\t");
          }
          printf("\n======================================================================================================================================\n");
     }
}

void inraFILECACNHOM(int nhiphan[][100],int a,int b,int x,int d, int d1)
{
               printf("----\n");
               printf("NHOM BAT BUOC:  ");         
               for(int i=a;i<b;i++){
                    for(int j=0;j<x;j++){
                         if(nhiphan[i][x]==3||nhiphan[i][x]==77)
                         if(nhiphan[i][j]==2) printf("-");
                         else printf("%d",nhiphan[i][j]);
                    }
                    if(nhiphan[i][x]==3||nhiphan[i][x]==77&&i!=b-1) printf(" ; ");
               }       
}


void inraFILEkq(int nhiphan[][100],int a,int b,int x,int d,int d1)
{
     // printf("%d\t%d\t%d\t%d\n",a,b,d,d1);
     printf("\n\nF(");
     for(int i=0;i<x;i++)
     {
          if(i>0) printf(",");
          printf("%c",65+i);
     }
     printf(")= ");
     
     if(d==0)
      {
           if(d1==0){
               int count=0;
               for(int i=a;i<b;i++)
               {
                    if(nhiphan[i][x]==3||nhiphan[i][x]==77)
                    {
                          int count_sp=0;
                         if( count==1) printf(" + ");
                         for(int j=0;j<x;j++)
                         {
                              if(nhiphan[i][j]==1)
                              {
                                   printf("%c",65+j);
                                   count=1;
                              }
                              if(nhiphan[i][j]==0)
                              {
                                   printf("%c'",65+j);
                                   count=1;
                              }
                              if(nhiphan[i][j]==2) ++count_sp;
                         }
                         if(count_sp==x) printf("1");
                    }  
               }
           }
          
          if(d1!=0){

               for(int e=1;e<=d1;e++)
               {
                    //7B.HIEN THI CAC NHOM BAT BUOC:
                    int count=0;
                    for(int i=a;i<b;i++)
                    {
                         if(nhiphan[i][x]==3)
                         {
                              if(count==1) printf(" + ");
                                   for(int j=0;j<x;j++)
                                   {
                                        if(nhiphan[i][j]==1)
                                        {
                                             printf("%c",65+j);
                                             count=1;
                                        }
                                        if(nhiphan[i][j]==0)
                                        {
                                             printf("%c'",65+j);
                                             count=1;
                                        }
                                   }
                         }  
                    }
                    //7C.HIEN THI CAC NHOM TUY CHON:
                    for(int i=a;i<b;i++)
                    {
                         if(nhiphan[i][x]==41+e)
                         {
                              printf(" + ");
                              for(int j=0;j<x;j++)
                              {
                                   if(nhiphan[i][j]==1)
                                   {
                                   printf("%c",65+j);
                                   count=1;
                                   }
                                   if(nhiphan[i][j]==0)
                                   {
                                        printf("%c'",65+j);
                                        count=1;
                                   }
                              }
                         }  
                    }  
                    if(e!=d1) printf("\n\tHOAC:\n");
               }

          }

      }
      if(d!=0)
      {

           if(d1==0){
               for(int e=1;e<=d;e++)
               {
                    //7B.HIEN THI CAC NHOM BAT BUOC:
                    int count=0;
                    for(int i=a;i<b;i++)
                    {
                         if(nhiphan[i][x]==3)
                         {
                              if(count==1) printf(" + ");
                              for(int j=0;j<x;j++)
                              {
                                   if(nhiphan[i][j]==1)
                                   {
                                        printf("%c",65+j);
                                        count=1;
                                   }
                                   if(nhiphan[i][j]==0)
                                   {
                                        printf("%c'",65+j);
                                        // printf("sdfasdfa");
                                        count=1;
                                   }
                              }
                         }  
                    }
                    //7C.HIEN THI CAC NHOM TUY CHON:
                    for(int i=a;i<b;i++)
                    {
                         if(nhiphan[i][x]==30+e)
                         {
                              printf(" + ");
                              for(int j=0;j<x;j++)
                              {
                                   if(nhiphan[i][j]==1)
                                   {
                                        printf("%c",65+j);
                                        count=1;
                                   }
                                   if(nhiphan[i][j]==0)
                                   {
                                        printf("%c'",65+j);
                                        count=1;
                                   }
                              }
                         }  
                    }  
                    if(e!=d) printf("\n\tHOAC:\n");
               }
           }
           if(d1!=0){    
               // In nhom tuy chon loai 2 truoc
               for(int w=1;w<=d1;w++){

                    for(int e=1;e<=d;e++)
                    {
                    
                         int count=0;
                         for(int i=a;i<b;i++)
                         {
                              if(nhiphan[i][x]==41+w)
                              {
                                        if(count==1) printf(" + ");
                                             for(int j=0;j<x;j++)
                                             {
                                                  if(nhiphan[i][j]==1)
                                                  {
                                                       printf("%c",65+j);
                                                       count=1;
                                                  }
                                                  if(nhiphan[i][j]==0)
                                                  {
                                                       printf("%c'",65+j);
                                                       count=1;
                                                  }
                                             }
                              }  
                         }                    
                         //7B.HIEN THI CAC NHOM BAT BUOC:
                         for(int i=a;i<b;i++)
                         {
                              if(nhiphan[i][x]==3)
                              {
                                   printf(" + ");
                                   for(int j=0;j<x;j++)
                                   {
                                        if(nhiphan[i][j]==1)
                                        {
                                             printf("%c",65+j);
                                             
                                        }
                                        if(nhiphan[i][j]==0)
                                        {
                                             printf("%c'",65+j);
                                             
                                        }
                                   }
                              }  
                         }  
                    
                         //7C.HIEN THI CAC NHOM TUY CHON LOAI 1:
                         for(int i=a;i<b;i++)
                         {
                              if(nhiphan[i][x]==30+e)
                              {
                                   printf(" + ");
                                   for(int j=0;j<x;j++)
                                   {
                                        if(nhiphan[i][j]==1)
                                        {
                                             printf("%c",65+j);
                                             count=1;
                                        }
                                        if(nhiphan[i][j]==0)
                                        {
                                             printf("%c'",65+j);
                                             count=1;
                                        }
                                   }
                              }  
                         }  
                         if(e!=d) printf("\n\tHOAC:\n");
                    }
                    if(w!=d1) printf("\n\tHOAC:\n");
               }

          }
      }
}
