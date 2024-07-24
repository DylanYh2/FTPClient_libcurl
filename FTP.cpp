// FTP.cpp : 代码使用方式

#include<curl/curl.h>
#include <iostream>
#include"FtpManage.h"
int main()
{
    // 按格式初始化Ftp，第一个"1"是用户名，第二个"1"是用户名的密码，"ftp://192.168.1.1/"是FTP的ip地址，后面记得加'/'
    FtpManage Aftp = FtpManage("1", "1", "ftp://192.168.1.1/");                
    
    // 本地某个文件，需要绝对路径
    std::string localfile = "E:/Dylan/FTP/xxx.png";     

    // Ftp服务器上某个文件，需要绝对路径
    std::string remotefile = "/show.png";     

    // 从Ftp上下载来保存到本地的目录路径,需以“/”结尾
    std::string localpath = "E:/Dylan/FTP/image/";                             

    // 在FTP上创建文件夹，需要指名路径+文件夹名称，最后以'/'结尾
    std::string newdiretoty = "/ne111##new1/";              

    // 将localfile对应的文件上传到192.168.1.1的某个路径,remoteDirectory代表上传到的FTP路径
    std::string remoteDirectory = "/";

    // listpath 从FTP哪个文件夹下载文件
    std::string listpath = "/";

    /*第二部分：函数调用方式 */
    // 上传文件
    Aftp.Upload(localfile.c_str(), remoteDirectory.c_str());
    
    // 将Ftp上的remotefile对应的文件下载到本地localpath对应的目录下  
    Aftp.DownloadFile(remotefile.c_str(), localpath.c_str());   

    // 将Ftp上listpath文件夹里面所有文件下载到本地localpath目录下
    Aftp.DownloadAllFiles(listpath.c_str(), localpath.c_str());

    //在Ftp上创建newdiretoty对应的目录
    Aftp.Createdir(newdiretoty.c_str());      

    // 查看ftp某个目录下有哪些文件
    for (const auto& n : Aftp.GetFilesName(listpath))
    {
        std::cout << n << std::endl;
    }
    system("pause");                                                                
    return 0;
}  

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
