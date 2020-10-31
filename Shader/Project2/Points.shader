#version 330 core
layout (location = 0) in vec3 Point;
void main()
{
	gl_Position = vec4(Point.x, Point.y, Point.z, 1.0);
}