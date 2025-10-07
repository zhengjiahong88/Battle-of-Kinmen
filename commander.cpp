#include "commander.h"
#include "tcp_socket.h"

Commander::Commander(const std::string& file, const std::string& name, const SDL_FRect rect)
    : rect(rect) {
    headshot.init(name, rect, 40, 255);
    headshot.initImage("headshot/" + file);
    start.init("開始", {1360, 1000, 280, 40}, 40, 0);
}

bool Commander::handle() {
    for (int i = 0; i < 12; i++) if (self[i].icon.handle()) choice = i;
    if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        if (const MapPos pos = toMap({x, y}); inRange(pos) && basemap[pos] != 'S') self[choice].target = toF(pos);
    }
    if (start.handle()) {
        Base::start = true;
        return true;
    }
    return false;
}

void Commander::draw() {
    for (auto & s : self) {
        s.move();
        s.icon.draw();
    }
    start.draw();
}

Hu::Hu() : Commander("hu", "胡璉", {1248.f, 376.f, 168.f, 224.f}) {
    for (int i = 0; i < 12; i++) {
        const float x = i % 3;
        const float y = i / 3;
        self[i].init("步兵團", "roc", {240 * x + 1200, 160 * y + 240});
    }
    key.init("難度", 40, 255);
    value.init("2", 40, 255);
    add.init("+", {1360, 920, 40, 40}, 40, 0);
    sub.init("-", {1600, 920, 40, 40}, 40, 0);
}

bool Hu::handle() {
    if (Commander::handle()) {
        TCPSocket server(8080, "127.0.0.1");

        if (!server.is_valid()) SDL_Log("無法建立伺服器");

        if (!server.listen()) SDL_Log("監聽失敗");

        SDL_Log("伺服器正在監聽 127.0.0.1:8080");

        // 接受客戶端連線
        const auto client = server.accept();
        if (!client) SDL_Log("接受連線失敗");

        SDL_Log("客戶端已連線");

        for (const auto & army : self) client->send("roc " + to_string(toMap(army.target)));
        client->send(std::to_string(difficulty));
    }
    if (add.handle()) {
        difficulty++;
        value.init(std::to_string(difficulty), 40, 255);
    }
    if (sub.handle()) {
        difficulty--;
        value.init(std::to_string(difficulty), 40, 255);
    }
    return false;
}

void Hu::draw() {
    Commander::draw();
    value.draw({1360, 920, 280, 40});
    key.draw({1360, 840, 280, 40});
    add.draw();
    sub.draw();
}

Li::Li() : Commander("li", "李良榮", {1584, 376, 168, 224}) {
    for (int i = 0; i < 12; i++) {
        const float x = i % 3;
        const float y = i / 3;
        const FPos rect = {240 * x + 1200, 160 * y + 240};
        if (i < 8) self[i].init("步兵團", "roc", rect);
        else if (i == 8) self[i].init("戰車營", "tank", rect);
        else if (i == 11) self[i].init("工兵營", "engineer", rect);
        else self[i].init("砲兵連", "artillery", rect);
    }
}

bool Li::handle() {
    if (Commander::handle()) {
        TCPSocket client;

        if (!client.is_valid()) SDL_Log("無法建立客戶端");

        // 連接到伺服器
        if (!client.connect("127.0.0.1", 8080)) SDL_Log("連接失敗");

        SDL_Log("已連接到伺服器");

        for (const auto & army : self) client.send(army.arms + " " + to_string(toMap(army.target)));
    }
    return false;
}
