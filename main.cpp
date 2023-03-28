#include<iostream>
#include<fstream>
#include <string.h>
#include <windows.h>
#define MAX_SIZE 20                 //人名的最大长度
#define HASHSIZE 30             //定义表长
#define ok 1
#define error -1
typedef char CH[MAX_SIZE];
using namespace std;
typedef struct Record
{//记录
    CH name;
    CH tel;
    CH add;
    struct Record *next=NULL;
} Record;

typedef struct
{//散列表
    Record *elem[HASHSIZE];                 //数据元素存储基址
    int count;                              //当前数据元素个数
    int size;                               //当前容量
} HashTable;

//全局变量
int search_lenth_n=0;
double search_lenth[2][10]={0};//平均查找长度记录
int alength;//a数组个数
int NUM_BER;//新增个数
int random[10]={1,3,9,7,2,5,6,4,8,0};//伪随机数序列

void Cls()
{//清屏
    printf("*");
    system("cls");
}


int eq(CH x,CH y)
{//比较是否相等
    //关键字比较，相等返回1；否则返回-1
    if(strcmp(x,y)==0)
        return ok;
    else return error;
}


void getin(Record* a)
{//添加函数
    cout<<"输入要添加的个数："<<endl;
    cin>>NUM_BER;
    int i;
    for(i=alength;i<alength+NUM_BER; i++)
    {

        printf("请输入第%d个记录的用户名:\n",i+1);
        //scanf("%s",a[i].name);
        cin>>a[i].name;
        printf("请输入%d个记录的电话号码:\n",i+1);
        //scanf("%s",a[i].tel);
        cin>>a[i].tel;
        printf("请输入第%d个记录的地址:\n",i+1);
        //scanf("%s",a[i].add);
        cin>>a[i].add;

    }
    alength=alength+NUM_BER;
}


int daoru(Record* a)
{//导入文件里的信息

    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open())cout<<"打开文件失败";

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
{//显示用户信息
    int i;
    if(alength==0){
        cout<<"目前无输入"<<endl;
    }
    for( i=0; i<alength; i++)
        printf("\n第%d个用户信息:\n 姓名：%s\n 电话号码：%s\n 联系地址：%s\n",i+1,a[i].name,a[i].tel,a[i].add);
}


long fold(CH s)
{//人名的处理
    char *p;
    long sum=0;
    CH ss;
    strcpy(ss,s);
    strupr(ss);                              //将字符串ss转换为大写形式
    p=ss;
    while(*p!='\0'){
        sum+=*p;
        p++;
    }
   // printf("\n表的地址总数%ld",sum);
    return sum;
}


int Hash1(CH str)
{//姓名建表的散列函数
    long n;
    int m;
    n=fold(str);                          //先将用户名进行折叠处理
    m=n%HASHSIZE;                        //折叠处理后的数，用除留余数法构造散列函数
    if(m<0){
        m=m+HASHSIZE;
    }
    return m;                             //并返回模值
}


int Hash2(CH str)
{//电话建表的散列函数

    long n;
    int m;
    n = atoi(str);                        //把字符串转换成整型的函数.
    m=n%HASHSIZE;                         //用除留余数法构造散列函数
    return m;                             //并返回模值
}


int Choice()
{//选择解决冲突方法
    cout<<"---------------------"<<endl;
    cout<<"-1.线性探测再散列法--"<<endl;
    cout<<"-2.二次探测再散列法--"<<endl;
    cout<<"-3.伪随机探测再散列法"<<endl;
    cout<<"-4.链地址法----------"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"请输入解决冲突方式："<<endl;
    int k;
    cin>>k;
     switch(k)
    {
    case 1:
        cout<<"线性探测再散列法创建散列表结果："<<endl;
        break;
    case 2:
        cout<<"二次探测再散列法创建散列表结果："<<endl;
        break;
    case 3:
        cout<<"伪随机探测再散列法创建散列表结果："<<endl;
        break;
    case 4:
        cout<<"链地址法创建散列表结果："<<endl;
        break;
    default:
        cout<<"输入错误，请重新输入!"<<endl;
    }
    return k;
}


int collision_1(int p,int &c)
{//线性探测再散列法解决冲突函数
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
{//二次探测再散列法解决冲突函数
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
{//伪随机探测再散列法解决冲突函数
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
{//链地址法解决冲突函数
    if(x==0){//创建
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
{//选择解决冲突方法
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
        cout<<"输入错误，请重新输入!"<<endl;
    }
    return 0;
}


void Average_lenth(int k,int x)
{//求平均查找长度
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
        cout<<"平均查找长度为："<<r_1<<endl;
        cout<<"冲突率为      ："<<r_2<<endl;
    }
}

void DeleteOne(HashTable* H,Record* a)
{//删除一个节点
    int x;
    cout<<"1.按名字删除"<<endl;
    cout<<"2.按电话删除"<<endl;
    cin>>x;
    CH s;
    cout<<"请输入删除信息"<<endl;
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
        cout<<"删除成功"<<endl;
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
        cout<<"删除成功"<<endl;
        }

    }
}

void CreateHash1(HashTable* H,Record* a,int k)
{//以姓名为关键字，建立相应的散列表，并解决相应的冲突
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
                printf("第%d记录无法解决冲突",i+1);
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

            printf("第%d个记录的名字为%s,散列地址为%d，冲突次数为%d。\n",i+1,t->name,p,c);
        }
        else{
            H->elem[pp]=&(a[i]);                      //求得散列地址，将信息存入
            printf("第%d个记录的名字为%s,散列地址为%d，冲突次数为%d。\n",i+1,H->elem[pp]->name,pp,c); //需要显示冲突次数时输出
         }
        H->count++;
        if(H->count==HASHSIZE)
            cout<<"已经达到最大表长"<<endl;
        Average_lenth(c,0);
    }
    printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n",HASHSIZE,H->count);
    Average_lenth(0,1);
}


void SearchHash1(HashTable* H,int &c,int k)
{//在通讯录里查找姓名
    CH str;
    cout<<endl<<"请输入要查找记录的姓名："<<endl;
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
                cout<<endl<<"此人不存在，查找不成功!"<<endl;
            }
            else {
                    while(eq(str,y->name)==-1){
                if(y->next==NULL){
                    cout<<endl<<"此人不存在，查找不成功!"<<endl;
                    break;
                }
                else{
                    y=y->next;
                    c++;
                }
            }
            printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n\n",c);
            printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n",y->name,y->tel,y->add);
            }
    }

    else{
     if(H->elem[pp]!=NULL&&eq(str,H->elem[pp]->name)==1)
     {
        printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n\n",c);
        printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n",H->elem[pp]->name,H->elem[pp]->tel,H->elem[pp]->add);
     }
     else cout<<endl<<"此人不存在，查找不成功!"<<endl;
     }
}


void CreateHash2(HashTable* H,Record* a,int k)
{//以电话为关键字，建立相应的散列表，并解决相应的冲突
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
                printf("第%d记录无法解决冲突",i+1);   //需要显示冲突次数时输出
                continue;
            }                                      //无法解决冲突，跳入下一循环(即+1)
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

            printf("第%d个记录的电话为%s,散列地址为%d，冲突次数为%d。\n",i+1,t->tel,p,c);
        }
        else {
        H->elem[pp]=&(a[i]);                      //求得散列地址，将信息存入
        printf("第%d个记录的电话为%s,散列地址为%d，冲突次数为%d。\n",i+1,H->elem[pp]->tel,pp,c);//需要显示冲突次数时输出
        }
        H->count++;
        if(H->count==HASHSIZE)
        cout<<"已经达到最大表长"<<endl;
        Average_lenth(c,0);
    }
    printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n",HASHSIZE,H->count);
    Average_lenth(0,1);
}


void SearchHash2(HashTable* H,int &c,int k)
{//在通讯录里查找电话号码
    CH tele;
    cout<<endl<<"请输入要查找记录的电话号码："<<endl;
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
                cout<<endl<<"此人不存在，查找不成功!"<<endl;
            }
            else {
                    while(eq(tele,y->tel)==-1){
                if(y->next==NULL){
                    cout<<endl<<"此人不存在，查找不成功!"<<endl;
                    break;
                }
                else{
                    y=y->next;
                    c++;
                }
            }
            printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n\n",c);
            printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n",y->name,y->tel,y->add);
            }
    }
    else {
    if(H->elem[pp]!=NULL&&eq(tele,H->elem[pp]->tel)==1)
    {
        printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n",c);
        printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n",H->elem[pp]->name,H->elem[pp]->tel,H->elem[pp]->add);
    }
    else cout<<endl<<"此人不存在，查找不成功!"<<endl;
    }
}


void Clear(HashTable *H)
{//清空散列表
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
{//保存到文件
   ofstream ofs;
   ofs.open("test.txt",ios::trunc);//|ios::binary
   if(!ofs.is_open())cout<<"文件打开失败"<<endl;

    for(int i=0;i<alength;i++){
        ofs<<a[i].name<<endl<<a[i].tel<<endl<<a[i].add<<endl;

    }
        cout<<"保存成功"<<endl;
        ofs.close();
}


void DeleteAll()
{//清空文件
    ofstream ofs;
    ofs.open("test.txt",ios::trunc|ios::binary);
    ofs.close();
    cout<<"已清空"<<endl;
}


void menu()
{//菜单
    printf("                欢迎使用电话号码查找系统             ");
    printf("\n             1.  添加用户信息                         ");
    printf("\n             2.  读取所有用户信息                     ");
    printf("\n             3.  以姓名建表                           ");
    printf("\n             4.  以电话号码建表                       ");
    printf("\n             5.  查找并显示给定用户名的记录           ");
    printf("\n             6.  查找并显示给定电话号码的记录         ");
    printf("\n             7.  刷新菜单                             ");
    printf("\n             8.  保存到文件                           ");
    printf("\n             9.  删除某人信息                         ");
    printf("\n             10. 清空文件                            ");
    printf("\n             11. 退出程序                            ");
    cout<<endl<<"             最大表长"<<HASHSIZE;
    printf("\n   已建立散列表平均查找长度记录（用于比较）：  ");
    for(int i=1;i<=search_lenth_n;i++){
        cout<<search_lenth[0][i]<<"   ";
    }
    printf("\n   已建立散列表的冲突率（用于比较）        ：  ");
    for(int i=1;i<=search_lenth_n;i++){
        cout<<search_lenth[1][i]<<"   ";
    }
    printf("\n");
    printf("请输入你想要的操作：");
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
                cout<<"人数已经超过最大表长，不能加了,你不听？？？？换一个操作"<<endl;
                break;
            }
            getin(a);
            Cls();
            menu();
            cout<<"添加成功"<<endl;
            if(alength>=HASHSIZE)
                cout<<"人数已经超过最大表长，不可建表，也不能再添加了"<<endl;
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
                cout<<"人数已经超过最大表长，不可建表,你不听？？？？"<<endl;
                break;
            }
            Clear(H);
            k=Choice();
            CreateHash1(H,a,k);   // 以姓名建立散列表
            system("pause");
            Cls();
            menu();
            break;
        case 4:
            Cls();
            menu();
            Clear(H);
            k=Choice();
            CreateHash2(H,a,k);   // 以电话号码建立散列表
            system("pause");
            Cls();
            menu();
            break;
        case 5:
            c=0;
            SearchHash1(H,c,k);   //以姓名查找数据
            system("pause");
            Cls();
            menu();
            break;
        case 6:
            c=0;
            SearchHash2(H,c,k);   //以电话号码查找数据
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
            cout<<"输入错误，请重新输入!"<<endl;
        }
    }
    system("pause");
    return 0;
}



/*

1
1
张三
123456
123

1
1
李四
789456
612

1
1
婉儿
568256
659

1
1
孙策
665456
239

1
1
大大怪
453266
556

1
1
小小怪
446955
2235

1
1
开心超人
654782
2236

1
1
迪迦
556945
221

1
1
戴拿
556987
2235

1
1
赛文
654236
456

1
1
艾斯
657236
2256

1
1
杰克
112365
552

1
1
泰罗
665442
229

1
1
梦比优斯
445235
154

1
1
盖亚
556113
226

1
1
泽塔
663289
559

1
1
贝利亚
554522
223

1
1
初代
554875
2259


*/

/*

1
15
雷欧
1532658
5565
埃斯特拉
6632587
2265
尤利安
3369852
2256
奈克瑟斯
2231598
2255
格蕾
115875
2256
炎龙
2285364
22368
风鹰
3369852
6654
黑犀
5574896
2258
地虎
2365455
25222
雪獒
2269845
2236
帝皇
556895
3223
刑天
4456932
22554
飞影
4452369
22366
金刚
5546856
22365
修罗
5568422
2236







*/
