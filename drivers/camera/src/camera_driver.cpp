#include "camera_driver.h"
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <thread>
#include <atomic>

namespace EdgeAI {

class CameraDriver::Impl {
public:
    Impl(const CameraConfig& config) : config_(config) {
        gst_init(NULL, NULL);
        pipeline_ = createPipeline(config_);
        setupPipeline();
    }
    
    ~Impl() {
        stopStream();
        gst_object_unref(pipeline_);
    }
    
    bool initialize() {
        // Set pipeline state to READY
        GstStateChangeReturn ret = 
            gst_element_set_state(pipeline_, GST_STATE_READY);
        return ret != GST_STATE_CHANGE_FAILURE;
    }
    
    bool startStream() {
        running_ = true;
        streamThread_ = std::thread(&Impl::streamLoop, this);
        return true;
    }
    
    void stopStream() {
        running_ = false;
        if (streamThread_.joinable()) {
            streamThread_.join();
        }
        gst_element_set_state(pipeline_, GST_STATE_NULL);
    }
    
    cv::Mat captureFrame() {
        std::lock_guard<std::mutex> lock(frameMutex_);
        return currentFrame_.clone();
    }
    
private:
    GstElement* pipeline_;
    GstElement* appsink_;
    CameraConfig config_;
    cv::Mat currentFrame_;
    std::mutex frameMutex_;
    std::atomic<bool> running_{false};
    std::thread streamThread_;
    std::function<void(cv::Mat)> callback_;
    
    GstElement* createPipeline(const CameraConfig& config) {
        std::string pipelineStr;
        if (config.type == CAMERA_CSI) {
            // JetPack 6.2 nvarguscamerasrc with NVMM hardware accelerated conversion
            pipelineStr = "nvarguscamerasrc sensor-id=0 ! "
                          "video/x-raw(memory:NVMM),width=" + std::to_string(config.width) +
                          ",height=" + std::to_string(config.height) +
                          ",framerate=" + std::to_string(config.fps) + "/1,format=NV12 ! "
                          "nvvidconv ! video/x-raw,format=BGRx ! "
                          "videoconvert ! video/x-raw,format=BGR ! "
                          "appsink name=sink drop=true max-buffers=2";
        } else {
            // USB V4L2 fallback
            pipelineStr = "v4l2src device=" + config.device + " ! "
                          "video/x-raw,width=" + std::to_string(config.width) +
                          ",height=" + std::to_string(config.height) +
                          ",framerate=" + std::to_string(config.fps) + "/1 ! "
                          "videoconvert ! video/x-raw,format=BGR ! "
                          "appsink name=sink drop=true max-buffers=2";
        }
            
        GError* error = nullptr;
        GstElement* pipeline = gst_parse_launch(pipelineStr.c_str(), &error);
        if (!pipeline || error) {
            std::cerr << "Failed to parse GStreamer pipeline: " 
                      << (error ? error->message : "unknown error") << std::endl;
            if (error) g_error_free(error);
            return nullptr;
        }
        appsink_ = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
        gst_app_sink_set_drop(GST_APP_SINK(appsink_), true);
        gst_app_sink_set_max_buffers(GST_APP_SINK(appsink_), 2);
        
        return pipeline;
    }
    
    void streamLoop() {
        gst_element_set_state(pipeline_, GST_STATE_PLAYING);
        
        while (running_) {
            GstSample* sample = 
                gst_app_sink_pull_sample(GST_APP_SINK(appsink_));
            
            if (sample) {
                GstBuffer* buffer = gst_sample_get_buffer(sample);
                GstMapInfo map;
                gst_buffer_map(buffer, &map, GST_MAP_READ);
                
                cv::Mat frame(config_.height, config_.width, 
                              CV_8UC3, map.data);
                
                std::lock_guard<std::mutex> lock(frameMutex_);
                currentFrame_ = frame.clone();
                
                if (callback_) {
                    callback_(currentFrame_);
                }
                
                gst_buffer_unmap(buffer, &map);
                gst_sample_unref(sample);
            }
        }
    }
};

CameraDriver::CameraDriver(const CameraConfig& config) 
    : pImpl(std::make_unique<Impl>(config)) {}

CameraDriver::~CameraDriver() = default;

bool CameraDriver::initialize() {
    return pImpl->initialize();
}

bool CameraDriver::startStream() {
    return pImpl->startStream();
}

void CameraDriver::stopStream() {
    pImpl->stopStream();
}

cv::Mat CameraDriver::captureFrame() {
    return pImpl->captureFrame();
}

} // namespace EdgeAI
