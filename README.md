# resilient-backup-engine
A fault-tolerant C++ backup and restore tool that performs reliable file backups with integrity validation, error handling, and a modular system design.

Commands:
To create backup
```bash
g++ src\main.cpp -o backup_tool.exe
```
To create the backup
```bash
.\backup_tool.exe backup test_folder Backups
```
To restore the file in back
```bash
.\backup_tool.exe restore Backups Restored
```

