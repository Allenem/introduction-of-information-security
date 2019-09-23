#include<bits/stdc++.h>
#include<cmath>
#define MAXLENGTH 500      // ������󳤶ȣ���������������������

using namespace std;

int size = 0;              // ����Ҫ���ܵ�����������
int p,q;
int n,phi;                 // n=p*q,phi=(p-1)*(q-1)
int e,d;                   // {e,n}Ϊ��Կ,{d,n}Ϊ˽Կ
int cleartext[MAXLENGTH],Ciphertext[MAXLENGTH];//�ֱ����ڴ�ż���ǰ�����ĺͼ��ܺ������
int DecryptionText[MAXLENGTH];//��Ž��ܺ������

//������������������������������������������������������������������������������������������������������������

/*
** @desc   �����㷨
** @param  ֱ�����У���������p,q
*/
void Encryption()
{
    cout<<"�����������ϴ������"<<endl;
    cin>>p>>q;
    // �ж�ĳ���Ƿ�Ϊ����
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
                printf("%s\n","p��������");return;
            }
        printf("%s\n","p������");
    }
    {
        int i;
        for(i=2;i*i<=q;i++)
            if(q%i==0)
            {
                printf("%s\n","q��������");return;
            }
        printf("%s\n","q������");
    }
    cout<<"p="<<p<<",q="<<q<<endl;
    n = p*q;
    phi = (p-1)*(q-1);
    cout<<"n="<<n<<",phi="<<phi<<endl;
    cout<<"���[0��"<<phi-1<<"]��ѡ��һ����"<<phi<<"���ص���e:";
    cin>> e;
    // �ж������Ƿ��ʣ������Լ���Ƿ�Ϊ1
    /*
    int gcd(int x,int y)
    {
        int t;
        while (y) t=x, x=y, y=t%y;
        return x; // ���Լ��
    }
    */
    {
        int t,x=phi,y=e;
        while (y) t=x, x=y, y=t%y;
        if(x!=1)
            {
                printf("%d%s%d%s\n",phi,"��",e,"������");return;
            }
    }
    // ���˷���Ԫe*d = 1 (mod phi)
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
    cout <<"������Կ Pk = {e,n} = {"<< e <<","<< n <<"}"<< endl;
    cout <<"˽����Կ Pk = {d,n} = {"<< d <<","<< n <<"}"<< endl;
    cout << endl;
    cout <<"������Ҫ���ܵ�С��"<< n <<"������(��-1����) :"<<endl;
    cout <<"����ǰ������Ϊ:";
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
            // ���ļ��� Ciphertext=(cleartext)^e mod n
            Ciphertext[j] = (Ciphertext[j] * cleartext[j]) % n;
            // �����㷨
            count--;
        }
    }
    cout<<"����Ϊ��";
    size = j;
    for(int k=0; k<j; k++)
        cout<<Ciphertext[k]<<" ";
    cout<<endl;
}

//������������������������������������������������������������������������������������������������������������

/*
** @desc   �����㷨
** @param  ����y����Yʱ����
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
            //�����Ľ��н���DecryptionText = (Ciphertext) ^ d (mod n)
            DecryptionText[j] = ((DecryptionText[j] * Ciphertext[j]) %n) ;
            count-- ;
        }
    }
    cout <<"���ܺ������Ϊ:";
    for( int k = 0; k< size; k++)
        cout << DecryptionText[k] <<"";
    cout << endl ;
    cout <<"����ǰ������Ϊ:";
    for( int k =0;k<size; k++)
        cout << cleartext[k] <<"";
    cout << endl;
}


int main()
{

    Encryption();
    char c;
    cout<<endl;
    cout<<"�Ƿ�Ҫ����(Y or N):";
    cin>>c;
    if(c =='y'||c =='Y')
        Decryption() ;
    else
        return 1;
    return 1;
}
