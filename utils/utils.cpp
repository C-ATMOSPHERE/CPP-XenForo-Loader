#include "utils.hpp"

string CUtils::GetAppData()
{
	static TCHAR szPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath);

	return string(szPath);
}

bool CUtils::dirExists(const string& dirName)
{
    DWORD ftyp = GetFileAttributesA(dirName.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  // something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this directory exists

    return false;    // this directory doesn't exists
}

void CUtils::StoreLogin(string username, string password, string hwid, string file) 
{
    ofstream output(file.c_str());
    output.close();

    // storing username and password within appdata for possible authentication checks withing the cheat, i will maybe go more indepth with this.
    configmanager->PushValue("logindata", "username", username, file.c_str());
    configmanager->PushValue("logindata", "password", password, file.c_str());
    configmanager->PushValue("logindata", "hwid", hwid, file.c_str());
}

DWORD CUtils::GetHWID() // using the system volume informations as hwid for testing purposes
{
    DWORD VolumeSerialNumber;

    BOOL GetVolumeInformationFlag = GetVolumeInformationA(
        "c:\\",
        0,
        0,
        &VolumeSerialNumber,
        0,
        0,
        0,
        0
    );

    if (GetVolumeInformationFlag)
        return VolumeSerialNumber;

    return 0;
}

CUtils* utils;