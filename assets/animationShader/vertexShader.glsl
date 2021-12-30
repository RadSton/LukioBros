#version 330 core

layout(location=0) in vec4 position;

out vec2 txCoords;

uniform vec2 sheetSize; // 1920 - 1920
uniform vec2 sheetPosition; // 3 - 4
uniform int sheetObjectSize; // 128

/** 
 Should output:

 3(sheetPosition.x) * 128(sheetObjectSize) = 384 = output(int - px.x)
 output(int - px.x) / 1920(sheetSize.x) = 0.2(txCoord)


 Same for Y

*/


void main() {
	txCoords = vec2(((sheetPosition.x * sheetObjectSize) /sheetSize.x), ((sheetPosition.y * sheetObjectSize) /sheetSize.y));
	gl_Position = position;
}