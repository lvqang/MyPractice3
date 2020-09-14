#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<cstring>
using namespace std;
class LZW
{
public:
        LZW(int left=false, int lefO=0):bitsLeftOver(left), leftOver(lefO){}
        //输入输出流
        void com_setFiles(int argc,  char *argv[ ]);
        //压缩
        void compress( );
        void com_output(int pcode);
        //解压缩
        void decom_setFiles(int argc,  char *argv[ ]);
        void decom_output(int pcode);
        bool getCode(int &pcode);
        void decompress();


        map<long, int> h;//关键字，代码
        int codesUsed;
private:
        ifstream in;
        ofstream out;

        int bitsLeftOver;
        int leftOver;
        const unsigned char MASK1 = 255;
        const unsigned char MASK2 = 15;
        const int BYTE_SIZE = 8;//8
       const int EXCESS = 4;//4
       const int ALPHA = 256;
       const static int MAX_CODES= 4096 ;//数组纬度，必须设置成静态常量，即全局变量，且不能改变(也可以在类外声明)

      //unordered_map<long, int> h;//关键字，代码

       typedef pair<int, char> typepair;
       typepair ht[MAX_CODES];//解压缩容器

       char s[MAX_CODES];
       int size=0;
};
