#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use
uniform vec3 color;
uniform float time;
uniform bool flicker;
uniform int shapeNumber;
uniform vec2 circMouseSpeed;
// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;

#define PI 3.1415926535897932384626433832795

void drawCircle(vec2 shiftValue, int rad, int color);
void drawRect(float res_x, float res_y, int color);
void drawSmileyFace();
void drawG();

// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {
    // Here we just output a constant color which is red (R=1, G=0, B=0, A=1)
    frag_color = vec4(color, 1.0);

    if (flicker)
    frag_color.rgb *= 0.5 * (1 + cos(2 * PI * time));

    if(shapeNumber==1){
        drawSmileyFace();
    } else if(shapeNumber==2){
        drawG();
    }
}

void drawSmileyFace(){
    //vec2 mouseSpeed = vec2((circMouseSpeed.x - 0.008)*1.75,circMouseSpeed.y);
    //float x = 1;
    drawCircle(vec2(0.5, 0.52), 270, 1);//face
    drawCircle(vec2(0.4, 0.68), 30, 2);//leftEye
    drawCircle(vec2(0.6, 0.68), 30, 2);//rightEye
    drawCircle(vec2(0.5, 0.42), 150, 2);//bigSmile
    drawCircle(vec2(0.5, 0.42), 120, 1);//smallSmile
    drawCircle(vec2(0.5, 0.48), 150, 1);//smallSmile
    //    drawRect(vec2(0.4,0.68), vec2(0.6,0.68), vec2(0.4,0.42), vec2(0.6,0.42), 1);
}

void drawG(){
    drawCircle(vec2(0.5, 0.35), 150, 2);//bigCircle
    drawCircle(vec2(0.5, 0.35), 120, 4);//smallCircle
    drawRect(3850.0, 150.0, 1);
    drawRect(3500.0, 40.0, 0);
    drawRect(4020.0, 250.0, 1);
}

void drawCircle(vec2 shiftvalue, int rad, int selectColor)
{
    vec2 resolution = vec2(1280, 720);
    vec2 norm = gl_FragCoord.xy;
    float dist = length(norm - (resolution*shiftvalue));
    if(dist < rad)
    {
        if(selectColor == 2)
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);// white
        else if(selectColor == 1)
        frag_color = vec4(1.0, 1.0, 0.0,1.0);//yellow
        else
        frag_color = vec4(color,1.0);//background color
    }
}

void drawRect(float res_x, float res_y, int selectColor)
{
    vec2 resolution = vec2( res_x, res_y );
    //vec2 center = resolution / 2.0;
    vec2 position = ( gl_FragCoord.xy - resolution.xy*0.2 )/resolution.y;

    if ( ( abs(position.x) < 0.5 ) && ( abs(position.y) > 0.5 ) )
    {
        if (selectColor == 1)
        frag_color = vec4(color, 1.0);
        else if (selectColor == 0)
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);//white
        else
        frag_color = vec4(color,1.0);//background color
    }
}
