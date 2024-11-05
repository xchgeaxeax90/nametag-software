import numpy as np
import math
from animation import face_light_phases, timer_freq, write_animation



def animation_circle():
    period = 16
    period_sec = 1.0
    face_lights = np.zeros((period, len(face_light_phases)))
    for i in range(period):
        face_lights[i] = np.sin(face_light_phases + (i/period)*math.pi*2)


    eyes = np.zeros((period, 2))
    lightsticks = np.zeros((period, 2))

    for i in range(period):
        lightsticks[i] = np.sin(i/period * math.pi*2)**5

    for i in range(period):
        eyes[i] = np.sin(i/period*2 * math.pi*2 + math.pi*1.3)**2



    lights = np.concat((lightsticks, eyes, face_lights), axis=1)
    write_animation('animation_circle', lights, period_sec)

def animation_breathe():
    period = 8
    period_sec = 1.0
    lights = np.zeros((period, len(face_light_phases) + 4))

    for i in range(period):
        lights[i] = np.sin(lights[i] + i/period * math.pi)
    write_animation('animation_breathe', lights, period_sec)
    

if __name__ == '__main__':
    animation_circle()
    animation_breathe()
