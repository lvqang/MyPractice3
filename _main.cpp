#include"class.h"

int  main(int argc, char *argv[ ] )
{
        class LZW  lzwTest;
        int k;//1:in 2:out
        cout<<"compress(1) or decompress(2):";
        cin>>k;
        if(k==1)
        {
                lzwTest.com_setFiles(argc,  argv);
                lzwTest.compress();
        }
        else
        {
                lzwTest.decom_setFiles(argc,  argv);
                lzwTest.decompress();
        }



       return 0;
}
