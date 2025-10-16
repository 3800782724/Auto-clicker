#include <windows.h>
#include <iostream>
using namespace std;

// 封装鼠标操作类
class MouseSimulator {
public:
    // 模拟鼠标左键按下
    static bool LeftDown() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // 模拟鼠标左键释放
    static bool LeftUp() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // 模拟鼠标左键点击（带可选延迟）
    static bool LeftClick(DWORD delayMs = 10) {
        if (!LeftDown()) return false;
        Sleep(delayMs);
        return LeftUp();
    }

    // 模拟鼠标左键长按
    static bool LeftPress(DWORD durationMs = 50) {
        if (!LeftDown()) return false;
        Sleep(durationMs);
        return LeftUp();
    }
};

// 隐藏控制台窗口
void HideConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
}

// 显示控制台窗口
void ShowConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);
}

// 检查是否按下热键
bool IsHotKeyPressed(int vKey) {
    return (GetAsyncKeyState(vKey) & 0x8000);
}

// 连点器模式
void ldq(){
    int pressTime;  // 鼠标按下时间
    int intervalTime;  // 点击间隔时间
    cout << "按F11开始/停止点击，按ESC退出程序"  << endl;
    cout << "请输入鼠标按下时间（单位：毫秒，10~90）：" << endl ;
    cin >> pressTime;
    // 限制输入范围
    if (pressTime < 10) pressTime = 10;
    if (pressTime > 90) pressTime = 90;
    
    cout << "请输入每次点击间隔时间（单位：毫秒）：" << endl;
    cin >> intervalTime;
    if (intervalTime < 0) intervalTime = 0;
    
    cout << "设置完成，控制台将隐藏，按ESC显示控制台" << endl;
    Sleep(2000); // 等待用户阅读提示
    HideConsole(); // 隐藏控制台窗口
    
    while (true) {
        // 检查显示控制台
        if (IsHotKeyPressed(VK_F12)) {
            ShowConsole();
        }
        
        // 检查启动/停止热键
        if (IsHotKeyPressed(VK_F11)) { // F11键作为启动/停止热键
            // 点击循环
            do {
                MouseSimulator::LeftPress(pressTime);
                Sleep(intervalTime); // 点击间隔
                // 检查退出热键
                if (IsHotKeyPressed(VK_ESCAPE)) {
                    ShowConsole();
                    return;
                }
            } while (IsHotKeyPressed(VK_F11)); // 按住F11持续点击，松开停止
        }

        // 检查退出热键
        if (IsHotKeyPressed(VK_ESCAPE)) {
            ShowConsole();
            break;
        }

        Sleep(10); // 降低CPU占用
    }
} 

// 长按模式
void can(){
    cout << "按F11开始长按鼠标左键，松开F11停止，按ESC退出程序" << endl;
    cout << "控制台将隐藏，按F12显示控制台" << endl;
    Sleep(2000); // 等待用户阅读提示
    HideConsole(); // 隐藏控制台窗口
    
    while (true) {
        // 检查显示控制台
        if (IsHotKeyPressed(VK_F12)) {
            ShowConsole();
        }
        
        // 检查启动热键
        if (IsHotKeyPressed(VK_F11)) { 
            // 长按鼠标左键
            MouseSimulator::LeftDown();
            
            // 保持按下状态，直到松开F11或按下ESC
            while (IsHotKeyPressed(VK_F11) && !IsHotKeyPressed(VK_ESCAPE)) {
                Sleep(10);
            }
            
            // 释放鼠标左键
            MouseSimulator::LeftUp();
        }

        // 检查退出热键
        if (IsHotKeyPressed(VK_ESCAPE)) {
            ShowConsole();
            break;
        }

        Sleep(10); // 降低CPU占用
    }
}

int main() {
    // 模式选择 
    cout << "请选择模式：1-连点器 2-长按" << endl ;
    int moshi;
    cin >> moshi;  // 读取用户输入
    
    if(moshi == 1)
    {
        ldq();
    }
    else if(moshi == 2)  // 使用else if更安全
    {
        can(); 
    }
    else
    {
        cout << "无效的模式选择" << endl;
    }
        
    return 0;
}

