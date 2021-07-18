/*
	Create a registry key for Mecab library to be able to function normally.
	Without this, MeCab has to be manually installed by user or it will crash.
*/

#pragma once

#include "../../lib/WinReg/WinReg.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <atlsecurity.h>
#include <locale>
#include <codecvt>
#include <qdir.h>
#include <qstring.h>


class MeCabKey {

public:
	bool init();

private:
	std::string getUserSID();
	std::string MBFromW(LPCWSTR pwsz);
	std::wstring StringToWString(const std::string& s);
	bool createMeCabKey(std::string usid);
	bool verifyMeCabKey(std::string usid);

};