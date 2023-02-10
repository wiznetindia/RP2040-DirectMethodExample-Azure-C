<!-- omit in toc -->
# iothub_ll_telemetry_sample application

- [1. Prepare IoT Hub and Device for this example](#1-prepare-iot-hub-and-device-for-this-example)
  - [1.1. Azure portal](#11-azure-portal)
  - [1.2. Developer PC](#12-developer-pc)
    - [1.2.1. SDK setting](#121-sdk-setting)
    - [1.2.2. Build](#122-build)
    - [1.2.3. Azure IoT Explorer (preview) setting](#123-azure-iot-explorer-preview-setting)
    - [1.2.4. Serial terminal open](#124-serial-terminal-open)
- [2. Run the example code](#2-run-the-example-code)
  - [2.1. Copy main.uf2 file into your W5x00-EVB-Pico](#21-copy-mainuf2-file-into-your-w5x00-evb-pico)
  - [2.2. Serial terminal log](#22-serial-terminal-log)
  - [2.3. Azure IoT Explorer (preview) log](#23-azure-iot-explorer-preview-log)



# 1. Prepare IoT Hub and Device for this example



## 1.1. Azure portal

In Azure portal, you need to create a device and get the connection string informations as below:

![image](https://user-images.githubusercontent.com/6334864/137315276-40dd94f6-1abe-49c7-857b-9dcac646f056.png)

- This example uses symmetric key

![image](https://user-images.githubusercontent.com/6334864/137315405-e557691b-c9f7-4c6b-be4e-d30811d2aad2.png)
![image](https://user-images.githubusercontent.com/6334864/137315457-de69349f-76b4-4aee-bc6c-b09e1f39a542.png)
![image](https://user-images.githubusercontent.com/6334864/137315472-918638d8-667d-4ed8-8962-8a2412340285.png)

- You copy the key string,"Primary Connection String" and paste the string into your code as decribed in next section.

![image](https://user-images.githubusercontent.com/6334864/137315489-38c72158-118a-4797-a42e-7e6239348a41.png)



## 1.2. Developer PC



### 1.2.1. SDK setting

In the following [`RP2040-HAT-AZURE-C/exmaples/main.c`](examples/main.c) source file, find the line similar to this and replace it as you want:

```C
(...)

// The application you wish to use should be uncommented
//
#define APP_TELEMETRY
//#define APP_C2D
//#define APP_CLI_X509
//#define APP_PROV_X509

// The application you wish to use DHCP mode should be uncommented
#define _DHCP
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
#ifdef _DHCP
        .dhcp = NETINFO_DHCP // DHCP enable/disable
#else
        // this example uses static IP
        .dhcp = NETINFO_STATIC
#endif
};
```

Edit the [`RP2040-HAT-AZURE-C/exmaples/sample_certs.c`](examples/sample_certs.c) entering the proper connection string and key value from the Azure Portal:

```C
/* Paste in the your iothub connection string  */
const char pico_az_connectionString[] = "[device connection string]";
```



### 1.2.2. Build

Run `make` command

```
(PWD) RP2040-HAT-AZURE-C/build/examples
$ make
[ 12%] Built target AZURE_SDK_FILES
[ 12%] Built target bs2_default
[ 12%] Built target bs2_default_padded_checksummed_asm
[ 12%] Built target W5100S_FILES
[ 13%] Built target ETHERNET_FILES
[ 13%] Built target DHCP_FILES
[ 13%] Built target DNS_FILES
[ 21%] Built target SNTP_FILES
[ 43%] Built target AZURE_SDK_PORT_FILES
[ 43%] Performing build step for 'ELF2UF2Build'
[100%] Built target elf2uf2
[ 43%] No install step for 'ELF2UF2Build'
[ 43%] Completed 'ELF2UF2Build'
[ 44%] Built target ELF2UF2Build
[ 56%] Built target mbedcrypto
[ 58%] Built target mbedx509
[ 59%] Built target mbedtls
[ 66%] Built target TIMER_FILES
[ 73%] Built target SPI_FILES
Consolidate compiler generated dependencies of target main
[ 75%] Building C object examples/CMakeFiles/main.dir/main.c.obj
[ 75%] Linking CXX executable main.elf
[100%] Built target main
```



### 1.2.3. Azure IoT Explorer (preview) setting

To see the message from your IoT Device, you need to make a "Azure IoT Explorer" setting as below:

![image](https://user-images.githubusercontent.com/6334864/137316202-036e9dd1-bac3-4765-993d-cf34b462bed9.png)

- In Azure portal, you can get the "Connection String" as follows:

![image](https://user-images.githubusercontent.com/6334864/137316902-ef7a8b5f-b295-44ce-825f-6ad1a2233482.png)

- Copy & paste the connection string, and click "Save".

![image](https://user-images.githubusercontent.com/6334864/137317080-615fdbda-5e7b-48d2-8cfb-50291b6bb53a.png)

- Find the device and click name

![image](https://user-images.githubusercontent.com/6334864/137317529-653dda9b-d534-41da-aa86-7e68b51a094e.png)

- Go to "Telemetry" menu, and click "Start"

![image](https://user-images.githubusercontent.com/6334864/137317554-c17aabe7-cfd9-44fe-877b-5b5fd2d9ca28.png)

- Wait for incoming message from your IoT device

![image](https://user-images.githubusercontent.com/6334864/137317564-da8a3677-09fc-4490-b713-58f444934324.png)



### 1.2.4. Serial terminal open

- Open "COM" port to see debug code

![image](https://user-images.githubusercontent.com/6334864/137317966-b9f63168-e011-4a0a-a3b1-345d1e847304.png)



# 2. Run the example code



## 2.1. Copy main.uf2 file into your W5x00-EVB-Pico

```
(PWD) RP2040-HAT-AZURE-C/build/examples
$ cp main.uf2 /f/
```



## 2.2. Serial terminal log

- Connect to Azure IoT Hub

![image](https://user-images.githubusercontent.com/6334864/137318915-f46ac81c-8308-4f4f-939d-06cb279fea1f.png)

- Send messages to Azure IoT Hub

![image](https://user-images.githubusercontent.com/6334864/137319072-1c90ca70-9e6b-4af7-834b-a6adec321715.png)



## 2.3. Azure IoT Explorer (preview) log

- Getting device messages from Azure IoT Hub

![image](https://user-images.githubusercontent.com/6334864/137319420-d392a7aa-f117-43bf-945a-d84bf0913c7e.png)
