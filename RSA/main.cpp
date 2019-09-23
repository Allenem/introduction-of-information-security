#include<bits/stdc++.h>
#include<cmath>
#define MAXLENGTH 500      // 明文最大长度，即所允许的最大整数个数

using namespace std;

int size = 0;              // 保存要加密的正整数个数
int p,q;
int n,phi;                 // n=p*q,phi=(p-1)*(q-1)
int e,d;                   // {e,n}为公钥,{d,n}为私钥
int cleartext[MAXLENGTH],Ciphertext[MAXLENGTH];//分别用于存放加密前的明文和加密后的密文
int DecryptionText[MAXLENGTH];//存放解密后的明文

//——————————————————————————————————————————————————————

/*
** @desc   加密算法
** @param  直接运行，输入素数p,q
*/
void Encryption()
{
    cout<<"请输入两个较大的素数"<<endl;
    cin>>p>>q;
    // 判断某数是否为素数
    /*
    #include <stdio.h>
    int main()
    {
        int i,n;
        scanf("%d",&n);
        for(i=2;i*i<=n;i++)
            if(n%i==0)break;
        printf("%s\n",n%i==0?"No":"Yes");
        return 0;
    }
    */
    {
        int i;
        for(i=2;i*i<=p;i++)
            if(p%i==0)
            {
                printf("%s\n","p不是素数");return;
            }
        printf("%s\n","p是素数");
    }
    {
        int i;
        for(i=2;i*i<=q;i++)
            if(q%i==0)
            {
                printf("%s\n","q不是素数");return;
            }
        printf("%s\n","q是素数");
    }
    cout<<"p="<<p<<",q="<<q<<endl;
    n = p*q;
    phi = (p-1)*(q-1);
    cout<<"n="<<n<<",phi="<<phi<<endl;
    cout<<"请从[0，"<<phi-1<<"]中选择一个与"<<phi<<"互素的数e:";
    cin>> e;
    // 判断两数是否互质，即最大公约数是否为1
    /*
    int gcd(int x,int y)
    {
        int t;
        while (y) t=x, x=y, y=t%y;
        return x; // 最大公约数
    }
    */
    {
        int t,x=phi,y=e;
        while (y) t=x, x=y, y=t%y;
        if(x!=1)
            {
                printf("%d%s%d%s\n",phi,"和",e,"不互质");return;
            }
    }
    // 求解乘法逆元e*d = 1 (mod phi)
    float d0;
    for(int i=1;;i++)
    {
        d0 = (float)(phi*i+1) / e;
        if( d0-(int)d0 == 0 )
            break;
    }
    d = (int)d0;
    cout << endl;
    cout <<"e="<<e<<",d="<<d<< endl;
    cout <<"公开密钥 Pk = {e,n} = {"<< e <<","<< n <<"}"<< endl;
    cout <<"私密密钥 Pk = {d,n} = {"<< d <<","<< n <<"}"<< endl;
    cout << endl;
    cout <<"请输入要加密的小于"<< n <<"正整数(以-1结束) :"<<endl;
    cout <<"加密前的明文为:";
    for(int i = 0; i < MAXLENGTH; i++)
        Ciphertext[i] = 1;
    int count;
    int j;
    for(j = 0; j < MAXLENGTH; j++)
    {
        cin >> cleartext[j];
        if( cleartext[j] == -1 )break;
        count = e;
        while(count > 0)
        {
            // 明文加密 Ciphertext=(cleartext)^e mod n
            Ciphertext[j] = (Ciphertext[j] * cleartext[j]) % n;
            // 加密算法
            count--;
        }
    }
    cout<<"密文为：";
    size = j;
    for(int k=0; k<j; k++)
        cout<<Ciphertext[k]<<" ";
    cout<<endl;
}

//——————————————————————————————————————————————————————

/*
** @desc   解密算法
** @param  输入y或者Y时运行
*/
void Decryption()
{
for(int i= 0; i < MAXLENGTH; i++)
    DecryptionText[i] = 1;
    int count;
    for(int j = 0; j < size; j++)
    {
        count = d;
        while(count > 0)
        {
            //对密文进行解密DecryptionText = (Ciphertext) ^ d (mod n)
            DecryptionText[j] = ((DecryptionText[j] * Ciphertext[j]) %n) ;
            count-- ;
        }
    }
    cout <<"解密后的明文为:";
    for( int k = 0; k< size; k++)
        cout << DecryptionText[k] <<"";
    cout << endl ;
    cout <<"加密前的明文为:";
    for( int k =0;k<size; k++)
        cout << cleartext[k] <<"";
    cout << endl;
}


int main()
{

    Encryption();
    char c;
    cout<<endl;
    cout<<"是否要解密(Y or N):";
    cin>>c;
    if(c =='y'||c =='Y')
        Decryption() ;
    else
        return 1;
    return 1;
}
