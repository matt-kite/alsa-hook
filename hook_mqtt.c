// alsa hook

#include <alsa/asoundlib.h>
#include <alsa/conf.h>
#include <alsa/pcm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if 0
static int _hook_hw_params(snd_pcm_hook_t *hook)
{
    snd_pcm_t *pcm = snd_pcm_hook_get_pcm(hook);
    fprintf(stderr, "PCM hw params\n");
    if (!pcm) return -1;
    return 0;
}

static int _hook_hw_free(snd_pcm_hook_t *hook)
{
    fprintf(stderr, "PCM hw free\n");
    return 0;
}
#endif

static int _hook_close(snd_pcm_hook_t *hook)
{
    char buf[] = "mosquitto_pub -h noid.local -t kitchenpi/alsa/status -m stopped";
    system(buf);
    return 0;
}

int _snd_pcm_hook_mqtt_install(snd_pcm_t *pcm, snd_config_t *conf)
{
    int err;
    snd_pcm_hook_t *h_close = NULL;
    char buf[] = "mosquitto_pub -h noid.local -t kitchenpi/alsa/status -m playing";
    system(buf);
    
#if 0
    snd_pcm_hook_t *h_hw_params = NULL;
    snd_pcm_hook_t *h_hw_free = NULL;

    err = snd_pcm_hook_add(&h_hw_params, pcm, SND_PCM_HOOK_TYPE_HW_PARAMS,
                           _hook_hw_params, NULL);
    if (err < 0)
        goto error;

    err = snd_pcm_hook_add(&h_hw_free, pcm, SND_PCM_HOOK_TYPE_HW_FREE,
                           _hook_hw_free, NULL);
    if (err < 0)
        goto error;
#endif

    err = snd_pcm_hook_add(&h_close, pcm, SND_PCM_HOOK_TYPE_CLOSE,
                           _hook_close, NULL);
    if (err < 0)
        goto error;

    return 0;

error:
#if 0
    if (h_hw_params)
        snd_pcm_hook_remove(h_hw_params);

    if (h_hw_free)
        snd_pcm_hook_remove(h_hw_free);
#endif

    if (h_close)
        snd_pcm_hook_remove(h_close);

    return err;
}

SND_DLSYM_BUILD_VERSION(_snd_pcm_hook_mqtt_install, SND_PCM_DLSYM_VERSION);
