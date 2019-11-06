#version 430 core

#define SPACEONE 0
#define SPACETWO 1 
#define SPHERE 2
#define MENU 3
#define SPACECRAFT 4
#define TRACK 5
#define UFO 6
#define BOOSTER 7


in vec4 fAndBColsExport;
in vec2 texCoordsExport;

uniform sampler2D spaceOneTex;
uniform sampler2D spaceTwoTex;
uniform sampler2D spaceThreeTex;
uniform sampler2D sphereTex;
uniform sampler2D menuTex;
uniform sampler2D spaceCraftTex;
uniform sampler2D trackTex;
uniform sampler2D ufoTex;
uniform sampler2D boosterTex;


uniform uint object;
uniform float alpha;

out vec4 colorsOut;

vec4 spaceOneTexColor, spaceTwoTexColor, spaceThreeTexColor, menuTexColor, spaceCraftTexColor, trackTexColor, sphereTexColor, ufoTexColor;
void main(void)
{  
   spaceOneTexColor = texture(spaceOneTex, texCoordsExport);
   spaceTwoTexColor = texture(spaceTwoTex, texCoordsExport);
   spaceThreeTexColor = texture(spaceThreeTex, texCoordsExport);
   menuTexColor = texture(menuTex, texCoordsExport);
   spaceCraftTexColor = texture(spaceCraftTex, texCoordsExport);
   trackTexColor = texture(trackTex, texCoordsExport);
   ufoTexColor = texture(ufoTex, texCoordsExport);
   sphereTexColor = texture(sphereTex, texCoordsExport);
 

   if (object == SPACEONE) colorsOut = spaceOneTexColor * fAndBColsExport;
   if (object == SPACETWO) colorsOut = mix(spaceThreeTexColor * fAndBColsExport, spaceTwoTexColor, alpha); 
   if (object == SPHERE) colorsOut = sphereTexColor;
   if (object == MENU) colorsOut = menuTexColor;
   if (object == SPACECRAFT) colorsOut = spaceCraftTexColor;
   if (object == TRACK) colorsOut = trackTexColor;
   if (object == UFO) colorsOut = ufoTexColor;
   if (object == BOOSTER) colorsOut = spaceOneTexColor;
   
}
