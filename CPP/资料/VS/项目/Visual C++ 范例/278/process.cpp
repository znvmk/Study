//多进程测试：win32控制台+打开记事
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

//LPTSTR与char*之间转换
char* wide_Char_To_Multi_Byte(wchar_t* pWCStrKey);
wchar_t* multi_Byte_To_Wide_Char(string pKey);

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(STARTUPINFO));
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;

    wchar_t szFilePath[MAX_PATH];
    GetModuleFileName(NULL, szFilePath, MAX_PATH - 1);
    string strFilePath = wide_Char_To_Multi_Byte(szFilePath);
    int nPos = strFilePath.rfind('\\');
    if (nPos == -1)return -1;
    strFilePath = strFilePath.substr(0, nPos + 1);
    strFilePath += "text.txt";

    char szCmd[MAX_PATH + 201];
    _snprintf(szCmd, MAX_PATH + 200, "NotePad.exe %s", strFilePath.c_str());

    cout << "创建进程命令：" << szCmd << endl;

    string szc(szCmd);
    wchar_t* wcSzCmd = multi_Byte_To_Wide_Char(szc);

    BOOL bSucceed = CreateProcess(NULL, wcSzCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (bSucceed) cout << "创建进程成功" << endl;
    else cout << "创建进程失败" << endl;
    system("pause");
    return 0;
}


//不要忘记使用完char*后delete[]释放内存
char* wide_Char_To_Multi_Byte(wchar_t* pWCStrKey)
{
    //第一次调用确认转换后单字节字符串的长度，用于开辟空间
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize+1];
    //第二次调用将双字节字符串转换成单字节字符串
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;
 
    //如果想要转换成string，直接赋值即可
    //string pKey = pCStrKey;
}
//不要忘记在使用完wchar_t*后delete[]释放内存
wchar_t* multi_Byte_To_Wide_Char(string pKey)
{
    //string 转 char*
    const char* pCStrKey = pKey.c_str();
    //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
    wchar_t* pWCStrKey = new wchar_t[pSize];
    //第二次调用将单字节字符串转换成双字节字符串
    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
    return pWCStrKey;
}