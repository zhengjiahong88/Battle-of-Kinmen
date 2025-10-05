#include "button.h"
#include "tcp_socket.h"
#include "scene.h"

void Single::handle() {
    SDL_Log("Single");
}

void Create::handle() {
    Base::id = 1;
    SceneBase::fieldStart();

    // 建立伺服器，監聽 8080 埠
    TCPSocket server(8080, "127.0.0.1");

    if (!server.is_valid()) SDL_Log("無法建立伺服器");

    if (!server.listen()) SDL_Log("監聽失敗");

    SDL_Log("伺服器正在監聽 127.0.0.1:8080");

    // 接受客戶端連線
    const auto client = server.accept();
    if (!client) SDL_Log("接受連線失敗");

    SDL_Log("客戶端已連線");

    // 接收並回覆訊息
    const string message = client->recv();
    if (!message.empty()) {
        SDL_Log("收到: %s", message.c_str());
        client->send("你好，客戶端！");
    }
}

void Join::handle() {
    Base::id = 2;
    SceneBase::fieldStart();
    TCPSocket client;

    if (!client.is_valid()) SDL_Log("無法建立客戶端");

    // 連接到伺服器
    if (!client.connect("127.0.0.1", 8080)) SDL_Log("連接失敗");

    SDL_Log("已連接到伺服器");

    // 傳送訊息
    client.send("你好，伺服器！");

    // 接收回覆
    const string response = client.recv();
    if (!response.empty()) {
        SDL_Log("收到: %s", response.c_str());
    }
}
