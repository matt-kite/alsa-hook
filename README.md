ALSA Hook
=========

A simple ALSA hook is used to publish MQTT messages when a hooked ALSA PCM is opened or closed.
It works with the ALSA `hooks` plugin.

## Install
```
sudo apt install libasound2-dev
make
sudo make install
```

## Configure
Add the hooked pcm to `/etc/asound.conf` or `~/.asoundrc`.

```
# hook entry
pcm_hook_type.mqtt {
    install "_snd_pcm_hook_mqtt_install"
    lib "alsa_hook_mqtt.so"
}

pcm.hooked {
    type hooks
    slave.pcm "hw:0"

    hooks.0 {
        type "mqtt"
    }
}
```
(optional) Change the MQTT topic and host for your use case. E.g. set the first topic level to your hostname.


## MQTT messages
1.  when a hooked pcm is opened

    + topic: `kitchenpi/alsa/status` 
    + message: playing

2.  when a hooked pcm is closed

    + topic: `kitchenpi/alsa/status` 
    + message: stopped

## To Do

- [] Configurable MQTT topic, host and message

