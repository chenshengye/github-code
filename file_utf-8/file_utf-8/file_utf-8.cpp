#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

#ifdef _WIN32
#include <Windows.h>
#endif

string UTF8ToGB(const char* str)
{
	string result;
	WCHAR *strSrc;
	LPSTR szRes;

	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

string ReadTextFile(string strFileName)
{

	FILE * fp = NULL;
	fopen_s(&fp, strFileName.c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	string result;

	if (fp != NULL)
	{
		char* szBuf = new char[size + 1];
		memset(szBuf, 0, sizeof(char) * (size + 1));
		fread(szBuf, sizeof(char), size, fp);
		result.append(szBuf);
		delete szBuf;
	}
	fclose(fp);
	//if(is utf-8 file)
	result = UTF8ToGB(result.c_str());
	return result;
}
void WriteTextFile(string strFileName,const char* data,int data_len)
{
	FILE * fp = NULL;
	fopen_s(&fp, strFileName.c_str(), "wb");
	if (fp != NULL)
	{
		fwrite(data, sizeof(char), data_len, fp);
	}
	fclose(fp);
}


int main()
{
	string json = ReadTextFile("out-utf-8.txt");

	cout << json << endl;

	WriteTextFile("in.txt",json.c_str(),json.length());

	return 0;
}



