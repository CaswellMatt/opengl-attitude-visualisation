# opengl-attitude-visualisation
takes serial data orientation as quaternion and displays with open gl

## Getting Started
this has only been tested on linux, Ubuntu 18.04. 

execute scripts ``` ./build.sh ``` and ``` ./run.sh ```

quaternion data arrives over ```/dev/ttyACM0``` and comes in form ```"<q1> <q2> <q3> <q4>/n"```
