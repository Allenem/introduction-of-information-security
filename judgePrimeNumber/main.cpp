// ���ĳһ�����Ƿ�Ϊ�������ο���ַhttps://zhidao.baidu.com/question/560794399.html

#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

// �����������
// ����m~n֮���һ�������
unsigned long random(unsigned long m,unsigned long n)
{
    srand((unsigned long)time(NULL));
    return(unsigned long)(m+rand()%n);
}
// ģ�ݺ���
// ����X^YmodN
long PowMod(long x,long y,long n)
{
    long s,t,u;
    s = 1;
    t = x;
    u = y;
    while(u)
    {
        if(u&1)
            s = (s*t)%n;
        u >>= 1;
        t = (t*t)%n;
    }
    return s;
}
// Rabin-Miller�������ԣ�ͨ�����Է���1�����򷵻�0��
// n�Ǵ���������
// ע�⣺ͨ�����Բ���һ������������������ͨ�����Եĸ�����1/4
int RabinMillerTest(unsigned long n)
{
    unsigned long b,m,j,v,i;
    // �ȼ����m��j��ʹ��n-1=m*2^j������m����������j�ǷǸ�����
    m = n-1;
    j = 0;
    while(!(m&1))
    {
        ++j;
        m >>= 1;
    }
    // ���ȡһ��b��2<=b<n-1
    b = random(2,m);
    // ����v=b^mmodn
    v = PowMod(b,m,n);
    // ���v==1��ͨ������
    if(v == 1)
    {
        return 1;
    }
    i = 1;
    // ���v=n-1��ͨ������
    while(v!=n-1)
    {
        // ���i==l��������������
        if(i == j)
        {
            return 0;
        }
        //v=v^2modn��i=i+1
        v = PowMod(v,2,n);
        i++;
    }
    return 1;
}

int main()
{
    unsigned long p;
    int count = 0;
    int countMax = 10;
    cout<<"������һ��Ҫ�ж����Ƿ�Ϊ����������"<<endl;
    cin>>p;
    for(int temp = 0; temp < countMax; temp++)
    {
        if(RabinMillerTest(p))
        {
            count++;
        }
        else
            break;
    }
    if(count == countMax)
        cout<<"һ��ͨ��"<<countMax<<"�β��ԣ�"<<p<<"��������"<<endl;
    else
        cout<<"��������"<<endl;
    return 0;
}


/*
//X^YmodN
#include<iostream>

using namespace std;

//ģ�ݺ���
//����X^YmodN
long PowMod(long x,long y,long n)
{
    long s,t,u;
    s = 1;
    t = x;
    u = y;
    while(u)
    {
        if(u&1)
            s = (s*t)%n;
        u >>= 1;
        t = (t*t)%n;
    }
    return s;
}

int main(){
    unsigned long x,e,n,m;
    cout<<"������3������x,e,n"<<endl;
    cin>>x>>e>>n;
    m = PowMod(x,e,n);
    cout<<"m = x^e mod n = "<<m<<endl;
}
*/
