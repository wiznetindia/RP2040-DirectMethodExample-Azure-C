/**
 * Copyright (c) 2021 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "azure_samples.h"

/* Paste in the your IoT Hub connection string  */
const char pico_az_connectionString[] = "HostName=wiznet-iot-dps.azure-devices-provisioning.net;SharedAccessKeyName=provisioningserviceowner;SharedAccessKey=mR3cikkiS5PJh1L7zOE8cuucsDKz6JXl2osnm5E0wI8=";

const char pico_az_x509connectionString[] = "[device connection string]";

const char pico_az_x509certificate[] =
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_x509privatekey[] =
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";

const char pico_az_id_scope[] = "0ne005A888E";

const char pico_az_COMMON_NAME[] = "8WB0NRK1KQ";

const char pico_az_CERTIFICATE[] = 
"-----BEGIN CERTIFICATE-----""\n"
"MIICsTCCAZkCFGAJC7v9HdOuB8k6T0ziMFseqnWcMA0GCSqGSIb3DQEBCwUAMBUx""\n"
"EzARBgNVBAMMCjhXQjBOUksxS1EwHhcNMjMwMTE5MDYyMjIzWhcNMjQwMTE5MDYy""\n"
"MjIzWjAVMRMwEQYDVQQDDAo4V0IwTlJLMUtRMIIBIjANBgkqhkiG9w0BAQEFAAOC""\n"
"AQ8AMIIBCgKCAQEAyte9LzdbFCKP5Hu5gRkcB5qAXd4S7u8QIAAHavTPtnjxjeSO""\n"
"dce6DHVD5IhiXnSN5ApKYL1mP30dsh7vMdMI9sgAGLNL/CGKOkW4r6mn1aXLntz4""\n"
"iGFAJ6e6QUGAS+ybgYN6/GlIDfSHCQvJGbrlc9Q6YsZTRcMz9dswjHfamLfmbVcl""\n"
"QNhTSmfoKSWGYzeRJLd/t1/5zEMgonJHC08k18kJ4N7p8yKcB1aP3opdNMkPh1A8""\n"
"aoGvzGQyK22EyBs6PHKLJWdAyo2ajfrqI/AzbPo8PXWA0vfCVTASvnDstcMwvNtt""\n"
"pdVtyco2132MT1qfaJoWiAX+1OdeJstPeCW9twIDAQABMA0GCSqGSIb3DQEBCwUA""\n"
"A4IBAQBddeCG+WPJu0Z/7XNNmSb3IpQT66p0vy7cWDSyzk2u3MTqyvp05eb39zJq""\n"
"ZdLrnOtfs4XPk3MuFGo3u4jbbRhKSXSVs/XovoAGvVg9Me4bC3v0aahXKI0z16DS""\n"
"H0vHtnvkheSb43SqI6VQIS4NpqXWVauu7zSWWOfzMpGnBqmeXpmuZnX3+4mlsuFd""\n"
"YB6P7/VDm/DwNBi0zIY3VTgjPWgxrQgkTZ+aZ3ypP68UlGgrx6EbGjloC0agA5FU""\n"
"YrKnXjcwWITDIfvRwtFWWFJedhNC80agIFCM0tUL06c388IFJ6b1el7ArLB9g05X""\n"
"bWJBL1d0W6ev2g378dIr+OGP9OMc""\n"
"-----END CERTIFICATE-----";

const char pico_az_PRIVATE_KEY[] = 
"-----BEGIN PRIVATE KEY-----""\n"
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDK170vN1sUIo/k""\n"
"e7mBGRwHmoBd3hLu7xAgAAdq9M+2ePGN5I51x7oMdUPkiGJedI3kCkpgvWY/fR2y""\n"
"Hu8x0wj2yAAYs0v8IYo6RbivqafVpcue3PiIYUAnp7pBQYBL7JuBg3r8aUgN9IcJ""\n"
"C8kZuuVz1DpixlNFwzP12zCMd9qYt+ZtVyVA2FNKZ+gpJYZjN5Ekt3+3X/nMQyCi""\n"
"ckcLTyTXyQng3unzIpwHVo/eil00yQ+HUDxqga/MZDIrbYTIGzo8coslZ0DKjZqN""\n"
"+uoj8DNs+jw9dYDS98JVMBK+cOy1wzC8222l1W3JyjbXfYxPWp9omhaIBf7U514m""\n"
"y094Jb23AgMBAAECggEACpQ5366JZ4Ft88KoKB2BIrxiGYMthZyeQKz/tgpSkve3""\n"
"0WisLWRfRasQAWlDiB2YEN6ghm8aWBFUbSfD3dtdylEgACnJurqdFPDx8udsQ25E""\n"
"MmLf62z3BZpv0ltyL4OFkLmkvmlXQrMQH96nfFoNAX9+FAy35xmJKjdmTs0pb3GA""\n"
"GYNfn17tUwsrfJzovC+6sTu2Djv3HsH+NKPcVdN7/RFydTAMiQMSyfD44VgpwSYr""\n"
"c5Jzlihuy5Sxbkr73y1I1iwab75vz63SXccw98QX1dmkAWS5ylfWvBDs/1csR/Zo""\n"
"GVeC3CGTImYuEjDWtfvMowrPutFwHVJLb4Il22e9kQKBgQDxrwLkCvHX/D+C2jOO""\n"
"1Ld8zTOGGNntIkytiDzSKgOtoAwrNgOv+Q52mW3YLHtlhHct9Ad1ZdrKs+m/ldJ2""\n"
"knts5EtgxxhNZ9rURvdXcWMONrFNu/TUO7ETmDDD8MhRKDIPKHo6xtZWBy58xQCD""\n"
"ujgp5uEQgIlk2219xbLzAOcOKwKBgQDW27p603GW3qxTWWa00NMmZR3eNfcLHJ9Y""\n"
"sOXXnlmPcXOBcn7S1ptGwfZJkoX48Em/SqQQ0lG9ZhxM6XW+gaIypYbWy0s9OdTs""\n"
"p6o9PhS9aIFqTx3e15DmeB3vqdhFVfD+2JDRh+7R9SQBWNLyzPhR8TYxzBSS4JRV""\n"
"YlMg4XrUpQKBgQC06c7+KXsztK1OJExn5K+dinXBMaUgL4a6d7sfjzfFpoK1be+A""\n"
"sKy09tEU+uc77NbR3VQf+yi2h8q4EUzEWY5uys3qGd8FQnK6aI0KNeRyZVp/1+zD""\n"
"WhOJmWkXo4wvxCkE08X7bZBQQXv5BfcGpEUaiKt9ENrIVsE1XuI/qTNMlQKBgDnx""\n"
"Y+b/4uA3CO4pbANTVb5DAr0MfKUogOigPDvb3ndKt0WvpPgjHBkG8e6Bb1PlKV5H""\n"
"ONu4fIbBZNxxEWng9+cEsMp4ZMAMOpnf1Y9SkLFL36rVz05rgA5HUntxqHt6Y9W2""\n"
"fcekCwngPGeIlssX79fZXy4qxVme6yHjtFtns4JpAoGAdGn9pm8PEf3NgeBN+A8B""\n"
"QU7dyYVNsF6ZEKIQLMcXrw9DUW8cVrRZk/Cmkgopxu9VOYdJGYTOnmQEEEVObKrB""\n"
"dpc/5/NQmZG+AFQTynJfUEZdnSKsPS+/oJ7FMuLwwSZrMiyN/tQhW20jzxFkaHqz""\n"
"HMDKYKAbq/1DfUPwo9VBo0g=""\n"
"-----END PRIVATE KEY-----";
