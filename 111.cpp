#include <windows.h>
#include <iostream>
using namespace std;

// ��װ��������
class MouseSimulator {
public:
    // ģ������������
    static bool LeftDown() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // ģ���������ͷ�
    static bool LeftUp() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // ģ�����������������ѡ�ӳ٣�
    static bool LeftClick(DWORD delayMs = 10) {
        if (!LeftDown()) return false;
        Sleep(delayMs);
        return LeftUp();
    }

    // ģ������������
    static bool LeftPress(DWORD durationMs = 50) {
        if (!LeftDown()) return false;
        Sleep(durationMs);
        return LeftUp();
    }
};

// ���ؿ���̨����
void HideConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
}

// ��ʾ����̨����
void ShowConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);
}

// ����Ƿ����ȼ�
bool IsHotKeyPressed(int vKey) {
    return (GetAsyncKeyState(vKey) & 0x8000);
}

// ������ģʽ
void ldq(){
    int pressTime;  // ��갴��ʱ��
    int intervalTime;  // ������ʱ��
    cout << "��F11��ʼ/ֹͣ�������ESC�˳�����"  << endl;
    cout << "��������갴��ʱ�䣨��λ�����룬10~90����" << endl ;
    cin >> pressTime;
    // �������뷶Χ
    if (pressTime < 10) pressTime = 10;
    if (pressTime > 90) pressTime = 90;
    
    cout << "������ÿ�ε�����ʱ�䣨��λ�����룩��" << endl;
    cin >> intervalTime;
    if (intervalTime < 0) intervalTime = 0;
    
    cout << "������ɣ�����̨�����أ���ESC��ʾ����̨" << endl;
    Sleep(2000); // �ȴ��û��Ķ���ʾ
    HideConsole(); // ���ؿ���̨����
    
    while (true) {
        // �����ʾ����̨
        if (IsHotKeyPressed(VK_F12)) {
            ShowConsole();
        }
        
        // �������/ֹͣ�ȼ�
        if (IsHotKeyPressed(VK_F11)) { // F11����Ϊ����/ֹͣ�ȼ�
            // ���ѭ��
            do {
                MouseSimulator::LeftPress(pressTime);
                Sleep(intervalTime); // ������
                // ����˳��ȼ�
                if (IsHotKeyPressed(VK_ESCAPE)) {
                    ShowConsole();
                    return;
                }
            } while (IsHotKeyPressed(VK_F11)); // ��סF11����������ɿ�ֹͣ
        }

        // ����˳��ȼ�
        if (IsHotKeyPressed(VK_ESCAPE)) {
            ShowConsole();
            break;
        }

        Sleep(10); // ����CPUռ��
    }
} 

// ����ģʽ
void can(){
    cout << "��F11��ʼ�������������ɿ�F11ֹͣ����ESC�˳�����" << endl;
    cout << "����̨�����أ���F12��ʾ����̨" << endl;
    Sleep(2000); // �ȴ��û��Ķ���ʾ
    HideConsole(); // ���ؿ���̨����
    
    while (true) {
        // �����ʾ����̨
        if (IsHotKeyPressed(VK_F12)) {
            ShowConsole();
        }
        
        // ��������ȼ�
        if (IsHotKeyPressed(VK_F11)) { 
            // ����������
            MouseSimulator::LeftDown();
            
            // ���ְ���״̬��ֱ���ɿ�F11����ESC
            while (IsHotKeyPressed(VK_F11) && !IsHotKeyPressed(VK_ESCAPE)) {
                Sleep(10);
            }
            
            // �ͷ�������
            MouseSimulator::LeftUp();
        }

        // ����˳��ȼ�
        if (IsHotKeyPressed(VK_ESCAPE)) {
            ShowConsole();
            break;
        }

        Sleep(10); // ����CPUռ��
    }
}

int main() {
    // ģʽѡ�� 
    cout << "��ѡ��ģʽ��1-������ 2-����" << endl ;
    int moshi;
    cin >> moshi;  // ��ȡ�û�����
    
    if(moshi == 1)
    {
        ldq();
    }
    else if(moshi == 2)  // ʹ��else if����ȫ
    {
        can(); 
    }
    else
    {
        cout << "��Ч��ģʽѡ��" << endl;
    }
        
    return 0;
}

