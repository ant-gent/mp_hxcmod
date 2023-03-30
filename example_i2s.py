from hxcmod import Hxcmod
from machine import I2S
from machine import Pin

with open('cartoon-dreams_n_fantasies.mod', 'rb') as f:
    mod_data = f.read()
    
# 250ms audio buffer
# 1 sec of audio = 44100(sample rate) * 2 (16bit samples) * 2 (stereo)
audio_buffer = bytearray(44100)

hxcmod = Hxcmod()

hxcmod.load(mod_data)

SCK_PIN = 27
WS_PIN = 28
SD_PIN = 26
I2S_ID = 0

audio_out = I2S(
    I2S_ID,
    sck=Pin(SCK_PIN),
    ws=Pin(WS_PIN),
    sd=Pin(SD_PIN),
    mode=I2S.TX,
    bits=16,
    format=I2S.STEREO,
    rate=44100,
    ibuf=len(audio_buffer),
)

while True:
    hxcmod.fillbuffer(audio_buffer)
    audio_out.write(audio_buffer)

