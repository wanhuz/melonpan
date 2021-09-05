#include "../../lib/WinReg/WinReg.hpp";
#include "mecabKey.h";
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <atlsecurity.h>
#include <locale>
#include <codecvt>
#include <qdir.h>
#include <qstring.h>

using std::optional;
using std::pair;
using std::vector;
using std::wcout;
using std::wstring;

using winreg::RegKey;
using winreg::RegException;
using winreg::RegResult;


bool MeCabKey::init()
{
    std::string usid = getUserSID();

    if (verifyMeCabKey(usid)) 
        return true;
    else if (createMeCabKey(usid)){
        return true;
    }

    return false;
}

std::string MeCabKey::getUserSID() {
    std::string usid = "";
    ATL::CAccessToken accessToken;
    ATL::CSid currentUserSid;

    if (accessToken.GetProcessToken(TOKEN_READ | TOKEN_QUERY) && accessToken.GetUser(&currentUserSid))
        usid = MBFromW(currentUserSid.Sid());

    return usid;
}

bool MeCabKey::verifyMeCabKey(std::string usid) {
    const wstring keyDir = L"\\SOFTWARE\\MeCab";
    const wstring uSid = StringToWString(usid);
    const wstring mecab = L"mecabrc";

    wstring keyPath;
    keyPath += uSid;
    keyPath += keyDir;

    RegKey key{ HKEY_USERS, keyPath };

    if (auto result = key.TryGetStringValue(mecab)) { //Validate if key exist

        QString pathToMecabrc = QDir::currentPath();
        pathToMecabrc.replace("/", "\\");
        pathToMecabrc.append("\\res\\mecab\\etc\\mecabrc");
        pathToMecabrc = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\mecab\\etc\\mecabrc"; //debug mode
        std::wstring pathToMecabrcstr = StringToWString(pathToMecabrc.toStdString());

        if (key.GetStringValue(mecab) == pathToMecabrc) { //Validate key correctness
            key.Close();
            return true;
        }
    }

    key.Close();
    return false;
}

bool MeCabKey::createMeCabKey(std::string usid) {
    const wstring keyDir = L"\\SOFTWARE\\MeCab";
    const wstring uSid = StringToWString(usid);
    const wstring mecab = L"mecabrc";
    wstring keyPath;

    keyPath += uSid;
    keyPath += keyDir;

    RegKey key{ HKEY_USERS, keyPath };

    QString pathToMecabrc = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\mecab\\etc\\mecabrc"; //debug mode
    //QString pathToMecabrc = QDir::currentPath();
    //pathToMecabrc.replace("/", "\\");
    //pathToMecabrc.append("\\res\\mecab\\etc\\mecabrc");
    std::wstring pathToMecabrcstr = StringToWString(pathToMecabrc.toStdString());
    key.SetStringValue(mecab, pathToMecabrcstr);
    
    if (auto result = key.TryGetStringValue(mecab)) { //Verify key has been created
        key.Close();
        return true;
    }

    key.Close();
    return false;
}

//Convert string from LPCWSTR to Std::String
std::string MeCabKey::MBFromW(LPCWSTR pwsz) {
    int cch = WideCharToMultiByte(1, 0, pwsz, -1, 0, 0, NULL, NULL);
    char* psz = new char[cch];

    WideCharToMultiByte(1, 0, pwsz, -1, psz, cch, NULL, NULL);

    std::string st(psz);
    delete[] psz;

    return st;
}

//Convert String to WString
wstring MeCabKey::StringToWString(const std::string& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    std::wstring ws = wsTmp;
    return ws;
}