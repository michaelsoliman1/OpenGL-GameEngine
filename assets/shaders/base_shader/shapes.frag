#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use
uniform vec3 color;
uniform vec3 fillColor;
uniform float time;
uniform bool flicker;
uniform int shapeNumber;
uniform vec2 mousePosition;
uniform vec2 screenSize;

// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;

#define PI 3.1415926535897932384626433832795

void drawCircle(vec2 centerPoint, int radius, vec4 fillColor);
void drawRect(float res_x, float res_y, int color);
bool ptInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2);
void drawTriangle(vec2 p0, vec2 p1, vec2 p2,vec4 fillColor);
void drawRectangle(vec2 topleftPoint, int width, int height, vec4 fillcolor);
void drawSmileyFace(vec4 fillcolor);
void drawPacMan(vec4 fillColor);
void drawG(vec4 fillColor);

// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {

    //R,G,B,A
    frag_color=vec4(color, 1.0);
    vec4 fColor = vec4(fillColor,1.0);
    if(shapeNumber==1)
        drawSmileyFace(fColor);
    else if(shapeNumber==2)
        drawG(fColor);
    else if(shapeNumber==3)
        drawPacMan(fColor);

    if (flicker)
    frag_color.rgb *= 0.5 * (1 + cos(2 * PI * time));

}

void drawRectangle(vec2 topleftPoint, int width, int height, vec4 fillcolor){
    if(gl_FragCoord.x>topleftPoint.x
    && gl_FragCoord.y>topleftPoint.y
    && gl_FragCoord.x < topleftPoint.x+width
    && gl_FragCoord.y < topleftPoint.y+height)
        frag_color = fillcolor;
}

void drawTriangle(vec2 p0, vec2 p1, vec2 p2, vec4 fillColor){
    if(ptInTriangle(gl_FragCoord.xy,p0,p1,p2))
        frag_color = fillColor;
}

bool ptInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2) {
    float dX = p.x-p2.x;
    float dY = p.y-p2.y;
    float dX21 = p2.x-p1.x;
    float dY12 = p1.y-p2.y;
    float D = dY12*(p0.x-p2.x) + dX21*(p0.y-p2.y);
    float s = dY12*dX + dX21*dY;
    float t = (p2.y-p0.y)*dX + (p0.x-p2.x)*dY;
    if (D<0) return s<=0 && t<=0 && s+t>=D;
    return s>=0 && t>=0 && s+t<=D;
}

void drawCircle(vec2 centerPoint, int radius, vec4 fillColor){
    float dist = length(gl_FragCoord.xy - centerPoint);
    if(dist< radius)
        frag_color = fillColor;
}

void drawSmileyFace( vec4 fillColor){
    drawCircle(screenSize.xy/2, 270, fillColor);//face
    drawCircle(vec2(screenSize.x*0.4, screenSize.y*0.6), 30, vec4(color, 1.0));//leftEye
    drawCircle(vec2(screenSize.x*0.6, screenSize.y*0.6), 30, vec4(color, 1.0));//rightEye
    drawCircle(vec2(screenSize.x/2, screenSize.y*0.35), 120, vec4(color, 1.0));//smallSmile
    drawCircle(vec2(screenSize.x/2, screenSize.y*0.4), 120, fillColor);//bigSmile
}

void drawG(vec4 fillColor){
    vec2 pointFromCenter = gl_FragCoord.xy - screenSize.xy/2;
    float dist = length(pointFromCenter);
    if(all(greaterThan(gl_FragCoord.xy , screenSize.xy/2)))
        dist = 0.0;
    if(dist< 270 && dist>200)
        frag_color = fillColor;
    drawRectangle(screenSize.xy/2, 270, 70, fillColor);
}

void drawPacMan(vec4 fillColor) {
    drawCircle(vec2(640,360), 300,fillColor);
    drawCircle(vec2(700,550),50,vec4(color,1.0));
    drawTriangle(vec2(640,360),vec2(1000,100),vec2(1000,600), vec4(color,1.0));
}