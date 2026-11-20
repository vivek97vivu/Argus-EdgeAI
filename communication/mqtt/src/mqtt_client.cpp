#include "communication/mqtt/mqtt_client.h"
#include <iostream>
#include <atomic>
#include <mosquitto.h>

namespace EdgeAI {

class MQTTClient::Impl {
public:
    Impl(const std::string& host, int port)
        : host_(host), port_(port), mosq_(nullptr), connected_(false) {
        mosquitto_lib_init();
    }

    ~Impl() {
        disconnect();
        mosquitto_lib_cleanup();
    }

    bool connect(const std::string& client_id) {
        mosq_ = mosquitto_new(client_id.c_str(), true, this);
        if (!mosq_) {
            std::cerr << "Failed to create mosquitto instance." << std::endl;
            return false;
        }

        int rc = mosquitto_connect(mosq_, host_.c_str(), port_, 60);
        if (rc != MOSQ_ERR_SUCCESS) {
            std::cerr << "MQTT connection failed: " << mosquitto_strerror(rc) << std::endl;
            return false;
        }

        mosquitto_loop_start(mosq_);
        connected_ = true;
        return true;
    }

    void disconnect() {
        if (mosq_ && connected_) {
            mosquitto_disconnect(mosq_);
            mosquitto_loop_stop(mosq_, true);
            mosquitto_destroy(mosq_);
            mosq_ = nullptr;
            connected_ = false;
        }
    }

    bool isConnected() const {
        return connected_;
    }

    bool publish(const std::string& topic, const std::string& payload, int qos, bool retain) {
        if (!mosq_ || !connected_) return false;
        int rc = mosquitto_publish(mosq_, nullptr, topic.c_str(), 
                                   static_cast<int>(payload.size()), payload.data(), qos, retain);
        return rc == MOSQ_ERR_SUCCESS;
    }

    bool subscribe(const std::string& topic, std::function<void(const std::string&, const std::string&)> callback, int qos) {
        (void)callback;
        if (!mosq_ || !connected_) return false;
        return mosquitto_subscribe(mosq_, nullptr, topic.c_str(), qos) == MOSQ_ERR_SUCCESS;
    }

private:
    std::string host_;
    int port_;
    struct mosquitto* mosq_;
    std::atomic<bool> connected_;
};

MQTTClient::MQTTClient(const std::string& host, int port)
    : pImpl(std::make_unique<Impl>(host, port)) {}

MQTTClient::~MQTTClient() = default;

bool MQTTClient::connect(const std::string& client_id) {
    return pImpl->connect(client_id);
}

void MQTTClient::disconnect() {
    pImpl->disconnect();
}

bool MQTTClient::isConnected() const {
    return pImpl->isConnected();
}

bool MQTTClient::publish(const std::string& topic, const std::string& payload, int qos, bool retain) {
    return pImpl->publish(topic, payload, qos, retain);
}

bool MQTTClient::subscribe(const std::string& topic, std::function<void(const std::string&, const std::string&)> callback, int qos) {
    return pImpl->subscribe(topic, callback, qos);
}

} // namespace EdgeAI
