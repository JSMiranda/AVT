#include "../include/lightManager.h"

const char* lightsIndex[] = { "lights[0].", "lights[1].", "lights[2]." , "lights[3].", "lights[4].", "lights[5].", "lights[6].", "lights[7]." };
const char* l_type_glslname = { "l_type" };
const char* l_dir_glslname = {"l_dir"};
const char* l_pos_glslname = {"l_pos"};
const char* l_spotDir_glslname = {"l_spotDir"};
const char* l_spotCutOff_glslname = {"l_spotCutOff"};

LightManager::LightManager(){
	this->lights_on = false;
	this->n_lights = 0;
}

void LightManager::init(VSShaderLib* shader){
	this->shader = shader;
}


void ClearColor(Light* l){
	float whiteColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	memcpy(l->l_amb, whiteColor, sizeof(float) * 4);
	memcpy(l->l_dif, whiteColor, sizeof(float) * 4);
	memcpy(l->l_spec, whiteColor, sizeof(float) * 4);
}

//Add Spotlight
void LightManager::addLight(float l_spot[4]){
	Light l;
	if(l_spot[3] == 1.0){
		l.l_type = POINT_LIGHT;
	}else {
		l.l_type = DIR_LIGHT;
	}
	memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	
	ClearColor(&l);
	lights[n_lights++] = l;
}
void LightManager::addLight(float l_spot[4], float l_dir[4], float l_cut){
	Light l;
	l.l_type = SPOT_LIGHT;
	
	memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	memcpy(l.l_dir, l_dir, sizeof(float) * 4);
	l.l_spot_cut = l_cut;
	
	ClearColor(&l);
	lights[n_lights++] = l;
}

void LightManager::setLightColor(int light_num, float amb[4], float dif[4], float spec[4]){
	memcpy(lights[light_num].l_amb, amb, sizeof(float) * 4);
	memcpy(lights[light_num].l_dif, dif, sizeof(float) * 4);
	memcpy(lights[light_num].l_spec, spec, sizeof(float) * 4);
}


void LightManager::processSpotLight(int n, Light* l, VSMathLib* core){

	
}
void LightManager::processDirLight(int n, Light* l, VSMathLib* core){
	
	
}
void LightManager::processPointLight(int n, Light* l, VSMathLib* core){
	
	float res[4];
	core->multMatrixPoint(VSMathLib::VIEW, l->l_pos, res);
	
	char type_name[30];
	strcpy(type_name, lightsIndex[n]);
	strcat(type_name,l_type_glslname);
	int type_loc = glGetUniformLocation(shader->getProgramIndex(), type_name);
	glUniform1i(type_loc, l->l_type);
	printf("########DEBUG String:%s, type_loc:%d\n", type_name, type_loc); 
	
	char pos_name[30];
	strcpy(pos_name, lightsIndex[n]);
	strcat(pos_name,l_pos_glslname);
	int pos_loc = glGetUniformLocation(shader->getProgramIndex(), pos_name);	
	glUniform4f(pos_loc, res[0], res[1], res[2], res[3]);
	printf("########DEBUG String:%s, type_loc:%d\n", pos_name, pos_loc); 
	
	
}

void LightManager::drawLight(VSMathLib* core){
	if(lights_on){
		int l;
		Light light;
		for(l = 0; l < n_lights; ++l){
			light = lights[l];
			switch(light.l_type){
				case(SPOT_LIGHT):{
					processSpotLight(l, &light, core);
					break;
				}
				case(DIR_LIGHT):{
					processDirLight(l, &light, core);
					break;	
				}
				case(POINT_LIGHT):{
					printf("processing point light\n");
					processPointLight(l, &light, core);
					break;
				}
				default:{
					printf("Light type:%d is not supported:(\n", light.l_type);
				}
			}
			
		}
	}
}

void LightManager::lightsOff(){
	lights_on = false;
}
void LightManager::lightsOn(){
	lights_on = true;
}
