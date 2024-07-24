#include "FtpManage.h"
#include <vector>
#include <sstream>
#include<memory>

using namespace std;

FtpManage::FtpManage(const string user, const string password, const string id)
	:Ftp_ip(id), User(user), Password(password)
{
	CURLcode res = curl_global_init(CURL_GLOBAL_ALL);	// 初始化全局环境只需要初始化一次
	if (res != CURLE_OK)
	{
		std::cout << "curl_global_init() falied" << curl_easy_strerror(res) << std::endl;
		return;
	}
}

FtpManage::~FtpManage()
{
	if (curl)
	{
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

//接收消息回调函数
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
	size_t totalSize = size * nmemb;
	output->append(static_cast<char*>(contents), totalSize);
	return totalSize;
}

// 初始化curl
void FtpManage::SetURL()
{
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);		// 设置长连接
	curl_easy_setopt(curl, CURLOPT_USERPWD, (User + ':' + Password).c_str());	//设置用户名和密码
}

// 把带有路径的文件转换为文件名 D:/ggbond/123.jpg->123.jpg
std::string FtpManage::GetFileNameFromPath(const std::string& filePath)
{
	if (filePath == "") return filePath;

	//去除路径最后的空格
	string retPath;
	size_t lastBlank = filePath.find_last_not_of(' ');
	if (lastBlank != std::string::npos)
	{
		retPath = filePath.substr(0, lastBlank+1);
	}
	else
	{
		return "";
	}
	size_t lastSlashPos = retPath.find_last_of("/\\");
	if (lastSlashPos != std::string::npos)
	{
		return retPath.substr(lastSlashPos + 1);
	}
	else
	{
		// 如果没有找到斜杠或反斜杠，整个路径就是文件名
		return retPath;
	}
}

// 对文件名进行URL编码，否则文件名中有空格，特殊符合(#^...)会出现URL错误
std::string FtpManage::UrlEncode(const std::string &value) 
{
	CURL* curl = curl_easy_init();
	if (!curl) return "";
	char* output = curl_easy_escape(curl, value.c_str(), value.length());
	if (output) {
		std::string encoded(output);
		curl_free(output);
		curl_easy_cleanup(curl);
		return encoded;
	}
	curl_easy_cleanup(curl);
	return "";
}

// 上传文件
bool FtpManage::Upload(const char* localFilePath, const char* remoteDirectory)
{
	SetURL();
	_URL = Ftp_ip + remoteDirectory+ GetFileNameFromPath(localFilePath);
	curl_easy_setopt(curl, CURLOPT_URL, _URL.c_str());		// 设置访问的FTP地址
	if (curl)
	{
		FILE* fp = fopen(localFilePath, "rb");
		curl_off_t fsize = 0;
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			fsize = ftell(fp);			// 获取文件大小
			fseek(fp, 0, SEEK_SET);

			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);				// 指定为上传文件模式
			curl_easy_setopt(curl, CURLOPT_READDATA, fp);			// 指定上传的文件是哪个
			curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, fsize);// 指定上传的文件大小

			CURLcode res = curl_easy_perform(curl);					// 开始上传
			if (res != CURLE_OK)
			{
				std::cout << "localFilePath: " << localFilePath << " upload failed!" << curl_easy_strerror(res) << std::endl;
				curl_easy_cleanup(curl);
				fclose(fp);
				return false;
			}
			else
			{
				std::cout << "localFilePath: " << localFilePath << " upload successfully!" << std::endl;
			}
			fclose(fp);
		}
		else
		{
			std::cout << "file: " << localFilePath << " open failed!" << std::endl;
			curl_easy_cleanup(curl);
			return false;
		}
	}
	curl_easy_cleanup(curl);
	return true;
}

// 下载单一文件,把remoteFilePath的文件下载到localDirectory里面
bool FtpManage::DownloadFile(const char* remoteFilePath, const char* localDirectory)
{
	SetURL();
	_URL = Ftp_ip + UrlEncode(remoteFilePath);
	curl_easy_setopt(curl, CURLOPT_URL, _URL.c_str());		// 设置请求的URL
	if (curl)
	{
		FILE* fp = fopen((localDirectory + GetFileNameFromPath(remoteFilePath)).c_str(), "wb");
		if (fp)
		{
			// 设置文件写入地址
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			// 执行任务
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cout << "DownLoad file:" << remoteFilePath << " failed! " << curl_easy_strerror(res) << std::endl;
				fclose(fp);
				curl_easy_cleanup(curl);
				return false;
			}
			else
			{
				std::cout << "DownLoad file:" << remoteFilePath << " successfully!" << std::endl;
				fclose(fp);
			}
		}
		else
		{
			std::cout << "file open failed!" << std::endl;
			curl_easy_cleanup(curl);		// 清除curl
			return false;
		}
	}
	curl_easy_cleanup(curl);
	return true;
}
// 下载全部文件
bool FtpManage::DownloadAllFiles(const char* remoteFilePath, const char* localDirectory)
{
	if (GetfilenameFromftp(remoteFilePath))
	{
		for (const auto& fns : fNs)
		{
			std::string filename = remoteFilePath + fns;
			bool res = DownloadFile(filename.c_str(), localDirectory);
			if (res) continue;
			else
			{
				return false;
			}
		}
	}
	return true;
}
//在Ftp服务器上创建文件夹
bool FtpManage::Createdir(const char* directoryname)
{
	if (directoryname == nullptr)
	{
		std::cout << "directoryname is NULL!" << std::endl;
		return false;
	}
	SetURL();
	_URL = Ftp_ip + UrlEncode(directoryname);
	curl_easy_setopt(curl, CURLOPT_URL, _URL.c_str());				// 指定url
	curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);	//如果目录不存在则创建一个
	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		std::cout << "Directory:" << directoryname << "create failed!" << curl_easy_strerror(res) << std::endl;
		curl_easy_cleanup(curl);		// 清理curl
		return false;
	}
	else
	{
		std::cout << "Create directory:" << directoryname << " successfully!" << std::endl;
	}
	curl_easy_cleanup(curl);
	return true;
}


// 获取ftp某个文件夹内文件名
bool FtpManage::GetfilenameFromftp(const std::string filePath)
{
	SetURL();
	std::string path = Ftp_ip + UrlEncode(filePath);
	std::string fileName;	// 文件名列表保存位置
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());	// 设置访问URL
		curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L);	// 设置只返回文件
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fileName);	// 设置只获取文件名列表
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);	// 设置get的回调函数
		if (curl_easy_perform(curl) == CURLE_OK)				//执行任务
		{
			fNs.clear();
			size_t startPos = 0, endPos = 0;
			while ((endPos = fileName.find('\n', startPos)) != std::string::npos )
			{
				std::string name = fileName.substr(startPos, endPos - startPos-1);
				fNs.emplace_back(name);
				startPos = endPos + 1;
			}
		}
	}
	else
	{
		return false;
	}
	curl_easy_cleanup(curl);
	return true;
}

// 获取FTP文件夹内所有文件名的接口函数
const std::vector<std::string>& FtpManage::GetFilesName(const string filepath)
{
	if (GetfilenameFromftp(filepath))
	{
		return fNs;
	}
	else
	{
		return std::vector<std::string>();
	}
}