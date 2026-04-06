# C++ Todo List CLI

C/C++ 命令列任務管理工具，支援中文輸入與顯示，資料可永久存取，還能輸出JSON檔

## 功能特色

- ✅ 新增任務（支援中文標題與詳細描述）
- ✅ 列出所有任務
- ✅ 標記任務為已完成
- ✅ 刪除指定任務
- ✅ 清除所有任務（附確認機制）
- ✅ 資料持久化：關閉程式後任務不會消失
- ✅ 輸出JOSN：一鍵匯出為格式化 JSON 檔案

## 技術 stack

- C++20
- CMake 建置系統
- nlohmann/json（JSON 匯出）
- Windows UTF-8 終端機支援

## 如何建置與執行

### 使用 VS Code + CMake Tools（推薦）

1. 開啟專案資料夾
2. 按 `Ctrl + Shift + P` → 輸入 `CMake: Clean Rebuild`
3. 建置完成後，按 `CMake: Run Without Debugging` 執行

### 或使用終端機指令

```bash
cmake -B build -S . -G "Ninja"
cmake --build build --config Debug
./build/bin/cpp-todo-cli.exe