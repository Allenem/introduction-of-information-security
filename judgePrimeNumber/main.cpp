// 检测某一大数是否为素数，参考地址https://zhidao.baidu.com/question/560794399.html

#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

// 随机数产生器
// 产生m~n之间的一个随机数
unsigned long random(unsigned long m,unsigned long n)
{
    srand((unsigned long)time(NULL));
    return(unsigned long)(m+rand()%n);
}
// 模幂函数
// 返回X^YmodN
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
// Rabin-Miller素数测试，通过测试返回1，否则返回0。
// n是待测素数。
// 注意：通过测试并不一定就是素数，非素数通过测试的概率是1/4
int RabinMillerTest(unsigned long n)
{
    unsigned long b,m,j,v,i;
    // 先计算出m、j，使得n-1=m*2^j，其中m是正奇数，j是非负整数
    m = n-1;
    j = 0;
    while(!(m&1))
    {
        ++j;
        m >>= 1;
    }
    // 随机取一个b，2<=b<n-1
    b = random(2,m);
    // 计算v=b^mmodn
    v = PowMod(b,m,n);
    // 如果v==1，通过测试
    if(v == 1)
    {
        return 1;
    }
    i = 1;
    // 如果v=n-1，通过测试
    while(v!=n-1)
    {
        // 如果i==l，非素数，结束
        if(i == j)
        {
            return 0;
        }
        //v=v^2modn，i=i+1
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
    cout<<"请输入一个要判断它是否为素数的数字"<<endl;
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
        cout<<"一共通过"<<countMax<<"次测试，"<<p<<"是素数！"<<endl;
    else
        cout<<"不是素数"<<endl;
    return 0;
}


/*
//X^YmodN
#include<iostream>

using namespace std;

//模幂函数
//返回X^YmodN
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
    cout<<"请输入3个数字x,e,n"<<endl;
    cin>>x>>e>>n;
    m = PowMod(x,e,n);
    cout<<"m = x^e mod n = "<<m<<endl;
}
*/
