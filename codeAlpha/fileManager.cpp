#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
# include<limits.h>

std::string getCurrentPath() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX) == nullptr) {
        std::cerr << "Error getting current directory: " << strerror(errno) << std::endl;
        return "";
    }
    return std::string(buffer);
}

void listDirectory(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        std::cerr << "Error opening directory: " << strerror(errno) << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::cout << entry->d_name << std::endl;
    }

    closedir(dir);
}

void createDirectory(const std::string& path, const std::string& dirName) {
    if (mkdir((path + "/" + dirName).c_str()) != 0) {
        std::cerr << "Error creating directory: " << strerror(errno) << std::endl;
    }
}

void createFile(const std::string& path, const std::string& fileName) {
    std::ofstream newFile(path + "/" + fileName);
    if (!newFile.is_open()) {
        std::cerr << "Error creating file: " << strerror(errno) << std::endl;
    } else {
        std::cout << "File created successfully: " << fileName << std::endl;
    }
}

int main() {
    std::string currentPath = getCurrentPath();

    while (true) {
        std::cout << "Current Directory: " << currentPath << std::endl;
        std::cout << "1. List files and directories\n"
                  << "2. Create directory\n"
                  << "3. Create file\n"
                  << "4. Change directory\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                listDirectory(currentPath);
                break;
            case 2: {
                std::string newDirName;
                std::cout << "Enter new directory name: ";
                std::cin >> newDirName;
                createDirectory(currentPath, newDirName);
                break;
            }
            case 3: {
                std::string newFileName;
                std::cout << "Enter new file name: ";
                std::cin >> newFileName;
                createFile(currentPath, newFileName);
                break;
            }
            case 4: {
                std::string newDir;
                std::cout << "Enter the new directory path: ";
                std::cin >> newDir;
                if (chdir(newDir.c_str()) != 0) {
                    std::cerr << "Error changing directory: " << strerror(errno) << std::endl;
                } else {
                    currentPath = getCurrentPath();
                }
                break;
            }
            case 5:
                std::cout << "Exiting file manager. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}
