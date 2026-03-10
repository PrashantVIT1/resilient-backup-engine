#include "../include/backup_manager.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <sys/stat.h>

bool isFileModified(const std::string& sourceFile,
                    const std::string& destFile)
{
    struct stat sourceStat;
    struct stat destStat;

    if (stat(destFile.c_str(), &destStat) != 0)
    {
        return true; // File doesn't exist in backup
    }

    stat(sourceFile.c_str(), &sourceStat);

    return sourceStat.st_mtime > destStat.st_mtime;
}

void backupRecursive(const std::string& source,
                     const std::string& destination)
{
    // Create destination folder
    if (!CreateDirectoryA(destination.c_str(), NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS)
    {
        std::cout << "Failed to create directory: " << destination << "\n";
        return;
    }

    WIN32_FIND_DATAA findData;
    std::string searchPath = source + "\\*";

    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "Cannot access: " << source << "\n";
        return;
    }

    do
    {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0)
        {
            continue;
        }

        std::string sourcePath = source + "\\" + findData.cFileName;
        std::string destPath = destination + "\\" + findData.cFileName;

        // If directory → recursive call
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            std::cout << "Entering folder: " << sourcePath << "\n";
            backupRecursive(sourcePath, destPath);
        }
        else
        {
            if (isFileModified(sourcePath, destPath))
            {
                if (CopyFileA(sourcePath.c_str(), destPath.c_str(), FALSE))
                {
                    std::cout << "Updated: " << sourcePath << "\n";
                }
                else
                {
                    std::cout << "Failed: " << sourcePath << "\n";
                }
            }
            else
            {
                std::cout << "Skipped (unchanged): " << sourcePath << "\n";
            }
        }

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

void backupFolder(const std::string& source,
                  const std::string& destination)
{
    std::cout << "Starting backup...\n";
    std::cout << "Source: " << source << "\n";
    std::cout << "Destination: " << destination << "\n";

    try
    {
        backupRecursive(source, destination);
        std::cout << "Backup completed\n";
    }
    catch (...)
    {
        std::cout << "Backup error occurred\n";
    }
}