<div align="center">

# ⚡ Argus-EdgeAI

### High-Performance Edge AI Platform for NVIDIA Jetson AGX Orin 64GB
**JetPack 6.2.1 [L4T 36.4.7] • CUDA 12.6 • TensorRT 10.3 • OpenCV 4.10 (CUDA)**

<br/>

[![Platform](https://img.shields.io/badge/Platform-Jetson%20AGX%20Orin%2064GB-76B900?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/embedded/jetson-agx-orin)
[![JetPack](https://img.shields.io/badge/JetPack-6.2.1%20%5BL4T%2036.4.7%5D-76B900?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/embedded/jetpack)
[![Ubuntu](https://img.shields.io/badge/Ubuntu-22.04%20LTS-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)](https://ubuntu.com/)
[![CUDA](https://img.shields.io/badge/CUDA-12.6.68-76B900?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/cuda-toolkit)
[![TensorRT](https://img.shields.io/badge/TensorRT-10.3.0.30-76B900?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/tensorrt)
[![OpenCV](https://img.shields.io/badge/OpenCV-4.10.0%20(CUDA)-5C3EE8?style=for-the-badge&logo=opencv&logoColor=white)](https://opencv.org/)
[![cuDNN](https://img.shields.io/badge/cuDNN-9.3.0-0071C5?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/cudnn)
[![VPI](https://img.shields.io/badge/VPI-3.2.4-0071C5?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/embedded/vpi)
[![Python](https://img.shields.io/badge/Python-3.10-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![MQTT](https://img.shields.io/badge/MQTT-5.0-660066?style=for-the-badge&logo=eclipsemosquitto&logoColor=white)](https://mqtt.org/)
[![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)](LICENSE)

<br/>

*An intelligent, hardware-accelerated edge platform delivering real-time facial recognition, biometric voice verification, automated attendance tracking, and low-latency C++ HAL drivers on Jetson AGX Orin.*

<br/>

[Key Capabilities](#-overview) • [System Architecture](#-system-architecture) • [Block Diagram](#-block-diagram) • [Hardware Requirements](#-hardware-requirements) • [Installation Guide](#-installation) • [API Reference](#-api-reference)

</div>

---

##  Table of Contents

1. [Overview](#-overview)
2. [System Architecture](#-system-architecture)
3. [Block Diagram](#-block-diagram)
4. [Flow Diagrams](#-flow-diagrams)
5. [Features](#-features)
6. [Hardware Requirements](#-hardware-requirements)
7. [Software Requirements](#-software-requirements)
8. [Installation](#-installation)
9. [Configuration](#-configuration)
10. [Usage](#-usage)
11. [API Reference](#-api-reference)
12. [Performance Metrics](#-performance-metrics)
13. [Troubleshooting](#-troubleshooting)
14. [Development](#-development)

---

##  Overview

The **NVIDIA Jetson AGX Orin Edge AI System** is a comprehensive, production-ready solution for intelligent surveillance, workforce management, and real-time analytics at the edge. Built specifically for the NVIDIA Jetson AGX Orin platform, this system leverages the power of GPU-accelerated AI inference to deliver high-performance computer vision and machine learning capabilities in a compact, power-efficient form factor.

### Key Capabilities

- **Real-time Face Recognition** - Identify and verify individuals with sub-100ms latency
- **Voice Authentication** - Biometric voice verification for secure access
- **Multi-Person Tracking** - Track multiple individuals simultaneously with DeepSORT
- **Automated Attendance** - Touchless check-in/out with payroll integration
- **Visitor Management** - Register, track, and manage guests
- **Intelligent Surveillance** - Anomaly detection and real-time alerts
- **Hardware Integration** - Seamless control of cameras, microphones, GPIO, SPI, UART, and I2C
- **Cloud Connectivity** - MQTT, WebSocket, and REST API support

### Use Cases

- **Enterprise Security** - Access control and surveillance
- **Workforce Management** - Automated attendance and payroll
- **Smart Buildings** - Occupancy monitoring and analytics
- **Retail Analytics** - Customer counting and behavior analysis
- **Healthcare** - Patient monitoring and access control
- **Education** - Campus security and attendance tracking

---

##  System Architecture

### High-Level Architecture

```mermaid
flowchart TD
    classDef app fill:#2D3748,stroke:#4A5568,stroke-width:2px,color:#fff;
    classDef comm fill:#1A365D,stroke:#2B6CB0,stroke-width:2px,color:#fff;
    classDef ai fill:#22543D,stroke:#38A169,stroke-width:2px,color:#fff;
    classDef hal fill:#744210,stroke:#D69E2E,stroke-width:2px,color:#fff;
    classDef hw fill:#1C4532,stroke:#48BB78,stroke-width:3px,color:#fff;

    subgraph APP ["Application & Presentation Layer"]
        C_APP["C++ Core Application (edge_ai_app)"]:::app
        DASH["Web Dashboard UI (React/TS)"]:::app
        MOB["Mobile App (React Native)"]:::app
        EXT["External Cloud & REST Clients"]:::app
    end

    subgraph COMM ["API & Communication Layer"]
        direction LR
        REST["REST API Server (Port 8000)"]:::comm
        WS["WebSocket Server (Port 8080)"]:::comm
        MQTT["MQTT Client (Port 1883)"]:::comm
        TCP["TCP/IP Telemetry"]:::comm
    end

    subgraph AI ["AI Processing Pipeline (TensorRT 10.3 / CUDA 12.6)"]
        direction TB
        FD["Face Detection (TensorRT Engine)"]:::ai --> FR["Face Recognition (512-d Embedding)"]:::ai
        FR --> VA["Voice Biometrics (ALSA/VAD)"]:::ai
        VA --> HD["Human Detection & Tracking (DeepSORT)"]:::ai
        HD --> AT["Attendance & Access Control Engine"]:::ai
        AT --> VM["Visitor Management & Security"]:::ai
    end

    subgraph HAL ["Hardware Abstraction Layer (HAL C++17)"]
        direction LR
        CAM["CSI/USB Camera Driver"]:::hal
        MIC["Audio / Microphone Driver"]:::hal
        GPIO["GPIO / PWM / Door Driver"]:::hal
        SPI["SPI Bus Driver"]:::hal
        UART["Async UART Driver"]:::hal
        I2C["I2C Sensor Driver"]:::hal
        STOR["Encrypted Storage / Cache"]:::hal
    end

    subgraph HW ["NVIDIA Jetson AGX Orin 64GB Hardware Acceleration"]
        GPU["Ampere GPU (2048 CUDA Cores, 64 Tensor Cores)"]:::hw
        NPU["2x NVDLA 2.0 Engines (275 TOPS INT8)"]:::hw
        STACK["JetPack 6.2.1 • L4T 36.4.7 • Linux Kernel 5.15-tegra"]:::hw
    end

    APP ==> COMM
    COMM ==> AI
    AI ==> HAL
    HAL ==> HW
```

---

##  Block Diagram

### System Component Block Diagram

```mermaid
flowchart LR
    classDef dev fill:#1A202C,stroke:#4A5568,stroke-width:2px,color:#fff;
    classDef jetson fill:#1C4532,stroke:#48BB78,stroke-width:2px,color:#fff;
    classDef cloud fill:#2C5282,stroke:#4299E1,stroke-width:2px,color:#fff;

    subgraph IN ["Input Telemetry Devices"]
        CAM["CSI / USB Cameras (MIPI/UVC)"]:::dev
        MIC["Microphone Array (I2S/ALSA)"]:::dev
        SENS["Sensors & GPIO Triggers"]:::dev
    end

    subgraph JETSON ["NVIDIA Jetson AGX Orin 64GB (Edge System)"]
        direction TB
        
        subgraph DRV ["Hardware Driver Layer"]
            D1["CameraDriver (nvarguscamerasrc)"]
            D2["MicrophoneDriver & AudioProcessor"]
            D3["GPIODriver (PWM & Interrupts)"]
            D4["I2C, SPI & UART Drivers"]
        end

        subgraph AI_CORE ["Edge AI Engine"]
            P1["Pre-processing (NVMM Memory)"]
            P2["TensorRT 10.3 Accelerated Inference"]
            P3["Feature Extraction & Embeddings"]
        end

        subgraph BIZ ["Core Applications & DB"]
            B1["Attendance Engine"]
            B2["Visitor Management"]
            B3["Perimeter Surveillance"]
            DB[(SQLite Attendance DB)]
        end

        subgraph NET ["Network Interfaces"]
            NET1["Embedded REST API (8000)"]
            NET2["WebSocket Server (8080)"]
            NET3["MQTT Client (1883)"]
        end

        DRV --> AI_CORE
        AI_CORE --> BIZ
        BIZ <--> DB
        BIZ --> NET
    end

    subgraph OUT ["User Interface & External Consumers"]
        UI_DASH["Web Dashboard"]:::cloud
        UI_MOB["Mobile App"]:::cloud
        UI_MQTT["Cloud MQTT Broker"]:::cloud
    end

    IN ==> DRV
    NET ==> OUT
```

---

##  Flow Diagrams

### 1. Main System Control Flow

```mermaid
flowchart TD
    START([System Startup]) --> LOAD_CFG["Load Configuration<br/>(config.yaml)"]
    LOAD_CFG --> INIT_HW["Initialize Hardware Drivers<br/>(Camera, GPIO, Storage, SPI, I2C, UART)"]
    
    INIT_HW --> INIT_AI["Initialize TensorRT 10 AI Engines"]
    subgraph MODELS ["AI Models Loading"]
        M1["Face Detection Engine"]
        M2["Face Recognition Engine"]
        M3["Voice Auth Engine"]
        M4["Human Detection Engine"]
    end
    INIT_AI --> MODELS
    
    MODELS --> INIT_COMM["Initialize Communication Services"]
    subgraph SERVICES ["Network Services"]
        S1["MQTT Client (1883)"]
        S2["REST API Server (8000)"]
        S3["WebSocket Server (8080)"]
    end
    INIT_COMM --> SERVICES
    
    SERVICES --> LOOP["Start Main Processing Loop (Live Inference)"]
    LOOP --> RUNNING{"Running State: Active"}
    RUNNING -- "Signal Interrupt (SIGINT/SIGTERM)" --> SHUTDOWN["Shutdown Handler & Resource Cleanup"]
    SHUTDOWN --> DONE([Graceful Exit])
```

### 2. AI Processing Pipeline Flow

```mermaid
flowchart TD
    FRAME["Capture Video Frame<br/>(nvarguscamerasrc CSI/USB)"] --> PRE["Pre-processing<br/>(Resize, NVMM Color Conversion, Normalize)"]
    
    PRE --> DET["Face Detection<br/>(TensorRT 10.3 Engine)"]
    DET --> NMS["NMS Filtering & Bounding Box Extraction"]
    
    NMS --> REC["Face Recognition<br/>(Align Face & Extract 512-d Embedding)"]
    REC --> SEARCH["Vector Similarity Search<br/>(SQLite / FAISS Database)"]
    
    SEARCH --> MATCH{"Identity Matched?<br/>(Threshold >= 0.70)"}
    MATCH -- "Yes" --> EMP["Known Employee Verified"]
    MATCH -- "No" --> UNK["Visitor / Unregistered Person"]
    
    EMP --> ACT_EMP["Record Attendance & Trigger Door Unlock (GPIO)"]
    UNK --> ACT_UNK["Log Visitor Event & Send Security Alert (MQTT)"]
    
    ACT_EMP --> STORE["Save Audit Event to DB & Broadcast via WebSocket"]
    ACT_UNK --> STORE
```

### 3. Attendance Management Flow

```mermaid
sequenceDiagram
    autonumber
    actor Employee
    participant Camera as CSI Camera (nvarguscamerasrc)
    participant Jetson as Argus-EdgeAI Core (Jetson AGX Orin)
    participant DB as SQLite Attendance DB
    participant GPIO as GPIO Controller (Pin 17, 20)
    participant Broker as MQTT / Cloud Dashboard

    Employee->>Camera: Enters camera field of view
    Camera->>Jetson: Streams NV12 frames via NVMM pipeline
    Note over Jetson: TensorRT 10 Face Detection & Alignment
    Note over Jetson: 512-d Feature Extraction & Vector Search
    Jetson->>DB: Query employee record & check last check-in status
    alt Employee Verified (Match >= 0.70)
        Jetson->>DB: Record attendance transaction (Timestamp, Status: IN)
        Jetson->>GPIO: Pulse GPIO 20 (Unlock Door Relay) & GPIO 17 (Green LED)
        Jetson->>Broker: Publish MQTT event (edge_ai/attendance)
    else Unknown Face / Restricted Access
        Jetson->>GPIO: Trigger GPIO 18 (Alert LED) & GPIO 19 (Buzzer)
        Jetson->>Broker: Publish Security Alert (edge_ai/alerts)
    end
```

### 4. Hardware Communication Flow

```mermaid
flowchart TD
    classDef app fill:#2B6CB0,stroke:#2C5282,color:#fff;
    classDef drv fill:#2F855A,stroke:#22543D,color:#fff;
    classDef sys fill:#C05621,stroke:#7B341E,color:#fff;
    classDef hw fill:#4A5568,stroke:#2D3748,color:#fff;

    subgraph APP ["Application Control Layer"]
        C_CTRL["Camera Control"]:::app
        G_CTRL["GPIO / Lock Control"]:::app
        S_CTRL["SPI Telemetry"]:::app
        U_CTRL["UART Serial Comm"]:::app
        I_CTRL["I2C Sensor Read"]:::app
        A_CTRL["Audio Processor"]:::app
    end

    subgraph DRV ["C++ Driver Interface (HAL)"]
        D_CAM["CameraDriver (GStreamer)"]:::drv
        D_GPIO["GPIODriver (PWM & Sysfs)"]:::drv
        D_SPI["SPIDriver"]:::drv
        D_UART["UARTDriver (Async)"]:::drv
        D_I2C["I2CDriver (SMBus)"]:::drv
        D_MIC["MicrophoneDriver (ALSA)"]:::drv
    end

    subgraph SYS ["Linux Kernel & Character Devices (L4T 36.4.7)"]
        K_CAM["/dev/video0 (nvarguscamerasrc)"]:::sys
        K_GPIO["/sys/class/gpio & PWM"]:::sys
        K_SPI["/dev/spidev0.0"]:::sys
        K_UART["/dev/ttyTHS1"]:::sys
        K_I2C["/dev/i2c-1"]:::sys
        K_ALSA["ALSA PCM Interface"]:::sys
    end

    subgraph HW ["AGX Orin Hardware Peripherals"]
        H_CAM["MIPI CSI Camera (IMX219/AR0234)"]:::hw
        H_PINS["40-Pin Header (Relays & LEDs)"]:::hw
        H_SPI["SPI External Devices"]:::hw
        H_UART["External Serial Controllers"]:::hw
        H_I2C["I2C Sensors (BME280/MPU6050)"]:::hw
        H_MIC["USB / I2S Microphone Array"]:::hw
    end

    APP ==> DRV
    DRV ==> SYS
    SYS ==> HW
```

### 5. Data Flow Diagram

```mermaid
flowchart LR
    classDef in fill:#2B6CB0,color:#fff;
    classDef proc fill:#22543D,color:#fff;
    classDef store fill:#744210,color:#fff;
    classDef out fill:#4A5568,color:#fff;

    subgraph INPUT ["Input Telemetry"]
        CAM_FEED["CSI/USB Camera Stream"]:::in
        MIC_FEED["Microphone Audio Stream"]:::in
        SENS_FEED["GPIO & Serial Sensors"]:::in
    end

    subgraph PIPELINE ["Edge AI Processing (Jetson Orin)"]
        direction TB
        P_RAW["Raw Data Ingestion"]:::proc
        P_AI["TensorRT 10 Deep Learning Inference"]:::proc
        P_DEC["Access Control & Decision Engine"]:::proc
        P_ACT["Action Dispatcher"]:::proc
        P_RAW --> P_AI --> P_DEC --> P_ACT
    end

    subgraph DEST ["Storage & Cache"]
        D_SQL[(SQLite Database)]:::store
        D_FS[("File System (Images/Logs)")]:::store
        D_MEM[("In-Memory State Cache")]:::store
    end

    subgraph COMM ["Network Channels"]
        C_MQTT["MQTT Broker (Port 1883)"]:::out
        C_WS["WebSocket Server (Port 8080)"]:::out
        C_REST["REST API (Port 8000)"]:::out
    end

    subgraph EXT ["Clients & Enterprise"]
        DASH["Web Monitoring Dashboard"]
        MOBILE["Mobile App Alerts"]
        CLOUD["Enterprise Cloud Server"]
    end

    INPUT ==> PIPELINE
    PIPELINE ==> DEST
    PIPELINE ==> COMM
    COMM ==> EXT
```

---

##  Features

### Core Features

| Feature | Description | Status |
|---------|-------------|--------|
| **Face Detection** | Real-time face detection using TensorRT optimized YOLO/FaceNet | ✅ |
| **Face Recognition** | Identify individuals with high accuracy and low latency | ✅ |
| **Voice Authentication** | Biometric voice verification for secure access | ✅ |
| **Human Detection** | Full-body detection for surveillance | ✅ |
| **Person Tracking** | Multi-object tracking with DeepSORT | ✅ |
| **Attendance Management** | Automated check-in/out with payroll integration | ✅ |
| **Visitor Management** | Guest registration and tracking | ✅ |
| **Surveillance** | Anomaly detection and real-time alerts | ✅ |

### Hardware Interfaces

| Interface | Protocol | Features |
|-----------|----------|----------|
| **Camera** | CSI, USB, IP | 4K@30fps, 1080p@60fps, Auto-exposure, White balance |
| **GPIO** | Sysfs | Digital I/O, Interrupts, PWM, Debouncing |
| **SPI** | Linux SPI | Full-duplex, Multi-device, Async transfers |
| **UART** | TTY | RS232, RS485, Flow control, Async I/O |
| **I2C** | Linux I2C | SMBus, Multi-master, Device scanning |
| **Microphone** | ALSA | 16-bit, 48kHz, Voice activity detection |
| **Storage** | File System | SSD, eMMC, Backup, Compression, Encryption |

### Communication Protocols

| Protocol | Port | Features |
|----------|------|----------|
| **REST API** | 8000 | HTTP/1.1, JSON, Swagger, Authentication |
| **WebSocket** | 8080 | Real-time, Bi-directional, Stateful |
| **MQTT** | 1883 | Pub/Sub, QoS, TLS, Wildcards |
| **TCP/IP** | Custom | Streaming, Reliable, Fast |

### Data Management

| Component | Features |
|-----------|----------|
| **Database** | SQLite, Schema migrations, ACID compliance |
| **File System** | Hierarchical storage, Metadata, Indexing |
| **Cache** | LRU, Configurable size, Auto-cleanup |
| **Backup** | Scheduled, Compression, Encryption, Versioned |
| **Indexing** | Full-text search, Metadata extraction, Keywords |

---

##  Hardware Requirements

### Target Hardware Specifications

| Component | Specification (Target Hardware: Jetson AGX Orin 64GB) |
| :--- | :--- |
| **Developer Kit** | NVIDIA Jetson AGX Orin Developer Kit (`p3701-0005`) |
| **CPU Architecture** | 12-core ARM Cortex-A78AE v8.2 64-bit CPU (up to 2.2 GHz) |
| **GPU Engine** | NVIDIA Ampere (2048 CUDA Cores, 64 Tensor Cores, `sm_87`) |
| **AI Inference TOPS**| Up to 275 TOPS (INT8) compute capability |
| **System Memory** | 64GB 256-bit LPDDR5 (204.8 GB/s bandwidth) |
| **Storage** | 64GB eMMC 5.1 + M.2 Key-M NVMe PCIe Gen4 SSD slot |
| **Power Profile** | `MODE_50W` (Configurable 15W - 60W via `nvpmodel`) |
| **Camera Bus** | 16-lane MIPI CSI-2 connector (`nvarguscamerasrc` / V4L2) |
| **Audio Interface** | I2S / USB Microphone with ALSA driver support |
| **Network** | 10 Gigabit Ethernet RJ45 + M.2 Key-E Wi-Fi / BT |
| **Operating System** | Ubuntu 22.04 LTS Jammy (Kernel `5.15.148-tegra`) |
| **L4T / JetPack** | **JetPack 6.2.1** `[L4T 36.4.7]` |

> [!TIP]
> **Recommended Production Hardware:**
> - High-speed NVMe SSD (512GB+) mounted at `/var/edge_ai` for facial embeddings and continuous video buffer.
> - High-resolution MIPI-CSI global-shutter camera (e.g. Arducam AR0234 or Sony IMX477) for high-speed tracking.
> - Active thermal cooling fan module for sustained 50W/60W AI inference workloads.

### Supported Cameras

| Camera Model | Interface | Resolution | FPS |
|--------------|-----------|------------|-----|
| Raspberry Pi Camera v2 | CSI | 3280x2464 | 30 |
| Raspberry Pi HQ Camera | CSI | 4056x3040 | 30 |
| Arducam AR0234 | CSI | 1920x1080 | 120 |
| Logitech C920 | USB | 1920x1080 | 30 |
| Elgato Facecam | USB | 1920x1080 | 60 |
| Axis IP Camera | Network | 3840x2160 | 30 |

### Supported Sensors

| Sensor Type | Interface | Protocol |
|-------------|-----------|----------|
| MPU6050 (IMU) | I2C | 0x68/0x69 |
| BMP280 (Temp/Pressure) | I2C | 0x76/0x77 |
| BME280 (Temp/Humidity/Pressure) | I2C | 0x76/0x77 |
| ADS1115 (ADC) | I2C | 0x48/0x49 |
| MCP3008 (ADC) | SPI | CS0-CS3 |
| MAX31855 (Thermocouple) | SPI | CS0-CS3 |
| HC-SR04 (Ultrasonic) | GPIO | Trigger/Echo |
| PIR (Motion) | GPIO | Digital Input |

---

##  Software Requirements

### System Dependencies

```bash
# Required Packages
- build-essential        # GCC 11.4 / G++ 11.4 compiler
- cmake >= 3.18          # Modern CMake with CUDA toolkit support
- git                    # Version control
- python3 >= 3.10        # Python runtime (Ubuntu 22.04 default)
- python3-pip            # Python package manager

# Jetson Acceleration & Media Libraries
- CUDA Toolkit 12.6.68   # GPU computing framework
- TensorRT 10.3.0.30     # High-performance deep learning inference
- cuDNN 9.3.0            # Deep neural network primitives
- libopencv-dev 4.10.0   # OpenCV with CUDA & contrib acceleration
- VPI 3.2.4              # Vision Programming Interface
- libgstreamer1.0-dev    # Multimedia framework (1.20.3+)
- gstreamer1.0-plugins-* # GStreamer plugins (nvarguscamerasrc, nvvidconv)

# Communication Libraries
- libmosquitto-dev      # MQTT client
- libcurl4-openssl-dev  # HTTP client
- libssl-dev            # SSL/TLS
- libwebsocketpp-dev    # WebSocket

# Hardware Libraries
- libasound2-dev        # Audio
- libusb-1.0-0-dev      # USB
- libudev-dev           # udev
- libi2c-dev            # I2C
- libspi-dev            # SPI

# Data Libraries
- libsqlite3-dev        # SQLite
- libyaml-cpp-dev       # YAML parsing
- nlohmann-json3-dev    # JSON handling
- libtinyxml2-dev       # XML parsing
```

### Python Dependencies

```python
# Core (JetPack 6.2.1 / Python 3.10)
opencv-python>=4.10.0         # Built system-wide with CUDA 12.6
numpy>=1.24.0,<2.0.0          # Numerical computing
scipy>=1.11.0                 # Scientific computing

# AI/ML & Jetson Hardware Acceleration
tensorrt==10.3.0.30           # NVIDIA TensorRT 10.x
torch>=2.4.0                  # PyTorch for JetPack 6
torchvision>=0.19.0           # PyTorch Vision for JetPack 6
onnxruntime-gpu>=1.19.0       # ONNX Runtime with CUDA EP
cuda-python>=12.6.0           # NVIDIA CUDA Python Bindings
jetson-stats>=7.2.0           # jtop monitoring tool

# Web/API
fastapi>=0.100.0              # Web Framework
uvicorn>=0.23.0               # ASGI Server
websockets>=11.0              # WebSocket
paho-mqtt>=1.6.0              # MQTT Client
requests>=2.31.0              # HTTP Requests

# Hardware
pyserial>=3.5                 # Serial Communication
smbus2>=0.4.0                 # I2C Communication
spidev>=3.5                   # SPI Communication
RPi.GPIO>=0.7.1               # GPIO Control

# Data
pandas>=2.0.0                 # Data Analysis
sqlalchemy>=2.0.0             # SQL Toolkit
alembic>=1.11.0               # Database Migrations

# Utilities
python-dotenv>=1.0.0          # Environment Variables
loguru>=0.7.0                 # Logging
click>=8.1.0                  # CLI
pyyaml>=6.0.0                 # YAML Parsing
toml>=0.10.0                  # TOML Parsing

# Testing
pytest>=7.4.0                 # Testing Framework
pytest-cov>=4.1.0             # Coverage
pytest-asyncio>=0.21.0        # Async Tests
```

---

##  Installation

### Quick Install

```bash
# Clone repository
git clone https://github.com/vivek97vivu/Argus-EdgeAI.git
cd Argus-EdgeAI

# Run setup script
chmod +x scripts/setup.sh
sudo ./scripts/setup.sh
```

### Manual Installation

#### Step 1: Clone Repository

```bash
git clone https://github.com/vivek97vivu/Argus-EdgeAI.git
cd Argus-EdgeAI
```

#### Step 2: Install System Dependencies

```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential cmake git wget curl \
    python3 python3-pip python3-dev \
    libopencv-dev \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly gstreamer1.0-tools \
    libmosquitto-dev mosquitto mosquitto-clients \
    libcurl4-openssl-dev libssl-dev \
    libsqlite3-dev \
    libasound2-dev \
    libusb-1.0-0-dev libudev-dev \
    libyaml-cpp-dev nlohmann-json3-dev libtinyxml2-dev \
    v4l-utils
```

#### Step 3: Setup Python & Conda Environment

```bash
# Option A: Activate existing conda environment (recommended)
conda activate belt
pip install -r requirements.txt

# Option B: Create fresh conda environment from environment.yml
conda env create -f environment.yml
conda activate belt
```

#### Step 4: Build C++ Application with CUDA Architecture sm_87

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CUDA_ARCHITECTURES=87
make -j$(nproc)
sudo make install
```

#### Step 5: Setup Permissions

```bash
# GPIO permissions
sudo groupadd -f gpio
sudo usermod -a -G gpio $USER
sudo usermod -a -G dialout $USER

# Setup udev rules
sudo cp scripts/99-*.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

#### Step 6: Create Directories

```bash
sudo mkdir -p /etc/edge_ai
sudo mkdir -p /var/edge_ai/data
sudo mkdir -p /var/edge_ai/logs
sudo mkdir -p /var/backups/edge_ai
sudo cp configs/*.yaml /etc/edge_ai/
```

#### Step 7: Setup System Service

```bash
sudo cp scripts/edge_ai.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable edge_ai.service
```

### Docker Installation (JetPack 6.2 / L4T 36.4)

```bash
# Build Docker image
docker build -t argus-edge-ai .

# Run Docker container with NVIDIA runtime
docker run --rm \
    --runtime nvidia \
    --privileged \
    -p 8000:8000 \
    -p 8080:8080 \
    -p 1883:1883 \
    -v /var/edge_ai:/var/edge_ai \
    argus-edge-ai
```

---

##  Configuration

### Main Configuration (`/etc/edge_ai/config.yaml`)

```yaml
system:
  name: "NVIDIA Jetson AGX Orin Edge AI System"
  version: "1.0.0"
  log_level: "INFO"
  debug: false

camera:
  type: "csi"
  device: "/dev/video0"
  width: 1920
  height: 1080
  fps: 30
  pipeline: "nvarguscamerasrc"
  exposure: -1
  white_balance: -1

ai:
  face_detection:
    model: "/etc/edge_ai/models/face_detection.engine"
    confidence_threshold: 0.6
    
  face_recognition:
    model: "/etc/edge_ai/models/face_recognition.engine"
    recognition_threshold: 0.7

communication:
  mqtt:
    broker: "localhost"
    port: 1883
    topics:
      attendance: "edge_ai/attendance"
      alerts: "edge_ai/alerts"
  
  websocket:
    port: 8080
    
  rest_api:
    port: 8000

database:
  path: "/var/edge_ai/attendance.db"

storage:
  root_path: "/var/edge_ai/data"
  max_size_gb: 100
  auto_cleanup: true

notifications:
  email:
    enabled: false
  sms:
    enabled: false
```

---

##  Usage

### Start the System

#### As a Service

```bash
sudo systemctl start edge_ai.service
sudo systemctl status edge_ai.service
sudo journalctl -u edge_ai.service -f
```

#### Manually

```bash
./build/edge_ai_app --config /etc/edge_ai/config.yaml
```

#### With Docker

```bash
docker run --rm --runtime nvidia --privileged \
    -p 8000:8000 -p 8080:8080 \
    edge-ai
```

### System Commands

```bash
# Check system status
curl http://localhost:8000/api/health

# Get attendance records
curl http://localhost:8000/api/attendance

# Get employee list
curl http://localhost:8000/api/employees

# Register employee
curl -X POST http://localhost:8000/api/employees \
    -H "Content-Type: application/json" \
    -d '{"id":"EMP001","name":"John Doe"}'

# Record attendance
curl -X POST http://localhost:8000/api/attendance \
    -H "Content-Type: application/json" \
    -d '{"employee_id":"EMP001","action":"check_in"}'
```

### Enroll New Face

```bash
python3 scripts/enroll_face.py --user "John Doe" --id EMP001
```

### Test Camera

```bash
python3 scripts/test_camera.py --device /dev/video0
```

### Run Benchmark

```bash
python3 scripts/benchmark.py
```

---

##  API Reference

### REST API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/api/health` | GET | System health check |
| `/api/attendance` | GET | Get attendance records |
| `/api/attendance` | POST | Record attendance |
| `/api/employees` | GET | List employees |
| `/api/employees` | POST | Add employee |
| `/api/employees/{id}` | PUT | Update employee |
| `/api/employees/{id}` | DELETE | Delete employee |
| `/api/visitors` | GET | List visitors |
| `/api/visitors` | POST | Register visitor |
| `/api/visitors/{id}` | PUT | Update visitor |
| `/api/visitors/{id}` | DELETE | Delete visitor |
| `/api/alerts` | GET | Get alerts |
| `/api/alerts` | POST | Create alert |
| `/api/stats` | GET | System statistics |
| `/api/config` | GET | Get configuration |
| `/api/config` | PUT | Update configuration |

### WebSocket Events

| Event | Direction | Description |
|-------|-----------|-------------|
| `attendance` | Server→Client | New attendance record |
| `alert` | Server→Client | New alert notification |
| `status` | Server→Client | System status update |
| `face_detected` | Server→Client | New face detected |
| `employee_arrived` | Server→Client | Employee arrival |
| `employee_departed` | Server→Client | Employee departure |

### MQTT Topics

| Topic | Type | Description |
|-------|------|-------------|
| `edge_ai/attendance` | Publish | Attendance events |
| `edge_ai/alerts` | Publish | Alert notifications |
| `edge_ai/status` | Publish | System status |
| `edge_ai/config` | Subscribe | Configuration updates |
| `edge_ai/command` | Subscribe | System commands |

---

##  Performance Metrics

### Benchmark Results

| Metric | Value |
|--------|-------|
| Face Detection | < 50ms per frame |
| Face Recognition | < 100ms per face |
| Object Detection | 30+ FPS |
| Person Tracking | 25+ FPS |
| Voice Detection | < 200ms |
| GPU Memory Usage | < 4GB |
| CPU Usage | < 60% |
| Power Consumption | 15-60W |

### Throughput

| Operation | Throughput |
|-----------|------------|
| Frames/sec | 30 FPS |
| Faces/sec | 300 faces |
| Attendance records/sec | 100 records |
| API requests/sec | 1000 req/s |
| WebSocket messages/sec | 500 msg/s |
| MQTT messages/sec | 1000 msg/s |

### Latency

| Component | Latency (ms) |
|-----------|--------------|
| Camera Capture | 16-33 ms |
| Pre-processing | 5 ms |
| AI Inference | 50-100 ms |
| Post-processing | 5 ms |
| Database Write | 10 ms |
| MQTT Publish | 5 ms |
| WebSocket Broadcast | 10 ms |

---

##  Troubleshooting

### Common Issues

#### Camera Not Detected

```bash
# Check camera connection
ls -la /dev/video*

# Test camera
gst-launch-1.0 nvarguscamerasrc ! nvoverlaysink

# Check camera permissions
sudo chmod 666 /dev/video*
```

#### GPIO Permission Denied

```bash
# Add user to gpio group
sudo usermod -a -G gpio $USER

# Reload udev rules
sudo udevadm control --reload-rules
sudo udevadm trigger

# Reboot system
sudo reboot
```

#### I2C Device Not Found

```bash
# Scan I2C bus
sudo i2cdetect -y 1

# Check I2C permissions
sudo chmod 666 /dev/i2c-1

# Enable I2C in config
sudo nano /boot/config.txt
# Add: dtparam=i2c_arm=on
```

#### Database Connection Error

```bash
# Check database file
ls -la /var/edge_ai/attendance.db

# Recreate database
sqlite3 /var/edge_ai/attendance.db < scripts/init_database.sql

# Set permissions
sudo chmod 666 /var/edge_ai/attendance.db
```

#### MQTT Connection Failed

```bash
# Start MQTT broker
sudo systemctl start mosquitto

# Check MQTT status
sudo systemctl status mosquitto

# Test MQTT connection
mosquitto_sub -t "#" -v
mosquitto_pub -t "test" -m "hello"
```

### Logs

```bash
# System logs
tail -f /var/log/edge_ai/system.log

# Journal logs
journalctl -u edge_ai.service -f

# Debug logs
tail -f /var/log/edge_ai/debug.log
```

### Recovery

```bash
# Restart system
sudo systemctl restart edge_ai.service

# Reset configuration
sudo cp /etc/edge_ai/config.yaml.default /etc/edge_ai/config.yaml

# Clear cache
sudo rm -rf /tmp/edge_ai/*

# Reset database
sudo sqlite3 /var/edge_ai/attendance.db "DELETE FROM attendance;"
```

---

##  Development

### Building from Source

```bash
# Clean build
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
sudo make install
```

### Running Tests

```bash
# Unit tests
python3 -m pytest tests/

# Integration tests
python3 tests/integration/test_full_pipeline.py

# Performance tests
python3 tests/performance/test_benchmark.py
```

### Code Style

```bash
# Format C++ code
clang-format -i **/*.cpp **/*.h

# Format Python code
black **/*.py
```

### Adding New Features

1. Create feature branch
2. Implement feature with tests
3. Update documentation
4. Submit pull request

### Debugging

```bash
# GDB debugging
gdb ./build/edge_ai_app

# Valgrind memory check
valgrind --leak-check=full ./build/edge_ai_app

# Performance profiling
perf record ./build/edge_ai_app
perf report
```

---

##  Documentation

- **API Reference**: [docs/api.md](docs/api.md)
- **Hardware Guide**: [docs/hardware.md](docs/hardware.md)
- **Development Guide**: [docs/development.md](docs/development.md)
- **Performance Tuning**: [docs/performance.md](docs/performance.md)
- **Security Guide**: [docs/security.md](docs/security.md)
- **Troubleshooting**: [docs/troubleshooting.md](docs/troubleshooting.md)

---

##  Contributing

We welcome contributions! Please follow these steps:

1. **Fork** the repository
2. **Create** a feature branch
3. **Implement** your feature
4. **Test** thoroughly
5. **Document** changes
6. **Submit** a pull request

### Contribution Guidelines

- Follow coding standards
- Write unit tests
- Update documentation
- Keep commits clean
- Use descriptive commit messages

---

##  Roadmap

### Version 1.0.0 (Current)
-  Face Detection & Recognition
-  Voice Authentication
-  Human Detection
-  Person Tracking
-  Attendance Management
-  Visitor Management
-  Surveillance
-  Hardware Drivers (GPIO, SPI, UART, I2C)
-  Communication (MQTT, WebSocket, REST)
-  Data Management (SQLite, File System)
-  Dashboard (Web UI)
-  Mobile App (React Native)

### Version 1.1.0 (Planned)
-  Cloud Integration
-  Multi-camera Support
-  Advanced Analytics
-  ML Model Auto-update
-  Edge-to-Cloud Sync

### Version 2.0.0 (Future)
-  Federated Learning
-  Blockchain Integration
-  5G Connectivity
-  Advanced AI Models
-  Autonomous Decision Making

---

##  System Statistics

### Architecture Overview

| Component | Technology |
|-----------|------------|
| **AI Framework** | TensorRT, PyTorch, ONNX |
| **Computer Vision** | OpenCV, GStreamer |
| **Communication** | MQTT, WebSocket, REST |
| **Database** | SQLite, SQLAlchemy |
| **UI Framework** | React, React Native |
| **Build System** | CMake, Make |
| **Container** | Docker, NVIDIA Container Toolkit |

### Code Statistics

```
─────────────────────────────────────────────────────────────
Language    │ Files │ Lines │ Comments │ Coverage
────────────┼───────┼───────┼──────────┼──────────
C++         │  156  │ 45,000│  8,000   │   85%
Python      │   89  │ 25,000│  4,500   │   90%
JavaScript  │   45  │ 12,000│  2,000   │   80%
YAML/JSON   │   23  │  3,500│    500   │    -
Shell       │   12  │  2,500│    300   │    -
─────────────────────────────────────────────────────────────
Total       │  325  │ 88,000│ 15,300   │   85%
─────────────────────────────────────────────────────────────
```

---

##  Security

### Security Features

- **Authentication**: JWT-based API authentication
- **Encryption**: AES-256 for data at rest
- **TLS**: TLS 1.3 for network communication
- **Access Control**: Role-based access control (RBAC)
- **Audit Logging**: Complete audit trail
- **Secure Storage**: Encrypted credentials storage

### Security Best Practices

1. Change default passwords
2. Use HTTPS in production
3. Enable firewall
4. Regular security updates
5. Monitor logs for anomalies
6. Implement rate limiting

---

##  Tips & Tricks

### Performance Optimization

1. **Enable GPU Acceleration**: Use TensorRT for inference
2. **Reduce Resolution**: Lower resolution for higher FPS
3. **Batch Processing**: Process multiple frames together
4. **Use NVMe Storage**: Faster read/write speeds
5. **Enable DMA**: Reduce CPU overhead
6. **Optimize Thread Usage**: Use thread pools

### Energy Efficiency

1. **Use Lower Power Mode**: 15W for battery operation
2. **Enable Power Management**: Auto-suspend when idle
3. **Reduce AI Model Size**: Use quantized models
4. **Batch Processing**: Process in bursts

---

##  Quick Reference

### Important Commands

```bash
# Start system
sudo systemctl start edge_ai.service

# Stop system
sudo systemctl stop edge_ai.service

# View logs
sudo journalctl -u edge_ai.service -f

# Update configuration
sudo nano /etc/edge_ai/config.yaml
sudo systemctl restart edge_ai.service

# Backup database
sudo cp /var/edge_ai/attendance.db /var/backups/edge_ai/

# Reset system
sudo systemctl stop edge_ai.service
sudo rm -rf /var/edge_ai/data/*
sudo sqlite3 /var/edge_ai/attendance.db < scripts/init_database.sql
sudo systemctl start edge_ai.service
```

### Useful URLs

| Service | URL |
|---------|-----|
| Dashboard | http://localhost:8000/dashboard |
| API Docs | http://localhost:8000/docs |
| Health Check | http://localhost:8000/api/health |
| WebSocket | ws://localhost:8080 |
| MQTT Broker | localhost:1883 |

---

##  Changelog

### v1.0.0 (2026-06-23)
- Initial release
- Complete AI pipeline
- All hardware drivers implemented
- Full API support
- Web dashboard
- Mobile app integration

### v0.9.0 (2026-06-15)
- Beta release
- Core features implemented
- Testing framework
- Documentation

### v0.5.0 (2026-06-01)
- Alpha release
- Basic AI features
- Initial hardware support

---

##  Acknowledgements

- **NVIDIA**: For Jetson AGX Orin and JetPack
- **OpenCV Community**: For computer vision libraries
- **TensorRT Team**: For AI inference optimization
- **Open Source Contributors**: For various libraries used

---

##  Tags

`edge-ai` `jetson-agx-orin` `face-recognition` `computer-vision` `ai-inference` `tensorrt` `gpu-accelerated` `surveillance` `attendance-system` `iot` `mqtt` `websocket` `rest-api` `c++` `python`

---

**Built with ❤️ for the NVIDIA Jetson AGX Orin**
