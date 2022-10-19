#include "assets.h"

xm64player_t xm;
wav64_t wav;

void update_audio(){
    if (audio_can_write()) 
    {    	
        short *buf = audio_write_begin();
        mixer_poll(buf, audio_get_buffer_length());
        audio_write_end();
    }
}