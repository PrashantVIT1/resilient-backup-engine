#include <iostream>
#include "../include/backup_manager.h"
#include "../include/restore_manager.h"

void showHelp()
{
    std::cout << "Resilient Backup Engine\n";
    std::cout << "-----------------------\n\n";

    std::cout << "Usage:\n";
    std::cout << "  backup_tool backup <source> <destination>\n";
    std::cout << "  backup_tool restore <backup> <destination>\n\n";

    std::cout << "Commands:\n";
    std::cout << "  backup     Create backup of a folder\n";
    std::cout << "  restore    Restore files from backup\n\n";

    std::cout << "Examples:\n";
    std::cout << "  backup_tool backup test_folder Backups\n";
    std::cout << "  backup_tool restore Backups restored_files\n";
}

int main(int argc, char* argv[])
{
    if (argc == 2 && std::string(argv[1]) == "-help")
    {
        showHelp();
        return 0;
    }

    if (argc < 4)
    {
        std::cout << "Invalid arguments.\n";
        std::cout << "Run '.\\backup_tool.exe -help' for usage.\n";
        return 1;
    }

    std::string command = argv[1];
    std::string source = argv[2];
    std::string destination = argv[3];

    if (command == "backup")
    {
        backupFolder(source, destination);
    }
    else if (command == "restore")
    {
        restoreFolder(source, destination);
    }
    else
    {
        std::cout << "Unknown command\n";
    }

    return 0;
}