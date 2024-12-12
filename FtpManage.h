#pragma once
#include<iostream>
#include<curl/curl.h>
#include<string>
#include<vector>
using namespace std;

class FtpManage {
public:
    FtpManage(const string user, const string password, const string id);

    ~FtpManage();

    /**
    * @Upload: 向Ftp服务器上传文件
    * @localFilePath:所上传的文件（精确到文件名），如"D:/ggbond/123.jpg"
    * @remoteDirectory:上传至Ftp的目录，如"/shjr/"
    * @remark:将123.jpg上传到Ftp服务器的"/shjr/"目录下,
    */
    bool Upload(const char *localFilePath, const char *remoteDirectory);

    /**
    * @Download:从Ftp服务器下载特定文件
    * @remoteFilePath:所下载的文件（精确到文件名）如"/shjr/333.jpg"
    * @localDirectory:保存至本地目录,如"D:/ggbond/"
    * @remark:将FTp服务器/shjr目录下的333.jpg下载到本地D:/ggbond目录
    */
    bool DownloadFile(const char *remoteFilePath, const char *localDirectory);

    /**
    * @DownloadAllFiles:从Ftp某个文件夹里面下载所有文件
    * @remoteFilePath:所下载的文件夹名称，如"/shjr/"
    * @localDirectory:保存至本地目录,如"D:/ggbond/"
    * @remark:将FTp服务器/shjr/目录里面下载所有文件到本地D:/ggbond/目录
    */
    bool DownloadAllFiles(const char *remoteFilePath, const char *localDirectory);

    /**
    * @Createdir：创建文件夹
    * @directoryname：文件夹名称，可包含上级目录名，要以“/”结尾以表示目录
    * 比如："/ggbond/"
    */
    bool Createdir(const char *directoryname);

    /**
    * @GetFilesName：提供获取FTP文件夹内所有文件名的接口
    * @filepath：文件夹名称，可包含上级目录名，要以“/”结尾以表示目录
    * 比如："/ggbond/"
    */
    const std::vector<std::string> &GetFilesName(const string filepath);

private:
    /**
    * @SetURL：初始化URL
    */
    void SetURL();

    /**
    * @UrlEncode：把含有特殊符号的文件名进行URL编码
    * @value：文件名
    * @"kunkunboy##  123"这种形式是无法传入curl的，需要转换一下
    */
    std::string UrlEncode(const std::string &value);

    /**
    * @GEtFileNameFromPath：从路径中提取文件名并返回
    * @filePath：文件完整路径
    * @"D:/ggbond/123.jpg"->123.jpg
    */
    std::string GetFileNameFromPath(const std::string &filePath);

    /**
    * @GetfilenameFromftp:获得FTP服务器上某个文件夹内所有文件名,如果文件夹内既有文件又有文件夹，则只会显示文件
    * @directoryname:文件夹名称，可包含上级目录名，要以“/”结尾以表示目录
    */
    bool GetfilenameFromftp(const string directoryname);

private:
    std::string Ftp_ip; //Ftp服务器地址
    std::string User, Password; //登录用户名及密码
    std::string _URL;
    std::vector<std::string> fNs; //用于记录全部文件名
    std::vector<std::string> dNs; //用于记录全部文件夹名
    CURL *curl;
};
