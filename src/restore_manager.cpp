#include "../include/restore_manager.h"
#include <iostream>
#include <windows.h>
#include <string>

void restoreRecursive(const std::string& backupSource,
                      const std::string& restoreDestination)
{
    // Create destination folder
    if (!CreateDirectoryA(restoreDestination.c_str(), NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS)
    {
        std::cout << "Failed to create directory: "
                  << restoreDestination << "\n";
        return;
    }

    WIN32_FIND_DATAA findData;
    std::string searchPath = backupSource + "\\*";

    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "Cannot access: " << backupSource << "\n";
        return;
    }

    do
    {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0)
        {
            continue;
        }

        std::string sourcePath = backupSource + "\\" + findData.cFileName;
        std::string destPath = restoreDestination + "\\" + findData.cFileName;

        // If directory → recursive restore
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            std::cout << "Restoring folder: " << sourcePath << "\n";
            restoreRecursive(sourcePath, destPath);
        }
        else
        {
            if (CopyFileA(sourcePath.c_str(), destPath.c_str(), TRUE))
            {
                std::cout << "Restored: " << sourcePath << "\n";
            }
            else
            {
                std::cout << "Failed: " << sourcePath << "\n";
            }
        }

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

void restoreFolder(const std::string& backupSource,
                   const std::string& restoreDestination)
{
    std::cout << "Starting restore...\n";
    std::cout << "Backup Source: " << backupSource << "\n";
    std::cout << "Restore Destination: " << restoreDestination << "\n";

    try
    {
        restoreRecursive(backupSource, restoreDestination);
        std::cout << "Restore completed\n";
    }
    catch (...)
    {
        std::cout << "Restore error occurred\n";
    }
}