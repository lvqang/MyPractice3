#include"class.h"

void LZW::com_setFiles(int argc,  char *argv[ ])
{
        string inputFile,outputFile;//保存压缩文件
        if(argc>=2)
        {
                inputFile = string(argv[1]);
        }
        else
        {
                cout<<"Please enter name of file to compress:"<<endl;
                cin>>inputFile;
        }
        in.open(inputFile,  ios::binary);//先定义文件流需要靠这个函数绑定文件
        if( !(in) )
        {
                cerr<<"Cannot open "<<inputFile<<endl;
                exit(1);
                //return;
        }
        outputFile=inputFile;
        outputFile.replace(outputFile.size()-4, 4,"zzz.txt" );
        out.open(outputFile,  ios::binary);
}

void LZW::com_output(int pcode)
{
        int c, d;
        if(bitsLeftOver)
        {
                c=int(leftOver<<EXCESS)|(pcode>>BYTE_SIZE);
                d=int(pcode&MASK1);
                out.put(c);
                out.put(d);
                bitsLeftOver=false;
        }
        else
        {
                c=int(pcode>>EXCESS);
                leftOver=pcode&MASK2;
                out.put(c);
                bitsLeftOver=true;
        }
}

 void LZW::compress( )
 {

         for(int i=0; i<ALPHA; i++)
         {
                 h[i]=i;
         }

         codesUsed = ALPHA;

         int c=in.get();//用于读取单个字符
         if(c!=EOF)//读取不成功则致EOF标志
         {
                 long pcode = c;
                 long theKey;
                 while( (c=in.get()) != EOF)
                 {
                         theKey = (pcode << BYTE_SIZE)+c;
                        auto thePair = h.find(theKey);//如过没有则返回尾后迭代器
                         if( thePair==h.cend() )
                         {
                                 com_output( pcode );
                                 if(codesUsed<MAX_CODES)
                                 {
                                         h.insert(  { theKey, codesUsed++ }  );
                                 }
                                 pcode=c;
                         }
                         else
                         {
                                 pcode=thePair->second;
                         }
                 }
                 com_output( pcode );
                 if(bitsLeftOver)
                 {
                         out.put( leftOver<<EXCESS );
                 }
         }
         out.close();
         in.close();
 }

 void LZW::decom_output(int pcode)
 {
         size = 0;

         while(pcode>=ALPHA)
         {
                 s[size++]=ht[pcode].second;
                 pcode = ht[pcode].first;
         }
         s[size]=pcode;
         for(int i=size; i>=0; --i)
         {
                 out.put( s[i] );
         }
 }

bool LZW::getCode(int &pcode)
{
        int c,d;
        if( (c=in.get() )==EOF )
                return false;
        if( bitsLeftOver )
        {
                pcode = (leftOver<<BYTE_SIZE)|c;
        }
        else
        {
                d = in.get();
                pcode = (c<<EXCESS)|(d>>EXCESS);
                leftOver = d&MASK2;
        }
        bitsLeftOver = !bitsLeftOver;
        return true;
}

void LZW::decompress()
{
        int codesUsed = ALPHA;
        int pcode, ccode;
        size=0;
        if( getCode(pcode) )
        {
                s[size] = pcode;
                out.put(s[0]);
                while( getCode(ccode) )
                {
                        if( ccode<codesUsed )
                        {
                                decom_output( ccode );
                                if( codesUsed<MAX_CODES )
                                {
                                        ht[codesUsed].first = pcode;
                                        ht[codesUsed++].second = s[size];
                                }
                        }
                        else
                        {
                                ht[codesUsed].first = pcode;
                                ht[codesUsed++].second = s[size];
                               decom_output( ccode);
                        }
                        pcode = ccode;
                }
        }
        out.close();
        in.close();
}

void LZW::decom_setFiles(int argc,  char *argv[ ])
{
        string inputFile,outputFile;//保存压缩文件
        if(argc>=2)
        {
                inputFile = string(argv[1]);
        }
        else
        {
                cout<<"Please enter name of file to decompress:"<<endl;
                cin>>inputFile;
        }
        in.open(inputFile,  ios::binary);//先定义文件流需要靠这个函数绑定文件
        if( !(in) )
        {
                cerr<<"Cannot open "<<inputFile<<endl;
                exit(1);
                //return;
        }
        outputFile=inputFile;
        outputFile.replace(outputFile.size()-7, 3, "bak");


        out.open(outputFile,  ios::binary);
}











