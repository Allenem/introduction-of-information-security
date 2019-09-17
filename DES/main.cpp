#include <bits/stdc++.h>
#define MAX_LINE 1024
#define PATH "./txt/"
using namespace std;
string k;
char encodee[2000];
char decodee[2000];
struct node
{
    int c[80];
    int d[80];
    int cd[80];
    int k_n[80];
    int l[80];
    int r[80];
    node()
    {
        memset(c,0,sizeof(c));
        memset(d,0,sizeof(d));
        memset(k_n,0,sizeof(k_n));
        memset(l,0,sizeof(l));
        memset(r,0,sizeof(r));
    }
};

char mikey[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// pc_ip 初始置换表
int pc_ip[65] = {0,58,50,42,34,26,18,10,2,
                60,52,44,36,28,20,12,4,
                62,54,46,38,30,22,14,6,
                64,56,48,40,32,24,16,8,
                57,49,41,33,25,17,9,1,
                59,51,43,35,27,19,11,3,
                61,53,45,37,29,21,13,5,
                63,55,47,39,31,23,15,7};

// pc_ip_1 逆初始置换表
int pc_ip_1[65] = {0,40,8,48,16,56,24,64,32,
                  39,7,47,15,55,23,63,31,
                  38,6,46,14,54,22,62,30,
                  37,5,45,13,53,21,61,29,
                  36,4,44,12,52,20,60,28,
                  35,3,43,11,51,19,59,27,
                  34,2,42,10,50,18,58,26,
                  33,1,41,9,49,17,57,25};

// pc_1 生成密钥时，置换选择1，56bits
int pc_1[57] = {0,57,49,41,33,25,17,9,
               1,58,50,42,34,26,18,
               10,2,59,51,43,35,27,
               19,11,3,60,52,44,36,
               63,55,47,39,31,23,15,
               7,62,54,46,38,30,22,
               14,6,61,53,45,37,29,
               21,13,5,28,20,12,4};

// pc_2 生成密钥时，置换选择2，48bits
int pc_2[49] = {0,14,17,11,24,1,5,
               3,28,15,6,21,10,
               23,19,12,4,26,8,
               16,7,27,20,13,2,
               41,52,31,37,47,55,
               30,40,51,45,33,48,
               44,49,39,56,34,53,
               46,42,50,36,29,32};

// E盒扩展变换 32bits -> 48bits
int pc_e[49] = {0,32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
               12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
               22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};

// P盒置换表 32bits
int pc_p[33] = {0,16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
               2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};

// S盒（s1~s8）压缩变换  48bits -> 32bits
int s_box[8][4][16] = {
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,

	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,10,5,14,9,

	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,

	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,

	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,

	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,

	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,

	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

/*
** @desc    F函数包含E盒扩展、异或、S盒压缩、P盒置换
** @param   r-右32bit，kn-加密密钥48bit
** @output  r-运算后的右32bit
*/
int f(int r[80],int kn[80])
{
    int x = 0;
    int e[80] = {0};
    int row = 0,column = 0,idx = 0;

    // E盒扩展得到e(Ri);
    for(int i = 1; i <= 48; i++)
        e[i] = r[pc_e[i]];

    // 异或运算得到e(Ri)^kn;
    for(int i = 1; i <= 48; i++)
        r[i] = e[i]^kn[i];

    // S盒压缩将48位分为8组，每组6位，压缩为4位，最终4×8=32位，得到S(e(Ri)^kn);
    for(int i = 1; i <= 48; i += 6)
    {
        row = r[i]*2+r[i+5]*1;
        column = r[i+1]*8+r[i+2]*4+r[i+3]*2+r[i+4]*1;
        e[++idx] = (s_box[x][row][column]>>3)&1;
        e[++idx] = (s_box[x][row][column]>>2)&1;
        e[++idx] = (s_box[x][row][column]>>1)&1;
        e[++idx] = s_box[x][row][column]&1;
        x++;
    }
    // P盒置换
    for(int i=1; i<=32; i++)
        r[i]=e[pc_p[i]];
    return 1;
}

/*
** @desc    DES_encode_decode函数加解密函数
** @param   m-要加密的明文或者要解密的密文，choice-选择加密还是解密，choice=0时是加密操作，choice=1时是解密操作
*/
int DES_encode_decode(string m,int choice)
{
    /*
    ** 转二进制
    ** 功能：将16个16进制转换成16个二进制并存到two数组
    **       k秘钥转换成二进制并存到two_k数组
    */
    int two[66] = {0},num,idx = 0,two_k[66] = {0},two_kup[66] = {0};
    // 将16个16进制转换成16个二进制:变成64位
    for(int i = 0; i < 16; i++)
    {
        if(m[i] >= '0'&& m[i] <= '9')
            num = m[i]-'0';
        else num = m[i]-'A'+10;
        two[++idx] = (num>>3)&1;
        two[++idx] = (num>>2)&1;
        two[++idx] = (num>>1)&1;
        two[++idx] = num&1;
    }
    idx=0;
    // k秘钥转2进制
    for(int i = 0; i < 16; i++)
    {
        if(k[i] >= '0'&&k[i] <= '9')
            num = k[i]-'0';
        else num = k[i]-'A'+10;
        two_k[++idx] = (num>>3)&1;
        two_k[++idx] = (num>>2)&1;
        two_k[++idx] = (num>>1)&1;
        two_k[++idx] = num&1;
    }

    //——————————————————————————————————————————————————————————————————————————————————————————————————————————

    /*
    ** 生成16个子密钥
    ** 功能：由密钥生成16轮加密所用的子密钥
    */
    // 将密钥用pc_1置换
    for(int i = 1; i <= 56; i++)
        two_kup[i]=two_k[pc_1[i]];
    // 左右分组,c_and_d[0]~c_and_d[17]。得到c[0],得到d[0]
    node c_and_d[17];
    for(int i = 1; i <= 28; i++)
        c_and_d[0].c[i] = two_kup[i];
    for(int i = 1,j = 29; j <= 56; i++,j++)
        c_and_d[0].d[i]=two_kup[j];

    // 16轮生成每轮子密钥,得到c[1]-c[15],d[1]-d[15],cd[1]-cd[16]
    for(int i=1; i<=16; i++)
    {
        // 如果为第1、2、9、16轮，则c,d循环左移1位
        if(i==1||i==2||i==9||i==16)
        {
            for(int j = 1; j <= 27; j++)
                c_and_d[i].c[j] = c_and_d[i-1].c[j+1];
            c_and_d[i].c[28] = c_and_d[i-1].c[1];
            for(int j = 1; j <= 27; j++)
                c_and_d[i].d[j] = c_and_d[i-1].d[j+1];
            c_and_d[i].d[28] = c_and_d[i-1].d[1];
        }
        // 如果是其他轮次，则c,d循环左移2位
        else
        {
            for(int j = 1; j <= 26; j++)
                c_and_d[i].c[j] = c_and_d[i-1].c[j+2];
            c_and_d[i].c[27] = c_and_d[i-1].c[1];
            c_and_d[i].c[28] = c_and_d[i-1].c[2];
            for(int j = 1; j <= 26; j++)
                c_and_d[i].d[j] = c_and_d[i-1].d[j+2];
            c_and_d[i].d[27] = c_and_d[i-1].d[1];
            c_and_d[i].d[28] = c_and_d[i-1].d[2];
        }
        // 将c，d合成cd(56bit)
        for(int j = 1; j <= 28; j++)
            c_and_d[i].cd[j] = c_and_d[i].c[j];
        for(int j = 29, t = 1; t <= 28; j++,t++)
            c_and_d[i].cd[j] = c_and_d[i].d[t];
    }

    // PC_2置换后得到k1-k16(56bit->48bit)
    node k_16[16];
    for(int i = 1; i <= 16; i++)
        for(int j = 1; j <= 48; j++)
            k_16[i].k_n[j] = c_and_d[i].cd[pc_2[j]];

    //——————————————————————————————————————————————————————————————————————————————————————————————————————————

    /*
    ** DES加密过程
    ** 功能：实现DES算法的16轮加密
    */
    int ip[80] = {0};
    // STEP1.初始变换ip
    for(int i = 1; i <= 64; i++)
        ip[i] = two[pc_ip[i]];

    // STEP2.初始化得到 l[0],r[0]
    node l_r[20];
    for(int i = 1; i <= 32; i++)              // 得到l;
        l_r[0].l[i] = ip[i];
    for(int i=1,j = 33; j <= 64; i++,j++)     // 得到r;
        l_r[0].r[i]=ip[j];

    // STEP3.进行16轮运算
    // choice=0时是加密操作
    if(choice==0)
    {
        for(int i = 1; i <= 16; i++)          // 加密16轮，计算L1-L16，R1-R16;
        {
            for(int j = 1; j <= 32; j++)      // 每轮32位，L[i] = R[i-1] , R[i] = L[i-1]^f(R[i-1])
                l_r[i].l[j] = l_r[i-1].r[j];
            f(l_r[i-1].r,k_16[i].k_n);
            for(int j = 1; j <= 32; j++)
                l_r[i].r[j] = l_r[i-1].l[j]^l_r[i-1].r[j];
        }
    }
    // choice=1时是解密操作。
    // 解密与加密的唯一区别就是f函数的密钥与加密时相反，即第1次用k_16[16],第2次用k_16[15],...,第16次用k_16[1]
    else
    {
        for(int i = 1; i <= 16; i++)           // 解密16轮，计算L1-L16，R1-R16;
        {
            for(int j = 1; j <= 32; j++)
                l_r[i].l[j] = l_r[i-1].r[j];
            f(l_r[i-1].r,k_16[16-i+1].k_n);
            for(int j = 1; j <= 32; j++)
                l_r[i].r[j] = l_r[i-1].l[j]^l_r[i-1].r[j];
        }
    }

    // STEP4.16轮后左右合在一起
    int R16L16[80] = {0};
    for(int i = 1; i <= 32; i++)
        R16L16[i] = l_r[16].r[i];
    for(int i = 33, j = 1; j <= 32; j++,i++)
        R16L16[i] = l_r[16].l[j];

    // STEP5.进行ip逆置换，得到最终变换;
    int encode[80] = {0};
    for(int i = 1; i <= 64; i++)
        encode[i] = R16L16[pc_ip_1[i]];

    //——————————————————————————————————————————————————————————————————————————————————————————————————————————

    int tem_num;
    int tem_char;
    // choice=0时是加密操作
    if(choice==0)
    {
        //字节转换成字符输出密文
        for(int i = 1; i <= 64; i += 4)
        {
            tem_num = encode[i]*8+encode[i+1]*4+encode[i+2]*2+encode[i+3]*1;
            if(tem_num >= 10)
            {
                tem_char = (tem_num-10)+'A';
                printf("%c",(tem_num-10)+'A');
            }
            else
            {
                tem_char = tem_num+'0';
                printf("%c",tem_num+'0');
            }
            strcat(encodee,(char*)&tem_char); // 加密字符拼接到一起
        }
    }
    // choice=1时是解密操作
    else
    {
        int change[1000];
        int pos = 0;
        for(int i = 1; i <= 64; i += 4)
        {
            tem_num = encode[i]*8+encode[i+1]*4+encode[i+2]*2+encode[i+3]*1;
            change[++pos] = tem_num;
        }
        int decode = 0;
        for(int i = 1; i <= 16; i += 2)
        {
            decode += change[i];
            decode *= 16;
            decode += change[i+1];
            printf("%c",decode);
            strcat(decodee,(char*)&decode); // 解密字符拼接到一起
            decode = 0;
        }
    }
    return 1;
}

int main()
{
    while(1)
    {
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"|                                                          |"<<endl;
        cout<<"|                     DES加密解密                          |"<<endl;
        cout<<"|                                                          |"<<endl;
        cout<<"|              字符串加密    请输入1                       |"<<endl;
        cout<<"|              字符串解密    请输入2                       |"<<endl;
        cout<<"|              文件加密      请输入3                       |"<<endl;
        cout<<"|              文件解密      请输入4                       |"<<endl;
        cout<<"|              退出          请输入其他任意键              |"<<endl;
        cout<<"|                                                          |"<<endl;
        cout<<"|                                         copyright: 蒲尧  |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        printf("\n");
        cout<<"STEP1.请输入选项："<<endl;
        int choice;
        cin>>choice;

        // ————————————————————————————————————————————————————————————————————————————————————————————————————————————

        // 1.实现字符串加密

        if(choice==1)
        {
            k="";
            getchar();
            srand((int)time(0));
            cout<<"STEP2.请输入明文:"<<endl;
            char plaintext[1000];
            gets(plaintext);

            // 生成随机密钥k(64bit=16个16进制数)
            cout<<"正在产生随机密钥......"<<endl;
            int num;
            for(int i = 1; i <= 16; i++)
                num = rand()%16,k += mikey[num];
            cout<<"生成成功,密钥为:\n"<<k<<endl;

            cout<<"密文为:"<<endl;
            int len = strlen(plaintext),idx = 0;
            char hex[2000],tem[1000];
            int now = 0;
            // 文本转16进制
            for(int i = 0; i < len; i++)
            {
                while(plaintext[i])
                {
                    if(plaintext[i]%16 >= 10) tem[++idx] = ((plaintext[i]%16)-10)+'A';
                    else tem[++idx] = (plaintext[i]%16)+'0';
                    plaintext[i] /= 16;
                }
                //倒序存入
                for(int j = idx; j >= 1; j--)
                    hex[++now]=tem[j];
                idx = 0;
            }
            // 不够16位补0；
            while(now%16)
            {
                ++now;
                hex[now] = '0';
            }
            int sum = 0;
            string m = "";
            for(int i = 1; i <= now; i++)
            {
                sum++;
                m += hex[i];
                // 每64位加密一次
                if(sum==16)
                {
                    sum=0;
                    DES_encode_decode(m,0);
                    m="";
                }
            }
            printf("\n\n");
        }

        // ————————————————————————————————————————————————————————————————————————————————————————————————————————————

        // 2.实现字符串+密钥 解密

        else if(choice==2)
        {
            getchar();
            cout<<"STEP2.请输入密文:"<<endl;
            char hex[1000];
            gets(hex);
            cout<<"STEP3.请输入密钥:"<<endl;
            cin>>k;
            cout<<"明文为:"<<endl;
            int len = strlen(hex);
            int sum = 0;
            string m = "";
            for(int i = 0; i<len; i++) //每64位解密一次；
            {
                sum++;
                m += hex[i];
                if(sum==16)
                {
                    sum=0;
                    DES_encode_decode(m,1);
                    m="";
                }
            }
            printf("\n\n");
        }

        // ————————————————————————————————————————————————————————————————————————————————————————————————————————————

        // 3.实现读取文本+文本加密+写入文本

        else if(choice==3)
        {
            memset(encodee,'\0',sizeof(encodee));
            memset(decodee,'\0',sizeof(decodee));
            k = "C7392539914812E3";                       // 固定密钥，方便下面解密
            char ifn[10];                                 // 读文件名
            char ofn[10];                                 // 写文件名
            char PathAndName[128] = {0};

            // ——————————————
            // 读取文件部分
            cout<<"STEP2.请输入需要加密的文件名:"<<endl;  // message.txt
            cin>>ifn;
            sprintf(PathAndName,PATH"%s",ifn);
            char buf[MAX_LINE];                           // 缓冲区
            FILE *fp;                                     // 文件指针
            int leng;                                     //行字符个数
            if((fp = fopen(PathAndName,"r")) == NULL)
            {
                perror("fail to read");
                exit (1) ;
            }
            while(fgets(buf,MAX_LINE,fp) != NULL)
            {
                leng = strlen(buf);
                buf[leng-1] = '\0';                       //去掉换行符
                printf("%s %s \n%s %d \n","明文：",buf,"长度：",leng - 1);
            }
            // ——————————————

            // ——————————————
            // 加密部分
            cout<<"密文为:"<<endl;
            int len = strlen(buf),idx = 0;
            char hex[2000],tem[1000];
            int now = 0;
            // 文本转16进制
            for(int i = 0; i < len; i++)
            {
                while(buf[i])
                {
                    if(buf[i]%16 >= 10) tem[++idx] = ((buf[i]%16)-10)+'A';
                    else tem[++idx] = (buf[i]%16)+'0';
                    buf[i] /= 16;
                }
                //倒序存入
                for(int j = idx; j >= 1; j--)
                    hex[++now]=tem[j];
                idx = 0;
            }
            // 不够16位补0；
            while(now%16)
            {
                ++now;
                hex[now] = '0';
            }
            int sum = 0;
            string m = "";
            for(int i = 1; i <= now; i++)
            {
                sum++;
                m += hex[i];
                // 每64位加密一次
                if(sum==16)
                {
                    sum=0;
                    DES_encode_decode(m,0);
                    m="";
                }
            }
            cout<<"\n写入密文为:\n"<<encodee<<endl; // 这里是将之前一个一个的字符集拼接成一个字符串了
            PathAndName[128] = {0};
            // ——————————————

            // ——————————————
            // 写入文件部分
            cout<<"\nSTEP3.请输入加密后想要的文件名:"<<endl;  // encode.txt
            cin>>ofn;
            sprintf(PathAndName,PATH"%s",ofn);
            FILE *fp2=fopen(PathAndName,"w");
            fprintf(fp2,encodee);
            fclose(fp2);
            cout<<"写入完成"<<endl;
            PathAndName[128] = {0};
            // ——————————————

            printf("\n\n");
        }

        // ————————————————————————————————————————————————————————————————————————————————————————————————————————————

        // 4.实现读取文本+文本解密+写入文本

        else if(choice==4)
        {
            memset(encodee,'\0',sizeof(encodee));         // 置空，也可以 bzero(a,sizeof(a))
            memset(decodee,'\0',sizeof(decodee));
            k = "C7392539914812E3";                       // 固定密钥解密
            char ifn[10];                                 // 读文件名
            char ofn[10];                                 // 写文件名
            char PathAndName[128] = {0};

            // ——————————————
            // 读取文件部分
            cout<<"STEP2.请输入需要解密的文件名:"<<endl;  // encode.txt
            cin>>ifn;
            sprintf(PathAndName,PATH"%s",ifn);
            char buf[MAX_LINE];                           // 缓冲区
            FILE *fp;                                     // 文件指针
            int leng;                                     //行字符个数
            if((fp = fopen(PathAndName,"r")) == NULL)
            {
                perror("fail to read");
                exit (1) ;
            }
            while(fgets(buf,MAX_LINE,fp) != NULL)
            {
                leng = strlen(buf);
                //buf[leng-1] = '\0';                       //去掉换行符
                printf("%s %s \n%s %d \n","密文：",buf,"长度：",leng - 1);
            }
            // ——————————————

            // ——————————————
            // 解密部分
            cout<<"明文为:"<<endl;
            int len = strlen(buf);
            int sum = 0;
            string m = "";
            for(int i = 0; i<len; i++) //每64位解密一次；
            {
                sum++;
                m += buf[i];
                if(sum==16)
                {
                    sum=0;
                    DES_encode_decode(m,1);
                    m="";
                }
            }
            PathAndName[128] = {0};
            cout<<"\n写入解码明文为:\n"<<decodee<<endl; // 这里是将之前一个一个的字符集拼接成一个字符串了
            // ——————————————

            // ——————————————
            // 写入文件部分
            cout<<"\nSTEP3.请输入解密后想要的文件名:"<<endl;  // decode.txt
            cin>>ofn;
            sprintf(PathAndName,PATH"%s",ofn);
            FILE *fp2=fopen(PathAndName,"w");
            fprintf(fp2,decodee);
            fclose(fp2);
            cout<<"写入完成"<<endl;
            PathAndName[128] = {0};
            // ——————————————

            printf("\n\n");
        }

        // ————————————————————————————————————————————————————————————————————————————————————————————————————————————

        // 其他任意键，退出

        else
            return 0;
    }
    return 0;
}
