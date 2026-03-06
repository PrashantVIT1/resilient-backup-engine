# resilient-backup-engine
A fault-tolerant C++ backup and restore tool that performs reliable file backups with integrity validation, error handling, and a modular system design.

Commands:
To get commands
```bash
.\backup_tool.exe -help
```
To create backup
```bash
g++ src\*.cpp -I include -o backup_tool.exe
```
To create the backup
```bash
.\backup_tool.exe backup test_folder Backups
```
To restore the file in back
```bash
.\backup_tool.exe restore Backups Restored
```
