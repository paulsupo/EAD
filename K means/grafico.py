

from abc import ABC
import pandas as pd
datos = pd.read_csv('output.csv', header=0)

from turtle import *
print(datos)
hideturtle()
setup(600, 600, 0, 0)
screensize(500, 500)
colormode(255)
pencolor("black")
goto(600,0)
goto(0,0)
goto(-600,0)

goto(0,0)
pencolor("black")
goto(0,600)
goto(0,0)
goto(0,-600)
goto(0,0)

AB = float(-25)
CD = float(-24)

penup()
goto(AB,CD)
dot(10, 255, 0, 0)
goto(0,0)

EF = float(-14)
GH = float(-14)

penup()
goto(EF,GH)
dot(10, 0, 255, 0)
goto(0,0)

IJ = float(-5)
kl = float(-28)

penup()
goto(IJ,kl)
dot(10, 0, 0, 255)
goto(0,0)

for i in range(0,100000):
    A=float(datos['x'][i])
    B=float(datos['y'][i])
    C=float(datos['c'][i])

    if C==0:
        penup()
        goto(A,B)
        dot(5, 255, 0, 0)
        goto(0,0)

    if C==1:
        penup()
        goto(A,B)
        dot(5, 0, 255, 0)
        goto(0,0)

    if C==2:
        penup()
        goto(A,B)
        dot(5, 0, 0, 255)
        goto(0,0)