#version 330 core
layout (location = 0) in vec3 aPos; // in is a keyword for input data

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); //gl_Position is vec4 behind the scenes and is out output data
}
