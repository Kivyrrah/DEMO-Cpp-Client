// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "tchar.h"
#include "afxsock.h" //Thêm cái này vào, nó là thư viện socket


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            //Code ở đây nhé các bạn
            //----------------------------

            //Khai báo Socket 
            AfxSocketInit(NULL);
            //Khai báo các Socket của Client
            CSocket client;

            //Khởi tạo Socket
            client.Create();
            //Kết nối tới Server port 3153
            client.Connect(_T("127.0.0.1"), 3153); //127.0.0.1 là một loopback; _T dùng để chuyển qua CString

            //Khai báo tin nhắn
            char message[100];
            int len = 0; //Độ dài tin nhắn

            //Bắt đầu gửi tin nhắn
            while (true)
            {
                cout << "Da ket noi voi Server thanh cong: " << endl;
                cout << "Hay nhap tin nhan cho Server: ";
                gets_s(message);
                len = strlen(message);

                //Gửi độ dài của chuỗi trước để Server còn lo liệu bộ nhớ lưu chuỗi
                client.Send(&len, sizeof(int), 0);
                client.Send(message, len, 0);

                //Nhận từ Server
                client.Receive(&len, sizeof(int), 0);

                //Vùng nhớ đủ để lưu chuỗi
                char* temp = new char[len + 1];

                client.Receive(message, len, 0);

                temp[len] = 0;

                cout << "Server: " << temp << endl;
                delete temp;

                //Ngắt Socket
                client.Close();
            }



            //----------------------------
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
