#include<iostream>
#include<fstream>
#include <string.h>
#include <windows.h>
#define MAX_SIZE 20                 //��������󳤶�
#define HASHSIZE 30             //�����
#define ok 1
#define error -1
typedef char CH[MAX_SIZE];
using namespace std;
typedef struct Record
{//��¼
    CH name;
    CH tel;
    CH add;
    struct Record *next=NULL;
} Record;

typedef struct
{//ɢ�б�
    Record *elem[HASHSIZE];                 //����Ԫ�ش洢��ַ
    int count;                              //��ǰ����Ԫ�ظ���
    int size;                               //��ǰ����
} HashTable;

//ȫ�ֱ���
int search_lenth_n=0;
double search_lenth[2][10]={0};//ƽ�����ҳ��ȼ�¼
int alength;//a�������
int NUM_BER;//��������
int random[10]={1,3,9,7,2,5,6,4,8,0};//α���������

void Cls()
{//����
    printf("*");
    system("cls");
}


int eq(CH x,CH y)
{//�Ƚ��Ƿ����
    //�ؼ��ֱȽϣ���ȷ���1�����򷵻�-1
    if(strcmp(x,y)==0)
        return ok;
    else return error;
}


void getin(Record* a)
{//��Ӻ���
    cout<<"����Ҫ��ӵĸ�����"<<endl;
    cin>>NUM_BER;
    int i;
    for(i=alength;i<alength+NUM_BER; i++)
    {

        printf("�������%d����¼���û���:\n",i+1);
        //scanf("%s",a[i].name);
        cin>>a[i].name;
        printf("������%d����¼�ĵ绰����:\n",i+1);
        //scanf("%s",a[i].tel);
        cin>>a[i].tel;
        printf("�������%d����¼�ĵ�ַ:\n",i+1);
        //scanf("%s",a[i].add);
        cin>>a[i].add;

    }
    alength=alength+NUM_BER;
}


int daoru(Record* a)
{//�����ļ������Ϣ

    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open())cout<<"���ļ�ʧ��";

    string s;
    int i=0;
    //int j=0;
    while(getline(ifs,s)){
       strncpy(a[i].name,s.c_str(),s.length()+1);
       getline(ifs,s);
       strncpy(a[i].tel,s.c_str(),s.length()+1);
       getline(ifs,s);
       strncpy(a[i].add,s.c_str(),s.length()+1);
       alength++;
       i++;
    }

    ifs.close();
    return 0;
}


void ShowInformation(Record* a)
{//��ʾ�û���Ϣ
    int i;
    if(alength==0){
        cout<<"Ŀǰ������"<<endl;
    }
    for( i=0; i<alength; i++)
        printf("\n��%d���û���Ϣ:\n ������%s\n �绰���룺%s\n ��ϵ��ַ��%s\n",i+1,a[i].name,a[i].tel,a[i].add);
}


long fold(CH s)
{//�����Ĵ���
    char *p;
    long sum=0;
    CH ss;
    strcpy(ss,s);
    strupr(ss);                              //���ַ���ssת��Ϊ��д��ʽ
    p=ss;
    while(*p!='\0'){
        sum+=*p;
        p++;
    }
   // printf("\n��ĵ�ַ����%ld",sum);
    return sum;
}


int Hash1(CH str)
{//���������ɢ�к���
    long n;
    int m;
    n=fold(str);                          //�Ƚ��û��������۵�����
    m=n%HASHSIZE;                        //�۵������������ó�������������ɢ�к���
    if(m<0){
        m=m+HASHSIZE;
    }
    return m;                             //������ģֵ
}


int Hash2(CH str)
{//�绰�����ɢ�к���

    long n;
    int m;
    n = atoi(str);                        //���ַ���ת�������͵ĺ���.
    m=n%HASHSIZE;                         //�ó�������������ɢ�к���
    return m;                             //������ģֵ
}


int Choice()
{//ѡ������ͻ����
    cout<<"---------------------"<<endl;
    cout<<"-1.����̽����ɢ�з�--"<<endl;
    cout<<"-2.����̽����ɢ�з�--"<<endl;
    cout<<"-3.α���̽����ɢ�з�"<<endl;
    cout<<"-4.����ַ��----------"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"����������ͻ��ʽ��"<<endl;
    int k;
    cin>>k;
     switch(k)
    {
    case 1:
        cout<<"����̽����ɢ�з�����ɢ�б�����"<<endl;
        break;
    case 2:
        cout<<"����̽����ɢ�з�����ɢ�б�����"<<endl;
        break;
    case 3:
        cout<<"α���̽����ɢ�з�����ɢ�б�����"<<endl;
        break;
    case 4:
        cout<<"����ַ������ɢ�б�����"<<endl;
        break;
    default:
        cout<<"�����������������!"<<endl;
    }
    return k;
}


int collision_1(int p,int &c)
{//����̽����ɢ�з������ͻ����
    int i,q;
    i=c;
    while(i<HASHSIZE){
        c++;
        q=(p+i+1)%HASHSIZE;
        if(q>=0)return q;
        else i=c;
    }
    return error;
}


int collision_2(int p,int &c)
{//����̽����ɢ�з������ͻ����
    int i,q;
    i=c/2+1;
    while(i<HASHSIZE)
    {
        if(c%2==0)
        {
            c++;
            q=(p+i*i)%HASHSIZE;
            if(q>=0) return q;
            else i=c/2+1;
        }
        else
        {
            q=(p-i*i)%HASHSIZE;
            c++;
            if(q>=0) return q;
            else i=c/2+1;
        }
    }
    return error;
}


int collision_3(int p,int &c)
{//α���̽����ɢ�з������ͻ����
    int i,q;
    i=c;
    while(i<HASHSIZE){
        c++;
        q=(p+random[c])%HASHSIZE;
        if(q>=0)return q;
        else i=c;
    }
    return error;
}


int collision_4(HashTable* H,int p,int &c,int x)
{//����ַ�������ͻ����
    if(x==0){//����
        Record *q;
        q=H->elem[p];
        c++;
        while(q->next!=NULL){
            c++;
            q=q->next;
        }
        return 1;
    }
    else{
        return 1;
    }
}


int collision(HashTable* H,int p,int &c,int k,int x)
{//ѡ������ͻ����
    switch(k)
    {
    case 1:
        return collision_1(p,c);
        break;
    case 2:
        return collision_2(p,c);
        break;
    case 3:
        return collision_3(p,c);
        break;
    case 4:
        return collision_4(H,p,c,x);
        break;
    default:
        cout<<"�����������������!"<<endl;
    }
    return 0;
}


void Average_lenth(int k,int x)
{//��ƽ�����ҳ���
    if(x==0){
        search_lenth[0][search_lenth_n]+=k;
        search_lenth[1][search_lenth_n]+=k;
    }
    else{
        double r_1=0;
        double r_2=0;
        if(alength!=0){
        r_1=(search_lenth[0][search_lenth_n]+alength*1.0)/alength;
        r_2=(search_lenth[1][search_lenth_n]*1.0)/(search_lenth[0][search_lenth_n]+alength);
        }
        search_lenth[0][search_lenth_n]=r_1;
        search_lenth[1][search_lenth_n]=r_2;
        cout<<"ƽ�����ҳ���Ϊ��"<<r_1<<endl;
        cout<<"��ͻ��Ϊ      ��"<<r_2<<endl;
    }
}

void DeleteOne(HashTable* H,Record* a)
{//ɾ��һ���ڵ�
    int x;
    cout<<"1.������ɾ��"<<endl;
    cout<<"2.���绰ɾ��"<<endl;
    cin>>x;
    CH s;
    cout<<"������ɾ����Ϣ"<<endl;
    cin>>s;
    bool k=FALSE;
    if(x==1){
        int i=0;
        for(;i<alength;i++){
            if(eq(a[i].name,s)==1){
                k=TRUE;
                break;
            }
        }
        if(k){
            alength=alength-1;
            for(int j=i;j<alength;j++){
                a[j]=a[j+1];
            }
        cout<<"ɾ���ɹ�"<<endl;
        }
    }
    else{
        int i=0;
        for(;i<alength;i++){
            if(eq(a[i].tel,s)==1){
                k=TRUE;
                break;
            }
        }
        if(k){
            alength=alength-1;
            for(int j=i;j<alength;j++){
                a[j]=a[j+1];
            }
        cout<<"ɾ���ɹ�"<<endl;
        }

    }
}

void CreateHash1(HashTable* H,Record* a,int k)
{//������Ϊ�ؼ��֣�������Ӧ��ɢ�б��������Ӧ�ĳ�ͻ
    int i,p=-1,c,pp;
    for(i=0; i<alength; i++)
    {
        c=0;
        p=Hash1(a[i].name);
        pp=p;
        while(H->elem[pp]!=NULL||pp<0)
        {
            pp=collision(H,p,c,k,0);
            if(k==4)break;
            if(pp<0)
            {
                printf("��%d��¼�޷������ͻ",i+1);
                //continue;
                break;
            }
        }
        if(k==4){
            Record *q;
            q=H->elem[p];
            Record *t;
            t=(Record *)malloc(sizeof(Record));
            t=&(a[i]);
            if(q==NULL){
                H->elem[p]=t;
            }
            else{
            for(int j=0;j<c-1;j++){
                q=q->next;
            }
            q->next=t;
            }

            printf("��%d����¼������Ϊ%s,ɢ�е�ַΪ%d����ͻ����Ϊ%d��\n",i+1,t->name,p,c);
        }
        else{
            H->elem[pp]=&(a[i]);                      //���ɢ�е�ַ������Ϣ����
            printf("��%d����¼������Ϊ%s,ɢ�е�ַΪ%d����ͻ����Ϊ%d��\n",i+1,H->elem[pp]->name,pp,c); //��Ҫ��ʾ��ͻ����ʱ���
         }
        H->count++;
        if(H->count==HASHSIZE)
            cout<<"�Ѿ��ﵽ����"<<endl;
        Average_lenth(c,0);
    }
    printf("\n�������!\n��ɢ�б�����Ϊ%d,��ǰ���ڴ洢�ļ�¼����Ϊ%d.\n",HASHSIZE,H->count);
    Average_lenth(0,1);
}


void SearchHash1(HashTable* H,int &c,int k)
{//��ͨѶ¼���������
    CH str;
    cout<<endl<<"������Ҫ���Ҽ�¼��������"<<endl;
    cin>>str;
    int p,pp;
    p=Hash1(str);
    pp=p;
    while((H->elem[pp]!=NULL)&&(eq(str,H->elem[pp]->name)==-1))
        pp=collision(H,p,c,k,1);


    if(k==4){
            Record *y;
            y=H->elem[p];
            if(y==NULL){
                cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
            }
            else {
                    while(eq(str,y->name)==-1){
                if(y->next==NULL){
                    cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
                    break;
                }
                else{
                    y=y->next;
                    c++;
                }
            }
            printf("\n���ҳɹ���\n���ҹ��̳�ͻ����Ϊ%d������������ҪҪ���ҵ���Ϣ��\n\n",c);
            printf("��  ����%s\n�绰���룺%s\n��ϵ��ַ��%s\n",y->name,y->tel,y->add);
            }
    }

    else{
     if(H->elem[pp]!=NULL&&eq(str,H->elem[pp]->name)==1)
     {
        printf("\n���ҳɹ���\n���ҹ��̳�ͻ����Ϊ%d������������ҪҪ���ҵ���Ϣ��\n\n",c);
        printf("��  ����%s\n�绰���룺%s\n��ϵ��ַ��%s\n",H->elem[pp]->name,H->elem[pp]->tel,H->elem[pp]->add);
     }
     else cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
     }
}


void CreateHash2(HashTable* H,Record* a,int k)
{//�Ե绰Ϊ�ؼ��֣�������Ӧ��ɢ�б��������Ӧ�ĳ�ͻ
    int i,p=-1,c,pp;
    for(i=0; i<alength; i++)
    {
        c=0;
        p=Hash2(a[i].tel);
        pp=p;
        while(H->elem[pp]!=NULL||pp<0)
        {
            pp=collision(H,p,c,k,0);
            if(k==4)break;
            if(pp<0)
            {
                printf("��%d��¼�޷������ͻ",i+1);   //��Ҫ��ʾ��ͻ����ʱ���
                continue;
            }                                      //�޷������ͻ��������һѭ��(��+1)
        }

        if(k==4){
            Record *q;
            q=H->elem[p];
            Record *t;
            t=(Record *)malloc(sizeof(Record));
            t=&(a[i]);
            if(q==NULL){
                H->elem[p]=t;
            }
            else{
            for(int j=0;j<c-1;j++){
                q=q->next;
            }
            q->next=t;
            }

            printf("��%d����¼�ĵ绰Ϊ%s,ɢ�е�ַΪ%d����ͻ����Ϊ%d��\n",i+1,t->tel,p,c);
        }
        else {
        H->elem[pp]=&(a[i]);                      //���ɢ�е�ַ������Ϣ����
        printf("��%d����¼�ĵ绰Ϊ%s,ɢ�е�ַΪ%d����ͻ����Ϊ%d��\n",i+1,H->elem[pp]->tel,pp,c);//��Ҫ��ʾ��ͻ����ʱ���
        }
        H->count++;
        if(H->count==HASHSIZE)
        cout<<"�Ѿ��ﵽ����"<<endl;
        Average_lenth(c,0);
    }
    printf("\n�������!\n��ɢ�б�����Ϊ%d,��ǰ���ڴ洢�ļ�¼����Ϊ%d.\n",HASHSIZE,H->count);
    Average_lenth(0,1);
}


void SearchHash2(HashTable* H,int &c,int k)
{//��ͨѶ¼����ҵ绰����
    CH tele;
    cout<<endl<<"������Ҫ���Ҽ�¼�ĵ绰���룺"<<endl;
    cin>>tele;
    int p,pp;
    p=Hash2(tele);
    pp=p;
    while((H->elem[pp]!=NULL)&&(eq(tele,H->elem[pp]->tel)==-1))
        pp=collision(H,p,c,k,1);

    if(k==4){
            Record *y;
            y=H->elem[p];
            if(y==NULL){
                cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
            }
            else {
                    while(eq(tele,y->tel)==-1){
                if(y->next==NULL){
                    cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
                    break;
                }
                else{
                    y=y->next;
                    c++;
                }
            }
            printf("\n���ҳɹ���\n���ҹ��̳�ͻ����Ϊ%d������������ҪҪ���ҵ���Ϣ��\n\n",c);
            printf("��  ����%s\n�绰���룺%s\n��ϵ��ַ��%s\n",y->name,y->tel,y->add);
            }
    }
    else {
    if(H->elem[pp]!=NULL&&eq(tele,H->elem[pp]->tel)==1)
    {
        printf("\n���ҳɹ���\n���ҹ��̳�ͻ����Ϊ%d������������ҪҪ���ҵ���Ϣ��\n",c);
        printf("��  ����%s\n�绰���룺%s\n��ϵ��ַ��%s\n",H->elem[pp]->name,H->elem[pp]->tel,H->elem[pp]->add);
    }
    else cout<<endl<<"���˲����ڣ����Ҳ��ɹ�!"<<endl;
    }
}


void Clear(HashTable *H)
{//���ɢ�б�
    for(int i=0;i<HASHSIZE; i++){
        if(H->elem[i]!=NULL){
        Record *p;
        p=H->elem[i];
        while(p->next!=NULL){
            Record *q=p->next;
            p->next=p->next->next;
            q->next=NULL;
        }
        H->elem[i]=NULL;
        }
    }
        H->count=0;
        search_lenth_n++;

}


void Save(Record *a)
{//���浽�ļ�
   ofstream ofs;
   ofs.open("test.txt",ios::trunc);//|ios::binary
   if(!ofs.is_open())cout<<"�ļ���ʧ��"<<endl;

    for(int i=0;i<alength;i++){
        ofs<<a[i].name<<endl<<a[i].tel<<endl<<a[i].add<<endl;

    }
        cout<<"����ɹ�"<<endl;
        ofs.close();
}


void DeleteAll()
{//����ļ�
    ofstream ofs;
    ofs.open("test.txt",ios::trunc|ios::binary);
    ofs.close();
    cout<<"�����"<<endl;
}


void menu()
{//�˵�
    printf("                ��ӭʹ�õ绰�������ϵͳ             ");
    printf("\n             1.  ����û���Ϣ                         ");
    printf("\n             2.  ��ȡ�����û���Ϣ                     ");
    printf("\n             3.  ����������                           ");
    printf("\n             4.  �Ե绰���뽨��                       ");
    printf("\n             5.  ���Ҳ���ʾ�����û����ļ�¼           ");
    printf("\n             6.  ���Ҳ���ʾ�����绰����ļ�¼         ");
    printf("\n             7.  ˢ�²˵�                             ");
    printf("\n             8.  ���浽�ļ�                           ");
    printf("\n             9.  ɾ��ĳ����Ϣ                         ");
    printf("\n             10. ����ļ�                            ");
    printf("\n             11. �˳�����                            ");
    cout<<endl<<"             ����"<<HASHSIZE;
    printf("\n   �ѽ���ɢ�б�ƽ�����ҳ��ȼ�¼�����ڱȽϣ���  ");
    for(int i=1;i<=search_lenth_n;i++){
        cout<<search_lenth[0][i]<<"   ";
    }
    printf("\n   �ѽ���ɢ�б�ĳ�ͻ�ʣ����ڱȽϣ�        ��  ");
    for(int i=1;i<=search_lenth_n;i++){
        cout<<search_lenth[1][i]<<"   ";
    }
    printf("\n");
    printf("����������Ҫ�Ĳ�����");
    printf("\n");
}


int main()
{
    int c,k=0;
    Record a[HASHSIZE];
    HashTable *H;
    H=(HashTable*)malloc(sizeof(HashTable));
    for(int i=0;i<HASHSIZE; i++){
        H->elem[i]=NULL;
    }
    H->size=HASHSIZE;
    H->count=0;

    alength=0;
    menu();
    daoru(a);
    while(1)
    {
        int num;
        cin>>num;
        switch(num)
        {
        case 1:
            if(alength>=HASHSIZE){
                cout<<"�����Ѿ��������������ܼ���,�㲻������������һ������"<<endl;
                break;
            }
            getin(a);
            Cls();
            menu();
            cout<<"��ӳɹ�"<<endl;
            if(alength>=HASHSIZE)
                cout<<"�����Ѿ��������������ɽ���Ҳ�����������"<<endl;
            break;
        case 2:
            ShowInformation(a);
            system("pause");
            Cls();
            menu();
            break;
        case 3:
            Cls();
            menu();
            if(alength>=HASHSIZE){
                cout<<"�����Ѿ��������������ɽ���,�㲻����������"<<endl;
                break;
            }
            Clear(H);
            k=Choice();
            CreateHash1(H,a,k);   // ����������ɢ�б�
            system("pause");
            Cls();
            menu();
            break;
        case 4:
            Cls();
            menu();
            Clear(H);
            k=Choice();
            CreateHash2(H,a,k);   // �Ե绰���뽨��ɢ�б�
            system("pause");
            Cls();
            menu();
            break;
        case 5:
            c=0;
            SearchHash1(H,c,k);   //��������������
            system("pause");
            Cls();
            menu();
            break;
        case 6:
            c=0;
            SearchHash2(H,c,k);   //�Ե绰�����������
            system("pause");
            Cls();
            menu();
            break;
        case 7:
            Cls();
            menu();
            break;
        case 8:
            Save(a);
            break;
        case 9:
            DeleteOne(H,a);
            break;
        case 10:
            DeleteAll();
            break;
        case 11:
            return 0;
            break;
        default:
            cout<<"�����������������!"<<endl;
        }
    }
    system("pause");
    return 0;
}



/*

1
1
����
123456
123

1
1
����
789456
612

1
1
���
568256
659

1
1
���
665456
239

1
1
����
453266
556

1
1
СС��
446955
2235

1
1
���ĳ���
654782
2236

1
1
����
556945
221

1
1
����
556987
2235

1
1
����
654236
456

1
1
��˹
657236
2256

1
1
�ܿ�
112365
552

1
1
̩��
665442
229

1
1
�α���˹
445235
154

1
1
����
556113
226

1
1
����
663289
559

1
1
������
554522
223

1
1
����
554875
2259


*/

/*

1
15
��ŷ
1532658
5565
��˹����
6632587
2265
������
3369852
2256
�ο�ɪ˹
2231598
2255
����
115875
2256
����
2285364
22368
��ӥ
3369852
6654
��Ϭ
5574896
2258
�ػ�
2365455
25222
ѩ��
2269845
2236
�ۻ�
556895
3223
����
4456932
22554
��Ӱ
4452369
22366
���
5546856
22365
����
5568422
2236







*/
