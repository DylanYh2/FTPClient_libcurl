#pragma once
#include<iostream>
#include<curl/curl.h>
#include<string>
#include<vector>
using namespace std;

class FtpManage
{
public:
	FtpManage();
	FtpManage(const string user, const string password, const string id);
	~FtpManage();
	
	/*
	*@Upload: ��Ftp�������ϴ��ļ�
	* @localFilePath:���ϴ����ļ�����ȷ���ļ���������"D:/ggbond/123.jpg"
	* @remoteDirectory:�ϴ���Ftp��Ŀ¼����"/shjr/"
	* @remark:��123.jpg�ϴ���Ftp��������"/shjr/"Ŀ¼��,
	*/
	bool Upload(const char* localFilePath, const char* remoteDirectory);

	/*
	* @Download:��Ftp�����������ض��ļ�
	* @remoteFilePath:�����ص��ļ�����ȷ���ļ�������"/shjr/333.jpg"
	* @localDirectory:����������Ŀ¼,��"D:/ggbond/"
	* @remark:��FTp������/shjrĿ¼�µ�333.jpg���ص�����D:/ggbondĿ¼
	*/
	bool DownloadFile(const char* remoteFilePath, const char* localDirectory);

	/*
	* @DownloadAllFiles:��Ftpĳ���ļ����������������ļ�
	* @remoteFilePath:�����ص��ļ������ƣ���"/shjr/"
	* @localDirectory:����������Ŀ¼,��"D:/ggbond/"
	* @remark:��FTp������/shjr/Ŀ¼�������������ļ�������D:/ggbond/Ŀ¼
	*/
	bool DownloadAllFiles(const char* remoteFilePath, const char* localDirectory);
	
	/*
	* @Createdir�������ļ���
	* @directoryname���ļ������ƣ��ɰ����ϼ�Ŀ¼����Ҫ�ԡ�/����β�Ա�ʾĿ¼
	* ���磺"/ggbond/"
	*/
	bool Createdir(const char* directoryname);

	/*
	* @GetFilesName���ṩ��ȡFTP�ļ����������ļ����Ľӿ�
	* @filepath���ļ������ƣ��ɰ����ϼ�Ŀ¼����Ҫ�ԡ�/����β�Ա�ʾĿ¼
	* ���磺"/ggbond/"
	*/
	const std::vector<std::string>& GetFilesName(const string filepath);
	
private:
	/*
	* @SetURL����ʼ��URL
	*/
	void SetURL();

	/*
	* @UrlEncode���Ѻ���������ŵ��ļ�������URL����
	* @value���ļ���
	* @"kunkunboy##  123"������ʽ���޷�����curl�ģ���Ҫת��һ��
	*/
	std::string UrlEncode(const std::string& value);

	/*
	* @GEtFileNameFromPath����·������ȡ�ļ���������
	* @filePath���ļ�����·��
	* @"D:/ggbond/123.jpg"->123.jpg
	*/
	std::string GetFileNameFromPath(const std::string& filePath);

	/*
	* @GetfilenameFromftp:���FTP��������ĳ���ļ����������ļ���,����ļ����ڼ����ļ������ļ��У���ֻ����ʾ�ļ�
	* @directoryname:�ļ������ƣ��ɰ����ϼ�Ŀ¼����Ҫ�ԡ�/����β�Ա�ʾĿ¼
	*/
	bool GetfilenameFromftp(const string directoryname);
private:
	std::string Ftp_ip;									//Ftp��������ַ
	std::string User, Password;							//��¼�û���������
	std::string _URL;
	std::vector<std::string> fNs;						//���ڼ�¼ȫ���ļ���
	CURL* curl;
};

