#include "todo.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs = std::filesystem;

// ==================== JSON 匯出功能 ====================

void TodoManager::exportToJson() const {
    json j;
    j["next_id"] = next_id;
    j["tasks"] = json::array();

    for (const auto& task : tasks) {
        json t;
        t["id"] = task.id;
        t["title"] = task.title;
        t["description"] = task.description;
        t["completed"] = task.completed;
        t["created_at"] = task.created_at;
        j["tasks"].push_back(t);
    }

    std::ofstream file("data/tasks.json", std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        std::cout << "✅ 已成功匯出為 data/tasks.json！（格式化 JSON）\n\n";
    } else {
        std::cout << "❌ 無法建立 tasks.json 檔案。\n\n";
    }
}

// Task 建構子
Task::Task(const std::string& t, const std::string& d) 
    : id(0), title(t), description(d), completed(false), created_at(std::time(nullptr)) {}

// TodoManager 建構子
TodoManager::TodoManager() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    loadFromFile();
}

// 新增任務
void TodoManager::addTask(const std::string& title, const std::string& description) {
    if (title.empty()) {
        std::cout << "❌ 任務標題不能為空！\n\n";
        return;
    }

    Task newTask(title, description);
    newTask.id = next_id++;
    tasks.push_back(newTask);

    std::cout << "✅ 任務新增成功！\n";
    std::cout << "   編號 #" << newTask.id << "： " << title << "\n\n";

    saveToFile();
}

// 列出所有任務
void TodoManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "目前沒有任何任務。\n\n";
        return;
    }

    std::cout << "=== 目前任務清單 (" << tasks.size() << " 個) ===\n";
    for (const auto& task : tasks) {
        std::cout << "[" << task.id << "] ";
        std::cout << (task.completed ? "[✓]" : "[ ]") << " ";
        std::cout << task.title;
        if (!task.description.empty()) {
            std::cout << "  (" << task.description << ")";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// 標記完成
void TodoManager::markCompleted(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            std::cout << "✅ 任務 #" << id << " 已標記為完成！\n\n";
            saveToFile();
            return;
        }
    }
    std::cout << "❌ 找不到編號 #" << id << " 的任務。\n\n";
}

// 刪除任務
void TodoManager::removeTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            std::cout << "🗑️ 任務 #" << id << " 已刪除。\n\n";
            tasks.erase(it);
            saveToFile();
            return;
        }
    }
    std::cout << "❌ 找不到編號 #" << id << " 的任務。\n\n";
}

// ==================== 強制 UTF-8 文字檔儲存 ====================

void TodoManager::saveToFile() const {
    std::ofstream file(data_file, std::ios::out | std::ios::binary);
    if (!file.is_open()) return;

    file << next_id << "\n";
    file << tasks.size() << "\n";

    for (const auto& task : tasks) {
        file << task.id << "\n";
        file << task.title << "\n";
        file << task.description << "\n";
        file << (task.completed ? "1" : "0") << "\n";
        file << task.created_at << "\n";
    }
    file.close();
}

void TodoManager::loadFromFile() {
    std::ifstream file(data_file, std::ios::in | std::ios::binary);
    if (!file.is_open()) return;

    tasks.clear();

    std::string line;
    int task_count = 0;

    if (std::getline(file, line)) {
        try { next_id = std::stoi(line); } catch (...) { next_id = 1; }
    }

    if (std::getline(file, line)) {
        try { task_count = std::stoi(line); } catch (...) { task_count = 0; }
    }

    for (int i = 0; i < task_count; ++i) {
        Task task("", "");

        if (std::getline(file, line)) {
            try { task.id = std::stoi(line); } catch (...) { task.id = 0; }
        }

        std::getline(file, task.title);
        std::getline(file, task.description);

        if (std::getline(file, line)) {
            task.completed = (line == "1");
        }

        if (std::getline(file, line)) {
            try { task.created_at = std::stoll(line); } catch (...) { task.created_at = std::time(nullptr); }
        }

        if (!task.title.empty()) {
            tasks.push_back(task);
        }
    }
}

// 清除所有任務
void TodoManager::clearAllTasks() {
    tasks.clear();
    next_id = 1;
    saveToFile();
    std::cout << "🗑️ 所有任務已清除，資料已完全重置。\n\n";
}

