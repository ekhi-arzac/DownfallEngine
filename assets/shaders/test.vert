#version 450

// vertex array for the triangle
vec3 vertices[3] = vec3[](
    vec3(-0.5, -0.5, 0.0),
    vec3(0.5, -0.5, 0.0),
    vec3(0.0, 0.5, 0.0)
);

void main()
{
    // set the vertex position
    gl_Position = vec4(vertices[gl_VertexIndex], 1.0);
    // set the color
    gl_FrontColor = vec4(1.0, 0.0, 0.0, 1.0);
}