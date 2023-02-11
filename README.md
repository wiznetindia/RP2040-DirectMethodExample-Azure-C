<!-- omit in toc -->
# Adding Direct method function in prov_dev_client_ll_sample application example(prov_dev_client_ll_sample.c)

Please refer to [gettingstarted][link-getting_started] for examples initialization.

<!--
Link
-->

[link-getting_started]: https://github.com/wiznetindia/RP2040-DirectMethodExample-Azure/blob/main/gettingstarted.txt

## What is Direct method?

IoT Hub gives you the ability to invoke direct methods on devices from the cloud. Direct methods represent a request-reply 
interaction with a device similar to an HTTP call in that they succeed or fail immediately (after a user-specified timeout). 
This approach is useful for scenarios where the course of immediate action is different depending on whether the device was 
able to respond.

Please refer to [DeviceMethodCallback Interface](https://learn.microsoft.com/en-us/java/api/com.microsoft.azure.sdk.iot.device.devicetwin.devicemethodcallback?view=azure-java-stable) for more details


- [1. Prepare IoT Hub and Device for this example](#1-prepare-iot-hub-and-device-for-this-example)
  - [1.1. Developer PC - Generate Device self-signed certificates](#11-developer-pc---generate-device-self-signed-certificates)
  - [1.2. Azure portal](#12-azure-portal)
    - [1.2.1. Create Azure Device Provisioning service](#121-create-azure-device-provisioning-service)
    - [1.2.2. Link to Azure IoT Hub & DPS](#122-link-to-azure-iot-hub--dps)
    - [1.2.3. Create a device enrollment](#123-create-a-device-enrollment)
  - [1.3. Developer PC - SDK setting](#13-developer-pc---sdk-setting)
  - [1.4. Developer PC - Build](#14-developer-pc---build)
  - [1.5. Developer PC - Serial terminal open](#15-developer-pc---serial-terminal-open)
- [2. Run the example code](#2-run-the-example-code)
  - [2.1. Copy main.uf2 file into your Pico board](#21-copy-mainuf2-file-into-your-pico-board)
  - [2.2. Azure portal Direct method (preview) log](#22-azure-portal-direct-method-preview-log)
  - [2.3. Serial terminal log](#23-serial-terminal-log)
  - [2.4. Getting C2D message](#24-getting-c2d-message)
  - [2.5. Azure IoT portal Direct method (preview) log](#25-azure-iot-portal-direct-method-preview-log)
---



# 1. Prepare IoT Hub and Device for this example



## 1.1. Developer PC - Generate Device self-signed certificates

**[MUST]** Please follow up [tutorial-x509-self-sign](https://docs.microsoft.com/en-us/azure/iot-hub/tutorial-x509-self-sign)

At last stage, you need to run the following command for making .pem file:
> openssl x509 -in device1.crt -out _device1.pem -outform PEM

For your reference, prepare example log as below:
Notice! device ID = **"8WB0NRK1KQ"**

```bash
MINGW64 ~/certi
$ openssl genpkey -out prov_device1.key -algorithm RSA -pkeyopt rsa_keygen_bits:2048
............+++++
...................................+++++

MINGW64 ~/certi
$ openssl req -new -key prov_device1.key -out prov_device1.csr
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:.
State or Province Name (full name) [Some-State]:.
Locality Name (eg, city) []:.
Organization Name (eg, company) [Internet Widgits Pty Ltd]:.
Organizational Unit Name (eg, section) []:.
Common Name (e.g. server FQDN or YOUR name) []:8WB0NRK1KQ
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:

MINGW64 ~/certi
$ openssl x509 -req -days 365 -in device1.csr -signkey device1.key -out device1.crt
Signature ok
subject=CN = 8WB0NRK1KQ
Getting Private key

MINGW64 ~/certi
$ openssl x509 -in device1.crt -out prov_device1.pem -outform PEM

MINGW64 ~/certi
$ ls
device1.crt  device1.key device1.csr  device1.pem

MINGW64 ~/certi
$
```



## 1.2. Azure portal



### 1.2.1. Create Azure Device Provisioning service

**[MUST]** For Device Provisioning service creation, please follow up the
[Quickstart: Set up the IoT Hub Device Provisioning Service with the Azure portal](https://docs.microsoft.com/en-us/azure/iot-dps/quick-setup-auto-provision) document first.

- After creating DPS, get your "ID Scope" value

  ![dps](https://user-images.githubusercontent.com/69140786/218097483-9fd28657-c36d-4148-89c0-9e300c3221c2.png)



### 1.2.2. Link to Azure IoT Hub & DPS

Connect DPS and IoT Hub service

![dps2](https://user-images.githubusercontent.com/69140786/218097683-3a5bc3af-b022-4b56-b7de-0b9b7558dbea.png)



### 1.2.3. Create a device enrollment

Add individual enrollment

![dps3](https://user-images.githubusercontent.com/69140786/218097873-9be26e71-2ea3-47e9-a8b4-c57fdea23cb3.png)

Use "device1.pem" file generated in previous section

![dps4](https://user-images.githubusercontent.com/69140786/218097969-f11a33a2-f531-4d97-b7ea-ee3f6fd3f093.png)

Check "Individual Enrollments" list

![dps5](https://user-images.githubusercontent.com/69140786/218098000-ae6f0c6f-7244-4a66-8854-210ae75882f5.png)

For more details,

- Please refer [How to manage device enrollments with Azure portal](https://docs.microsoft.com/en-us/azure/iot-dps/how-to-manage-enrollments)

- Or please read [Quickstart: Provision an X.509 certificate simulated device](https://docs.microsoft.com/en-us/azure/iot-dps/quick-create-simulated-device-x509?tabs=windows&pivots=programming-language-ansi-c) document as well.



## 1.3. Developer PC - SDK setting

- Get the key value from files _(device1.crt, device1.key)_ as below:

![dps6](https://user-images.githubusercontent.com/69140786/218098166-fdf404c0-8897-473c-b005-45e669faa9fc.PNG)

- Edit [`RP2040-DirectMethodExample-Azure/exmaples/sample_certs.c`](examples/sample_certs.c) with generated certificates as upper. For common name, Use "RP2040-DirectMethodExample-Azure" used in key generation.
  - `pico_az_CERTIFICATE` and `pico_az_PRIVATE_KEY` use key value from files _(device1.crt, device1.key)_
  - `pico_az_id_scope` use "ID Scope" string from [1.2.1. Create Azure Device Provisioning service](#121-create-azure-device-provisioning-service)
  - `pico_az_COMMON_NAME` use "device ID" from [1.1. Developer PC - Generate Device self-signed certificates](#11-developer-pc---generate-device-self-signed-certificates)

```C
const char pico_az_id_scope[] = "0nexxxxxxxx";

const char pico_az_COMMON_NAME[] = "8WB0NRK1KQ";

const char pico_az_CERTIFICATE[] =
"-----BEGIN CERTIFICATE-----""\n"
"MIIDrTCCApUCFG9+kOlk2I815L5XAGBX7DXNxGE+MA0GCSqGSIb3DQEBCwUAMIGS""\n"
"MQswCQYDVQQGEwJLUjEUMBIGA1UECAwLR3llb25nZ2ktZG8xFDASBgNVBAcMC1Nl""\n"
...
"AwyXH6BPlQhBylsB4J5psW9ptDNKDPwF5q9cC+UiER8nSoqo0nQkB/MFSqwpZ/t0""\n"
"F7Yi3Fh/3zOiiT3qJGbFq5hU6b+AWLFjEBf4STahhOm4""\n"
"-----END CERTIFICATE-----";

const char pico_az_PRIVATE_KEY[] =
"-----BEGIN PRIVATE KEY-----""\n"
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC/+cTz9dwyx0oQ""\n"
"RZq4eefN3GV6CSAUjAEVabjwO8Oa92rxAVtNhuPuFSOQMsixfW0EwPMrtBqWJx0k""\n"
...
"DHuwsI6yH1KXJ8AhQ9N99JHM00oCxVb1whKQghatpe/+4daatxD6YEoGqypxUxGv""\n"
"NCv2+ABkemj5BI2RGP5cHHk=""\n"
"-----END PRIVATE KEY-----";
```



In the following [`RP2040-DirectMethodExample-Azure/exmaples/main.c`](examples/main.c) source file, find the line similar to this and replace it as you want:

```C
(...)

// The application you wish to use should be uncommented
//
//#define APP_TELEMETRY
//#define APP_C2D
//#define APP_CLI_X509
#define APP_PROV_X509

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



## 1.4. Developer PC - Build

Run `make` command

```
(PWD) RP2040-DirectMethodExample-Azure/build/examples
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



## 1.5. Developer PC - Serial terminal open

Open "COM" port to see debug code

![image](https://user-images.githubusercontent.com/6334864/137317966-b9f63168-e011-4a0a-a3b1-345d1e847304.png)



# 2. Run the example code



## 2.1. Copy main.uf2 file into your Pico board

```
(PWD) RP2040-DirectMethodExample-Azure/build/examples
$ cp main.uf2 /f/
```



## 2.2. Azure portal Direct method (preview) log

Click "Device" under your delected IoTHub 

- You can find provison device from device list as belew:
![dps10](https://user-images.githubusercontent.com/69140786/218248814-606eecff-b095-44ab-be28-4d27796102b6.png)


- Edit [`RP2040-DirectMethodExample-Azure/exmaples/prov_dev_client_ll_sample.c`](examples/prov_dev_client_ll_sample.c)
  Assign your direct method name in firmware 
![dps11](https://user-images.githubusercontent.com/69140786/218249340-84465ffe-ab53-402f-952f-a7fb41d78153.png)

- Go to "Direct method" menu, click "Invoke method", and wait for incoming messages

![dps8](https://user-images.githubusercontent.com/69140786/218249115-29d0bd83-2eef-42f6-8e0c-52b1d32cfb26.png)

![dps9](https://user-images.githubusercontent.com/69140786/218249154-81f6897d-e78f-47fd-afb8-b64453d08641.png)



## 2.3. Serial terminal log

Connect to Azure DPS (Device Provisioning Server)

![dps12](https://user-images.githubusercontent.com/69140786/218249668-0ea36e90-603d-4fa9-8d3b-3d2fc64e000f.png)


Provision work is done

![dps13](https://user-images.githubusercontent.com/69140786/218249809-c9db13bc-bb14-40de-ae5d-49790b4ab589.png)


## 2.4. Getting C2D message

Then, you can see the received C2D message through your "Serial Terminal" window as below:
GPIO pin state change

![dps14](https://user-images.githubusercontent.com/69140786/218251049-4cf56a78-f14a-430d-b3e7-a85a45d0b04c.png)



## 2.5. Azure IoT portal Direct method (preview) log

![dps15](https://user-images.githubusercontent.com/69140786/218251137-d0286351-8377-444b-ade0-57d6db55ee78.png)

At this point, only default led pin state from W5100S-EVB-PICO is altered using Direct method