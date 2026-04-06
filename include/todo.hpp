#pragma once
#include <string>
#include <vector>
#include <ctime>

struct Task {
    int id;
    std::string title;
    std::string description;
    bool completed;
    std::time_t created_at;

    Task(const std::string& t, const std::string& d = "");
};

class TodoManager {
private:
    std::vector<Task> tasks;
    int next_id = 1;
    std::string data_file = "data/tasks.txt";

public:
    TodoManager();
    void addTask(const std::string& title, const std::string& description = "");
    void listTasks() const;
    void markCompleted(int id);
    void removeTask(int id);
    void saveToFile() const;
    void loadFromFile();
    void clearAllTasks();

    void exportToJson() const;  // 新增：JSON 匯出功能 
    
    size_t getTaskCount() const { return tasks.size(); }
};