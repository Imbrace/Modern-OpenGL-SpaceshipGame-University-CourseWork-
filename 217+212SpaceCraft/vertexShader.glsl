#version 430 core

#define SPACEONE 0
#define SPACETWO 1
#define SPHERE 2
#define MENU 3
#define SPACECRAFT 4
#define TRACK 5
#define UFO 6



layout(location=0) in vec4 spaceOneCoords;
layout(location=1) in vec3 spaceOneTexCoords;
layout(location=2) in vec2 spaceTwoNormal;
layout(location=3) in vec4 spaceTwoCoords;
layout(location=4) in vec2 spaceTwoTexCoords;
layout(location=5) in vec4 sphereCoords;
layout(location=6) in vec3 sphereNormals;
layout(location=7) in vec4 menuCoords;
layout(location=8) in vec2 menuTexCoords;
layout(location=9) in vec4 spaceCraftCoords;
layout(location=10) in vec2 spaceCraftTexCoords;
layout(location=11) in vec4 trackCoords;
layout(location=12) in vec2 trackTexCoords;
layout(location=13) in vec2 sphereTexCoords;
layout(location=14) in vec4 ufoCoords;
layout(location=15) in vec2 ufoTexCoords;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat3 normalMat;
uniform uint object;

out vec4 fAndBColsExport;
out vec2 texCoordsExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};
uniform Light light0;

uniform vec4 globAmb;
  
struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};
uniform Material matFandB;
uniform Material sphereFandB;

vec3 normal, lightDirection, eyeDirection, halfway;
vec4 fAndBEmit, fAndBGlobAmb, fAndBAmb, fAndBDif, fAndBSpec;
vec4 coords;

void main(void)
{   
/*
   if (object == SPACEONE)
   {
      coords = spaceOneCoords;
      normal = spaceOneNormal;
      texCoordsExport = spaceOneTexCoords;
	 
      normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = matFandB.emitCols;
      fAndBGlobAmb = globAmb * matFandB.ambRefl;
      fAndBAmb = light0.ambCols * matFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * matFandB.difRefl);    
      fAndBSpec = pow(max(dot(normal, halfway), 0.0f), matFandB.shininess) * (light0.specCols * matFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(fAndBEmit + fAndBGlobAmb + fAndBAmb + fAndBDif + fAndBSpec, vec4(1.0))), 1.0);  
	  }
	  */
   if (object == SPACETWO)
   {
      coords = spaceTwoCoords;
      texCoordsExport = spaceTwoTexCoords;
	  normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = matFandB.emitCols;
      fAndBGlobAmb = globAmb * matFandB.ambRefl;
      fAndBAmb = light0.ambCols * matFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * matFandB.difRefl);    
      fAndBSpec = pow(max(dot(normal, halfway), 0.0f), matFandB.shininess) * (light0.specCols * matFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(fAndBEmit + fAndBGlobAmb + fAndBAmb + fAndBDif + fAndBSpec, vec4(1.0))), 1.0);  
   }
   
   if(object == SPHERE)
   {
	   coords = sphereCoords;
	   texCoordsExport = sphereTexCoords;
	   normal = sphereNormals;
	  
      normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = sphereFandB.emitCols;
      fAndBGlobAmb = globAmb * sphereFandB.ambRefl;
      fAndBAmb = light0.ambCols * sphereFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl);    
      //fAndBSpec = pow(max(dot(normal, halfway), 0.0f), sphereFandB.shininess) * (light0.specCols * sphereFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(/*fAndBEmit + */fAndBGlobAmb + fAndBAmb + fAndBDif/* + fAndBSpec*/, vec4(1.0))), 1.0);  
   }
	
	if (object == SPACECRAFT)
	{
      coords = spaceCraftCoords;
	  texCoordsExport = spaceCraftTexCoords;
	  normal = vec3(0,1,0);
	  
      normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = sphereFandB.emitCols;
      fAndBGlobAmb = globAmb * sphereFandB.ambRefl;
      fAndBAmb = light0.ambCols * sphereFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl);    
      //fAndBSpec = pow(max(dot(normal, halfway), 0.0f), sphereFandB.shininess) * (light0.specCols * sphereFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(/*fAndBEmit + */fAndBGlobAmb + fAndBAmb + fAndBDif/* + fAndBSpec*/, vec4(1.0))), 1.0);  
     }
	  
	 if (object == TRACK)
	 {
      coords = trackCoords;
	  texCoordsExport = trackTexCoords;
	//  normal = vec3(0,1,0);
	  
      normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = sphereFandB.emitCols;
      fAndBGlobAmb = globAmb * sphereFandB.ambRefl;
      fAndBAmb = light0.ambCols * sphereFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl);    
      //fAndBSpec = pow(max(dot(normal, halfway), 0.0f), sphereFandB.shininess) * (light0.specCols * sphereFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(/*fAndBEmit + */fAndBGlobAmb + fAndBAmb + fAndBDif/* + fAndBSpec*/, vec4(1.0))), 1.0);  
     }

	  if (object == MENU)
     {
      coords = menuCoords;
	   texCoordsExport = menuTexCoords;
	   normal = vec3(0,1,0);
	   normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = sphereFandB.emitCols;
      fAndBGlobAmb = globAmb * sphereFandB.ambRefl;
      fAndBAmb = light0.ambCols * sphereFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl);    
      //fAndBSpec = pow(max(dot(normal, halfway), 0.0f), sphereFandB.shininess) * (light0.specCols * sphereFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(/*fAndBEmit + */fAndBGlobAmb + fAndBAmb + fAndBDif/* + fAndBSpec*/, vec4(1.0))), 1.0);  
	 }

	 if (object == UFO)
	  {
      coords = ufoCoords;
	  texCoordsExport = ufoTexCoords;
	  //normal = vec3(0,1,0);
	  
      normal = normalize(normalMat * normal);
      lightDirection = normalize(vec3(light0.coords));
      eyeDirection = vec3(0.0, 0.0, 1.0);
      //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);
   
      fAndBEmit = sphereFandB.emitCols;
      fAndBGlobAmb = globAmb * sphereFandB.ambRefl;
      fAndBAmb = light0.ambCols * sphereFandB.ambRefl;
      fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl);    
      //fAndBSpec = pow(max(dot(normal, halfway), 0.0f), sphereFandB.shininess) * (light0.specCols * sphereFandB.specRefl);
      fAndBColsExport =  vec4(vec3(min(/*fAndBEmit + */fAndBGlobAmb + fAndBAmb + fAndBDif/* + fAndBSpec*/, vec4(1.0))), 1.0);  
      }

	 

   gl_Position = projMat * viewMat * modelMat * coords;
}
