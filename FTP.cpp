// FTP.cpp : ����ʹ�÷�ʽ

#include<curl/curl.h>
#include <iostream>
#include"FtpManage.h"
int main()
{
    // ����ʽ��ʼ��Ftp����һ��"1"���û������ڶ���"1"���û��������룬"ftp://192.168.1.1/"��FTP��ip��ַ������ǵü�'/'
    FtpManage Aftp = FtpManage("1", "1", "ftp://192.168.1.1/");                
    
    // ����ĳ���ļ�����Ҫ����·��
    std::string localfile = "E:/Dylan/FTP/xxx.png";     

    // Ftp��������ĳ���ļ�����Ҫ����·��
    std::string remotefile = "/show.png";     

    // ��Ftp�����������浽���ص�Ŀ¼·��,���ԡ�/����β
    std::string localpath = "E:/Dylan/FTP/image/";                             

    // ��FTP�ϴ����ļ��У���Ҫָ��·��+�ļ������ƣ������'/'��β
    std::string newdiretoty = "/ne111##new1/";              

    // ��localfile��Ӧ���ļ��ϴ���192.168.1.1��ĳ��·��,remoteDirectory�����ϴ�����FTP·��
    std::string remoteDirectory = "/";

    // listpath ��FTP�ĸ��ļ��������ļ�
    std::string listpath = "/";

    /*�ڶ����֣��������÷�ʽ */
    // �ϴ��ļ�
    Aftp.Upload(localfile.c_str(), remoteDirectory.c_str());
    
    // ��Ftp�ϵ�remotefile��Ӧ���ļ����ص�����localpath��Ӧ��Ŀ¼��  
    Aftp.DownloadFile(remotefile.c_str(), localpath.c_str());   

    // ��Ftp��listpath�ļ������������ļ����ص�����localpathĿ¼��
    Aftp.DownloadAllFiles(listpath.c_str(), localpath.c_str());

    //��Ftp�ϴ���newdiretoty��Ӧ��Ŀ¼
    Aftp.Createdir(newdiretoty.c_str());      

    // �鿴ftpĳ��Ŀ¼������Щ�ļ�
    for (const auto& n : Aftp.GetFilesName(listpath))
    {
        std::cout << n << std::endl;
    }
    system("pause");                                                                
    return 0;
}  

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
