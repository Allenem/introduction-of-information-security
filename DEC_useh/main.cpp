#include "des.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
    unsigned char key[8] = {'a','b','c','d','a','b','c','d'};
    des_key skey;
    des_setup(key,8,0,&skey);
    FILE *fdl;
    FILE *fd2;
    FILE *fd3;
    fd1 = fopen("plaintextl.txt" ,"rb");
    fd2 = fopen("cipertext.txt","wb");

    int count = 0;
    unsigned char p_buf[8];
    unsigned char c_buf[8];
    while(true)
    {
        count = fread(p_buf,sizeof(unsigned char),8,fd1);
        if(count<8)
            for(int i = count; i <= 7; i++)
                p_buf[i] = '\0';
        des_ecb_encrypt(p_buf,c_buf,&skey);
        fwrite(c_buf,sizeof(unsigned char),8,fd2);
        if(count<8)
            break;
        count = 0;
    }
    fclose(fd1);
    fclose(fd2);
    fd2 = fopen("cipertex.txt","rb");
    fd3 = fopen("plaintext2.txt","wb");

    while(true)
    {
        count = fread(p_ buf,sizeof(unsigned char),8,fd2);
        if(count= =0)
        break;
        des_ecb_decrypt(p_buf,c_buf,&skey);
        fwrite(c_buf,sizeof(unsigned char),8,fd3);
        count=0;
    }
    fclose(fd2);
    fclose(fd3);
    system("PAUSE");
    return 0;

}


