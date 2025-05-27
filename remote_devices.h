// remote_device.h
#ifndef REMOTE_DEVICE_H
#define REMOTE_DEVICE_H

typedef struct {
    char remote_device_name[25];
    char mac_address[18];
} RemoteDeviceInfo;

// Extern declaration for global access
extern RemoteDeviceInfo remote_dev_i;

#endif
