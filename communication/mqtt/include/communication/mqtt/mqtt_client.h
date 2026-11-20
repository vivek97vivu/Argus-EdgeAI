#pragma once

#include <string>
#include <memory>
#include <functional>

namespace EdgeAI {

class MQTTClient {
public:
    MQTTClient(const std::string& host = "localhost", int port = 1883);
    ~MQTTClient();

    bool connect(const std::string& client_id);
    void disconnect();
    bool isConnected() const;

    bool publish(const std::string& topic, const std::string& payload, int qos = 0, bool retain = false);
    bool subscribe(const std::string& topic, std::function<void(const std::string&, const std::string&)> callback, int qos = 0);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace EdgeAI
