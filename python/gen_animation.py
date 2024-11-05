import numpy as np
import math
#import matplotlib
timer_period = 1/244 # 244Hz

#bot_l, bot_c, bot_r, top_l, top_c, top_r
face_light_phases = np.array([210, 270, 310, 150, 70, 45]) * math.pi/180
period = 16
period_sec = 1.0

face_period = period


face_lights = np.zeros((face_period, len(face_light_phases)))
for i in range(face_period):
    face_lights[i] = np.sin(face_light_phases + (i/face_period)*math.pi*2)


eyes = np.zeros((face_period, 2))
lightsticks = np.zeros((face_period, 2))

for i in range(period):
    lightsticks[i] = np.sin(i/period * math.pi*2)**5

for i in range(period):
    eyes[i] = np.sin(i/period*2 * math.pi*2 + math.pi*1.3)**2



lights = np.concat((lightsticks, eyes, face_lights), axis=1)
lights = np.clip(lights, 0, 1) * 255
print(lights)


with open('animation.inc', 'w') as f:
    f.write('const __flash animation_data_t animation[] = {\n')
    for line in lights:
        line = [f'{int(x):4}' for x in line]
        data = ','.join(line)
        timeout = period_sec / period / timer_period
        f.write(f'{{{{{data}}}, .timeout = {int(timeout)}}},\n')
    f.write('};')
    
