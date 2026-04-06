#include <iostream>
#include <windows.h>
#include <string>
#include "todo.hpp"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    TodoManager manager;

    std::cout << "========================================\n";
    std::cout << "     C++ Todo List CLI  -  Version 1.0     \n";
    std::cout << "========================================\n";
    std::cout << "========= 歡迎使用任務清單系統 =========\n";

    std::string line;
    int choice = 0;

    while (true) {
        std::cout << "----------------------------------------\n";
        std::cout << "1. 新增任務\n";
        std::cout << "2. 列出所有任務\n";
        std::cout << "3. 標記任務完成\n";
        std::cout << "4. 刪除任務\n";
        std::cout << "5. ⚠️ 清除所有任務（重置）\n";
        std::cout << "6. 匯出為 JSON 檔案\n";
        std::cout << "0. 結束程式\n";
        std::cout << "----------------------------------------\n";
        std::cout << "請輸入選擇 (0-6): ";

        std::getline(std::cin, line);
        if (line.empty()) continue;

        try {
            choice = std::stoi(line);
        } catch (...) {
            std::cout << "❌ 輸入錯誤！請輸入數字 (0-6)。\n\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "感謝使用 C++ Todo List CLI！再見～\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string title, desc;
                std::cout << "輸入任務標題: ";
                std::getline(std::cin, title);

                std::cout << "輸入詳細描述 (可直接按 Enter 跳過): ";
                std::getline(std::cin, desc);

                if (title.empty()) {
                    std::cout << "標題不能為空，請重新輸入: ";
                    std::getline(std::cin, title);
                }

                manager.addTask(title, desc);
                break;
            }
            case 2:
                manager.listTasks();
                break;
            case 3: {
                std::cout << "輸入要完成的任務編號: ";
                std::getline(std::cin, line);
                try {
                    int id = std::stoi(line);
                    manager.markCompleted(id);
                } catch (...) {
                    std::cout << "❌ 輸入錯誤！請輸入數字。\n";
                }
                break;
            }
            case 4: {
                std::cout << "輸入要刪除的任務編號: ";
                std::getline(std::cin, line);
                try {
                    int id = std::stoi(line);
                    manager.removeTask(id);
                } catch (...) {
                    std::cout << "❌ 輸入錯誤！請輸入數字。\n";
                }
                break;
            }
            case 5: {
                std::cout << "⚠️ 警告：這將清除所有任務且無法恢復！\n";
                std::cout << "確定要繼續嗎？(y/N): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (!confirm.empty() && (confirm[0] == 'y' || confirm[0] == 'Y')) {
                    manager.clearAllTasks();
                } else {
                    std::cout << "已取消清除操作。\n";
                }
                break;
            }
            case 6:
                manager.exportToJson();
                break;
            default:
                std::cout << "❌ 無效的選擇，請輸入 0~6 之間的數字。\n";
        }
        std::cout << "\n";
    }

    return 0;
}