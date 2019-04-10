#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <OpenGL/gl3.h>
#include <vector>
#include <iostream>
#include "Component.h"
#include "Material.h"
#include <glm/mat4x4.hpp> 
#include <glm/gtc/type_ptr.hpp>

//need to #define all the names for shader uniforms
#define MODEL_VARIABLE_NAME "Model"
#define NORMAL_VARIABLE_NAME "NormalMatrix"
#define VIEW_VARIABLE_NAME "View"
#define PROJECTION_VARIABLE_NAME "Projection"

#define AMBIENT_VARIABLE_NAME "ambientMaterialColor"
#define DIFFUSE_VARIABLE_NAME "diffuseMaterialColor"
#define SPECULAR_VARIABLE_NAME "specularMaterialColor"
#define TRANSPARENT_VARIABLE_NAME "transparentMaterialColor"
#define OPACITY_VARIABLE_NAME "materialOpacity"
#define SHININESS_VARIABLE_NAME "materialShininess"
#define COLOR_TEXTURE_VARIABLE_NAME "colorTexture"
#define NORMAL_TEXTURE_VARIABLE_NAME "normalTexture"
#define EMISSIVE_TEXTURE_VARIABLE_NAME "emissiveTexture"

//light variables
#define MAX_LIGHTS 32

#define LIGHT_ARRAY_VARIABLE_NAME "lights"
#define LIGHT_POSITION_VARIABLE_NAME "location"
#define LIGHT_DIFFUSE_VARIABLE_NAME "diffuse"
#define LIGHT_SPECULAR_VARIABLE_NAME "specular"
#define LIGHT_LINEAR_VARIABLE_NAME "linearAttenuation"
#define LIGHT_QUADRATIC_VARIABLE_NAME "quadraticAttenuation"

#define LIGHT_COUNT_VARIABLE_NAME "numLights"

// class shader tries to load all possible uniforms, and if it returns -1 , then don't try to load that uniform when binding material
class Shader
{
private:
	GLuint program;
	GLint modelMatrixLoc;
	GLint normalMatrixLoc;
	GLint viewMatrixLoc;
	GLint projectionMatrixLoc;
	GLint ambientColorLoc;
	GLint diffuseColorLoc;
	GLint specularColorLoc;
	GLint transparentColorLoc;
	GLint opacityLoc;
	GLint shininessLoc;
	GLint colorTextureLoc;
	GLint normalTextureLoc;
	GLint emissiveTextureLoc;
	//GLint specularTextureLoc;
	//GLint opacityTextureLoc;

	//light uniforms
	std::vector<GLint> lightPositionLoc;
	std::vector<GLint> lightDiffuseLoc;
	std::vector<GLint> lightSpecularLoc;
	std::vector<GLint> lightLinearAttenuationLoc;
	std::vector<GLint> lightQuadraticAttenuationLoc;

	//GLint lightArrayLoc;

	GLint lightCountLoc;
public:
	Shader(GLuint programID);
	~Shader();
	void loadModelMatrix(glm::mat4 *modelMatrix);
	void loadNormalMatrix(glm::mat3 *normalMatrix);
	void loadViewMatrix(glm::mat4 *viewMatrix);
	void loadProjectionMatrix(glm::mat4 *projectionMatrix);
	void bind();
	void bindMaterial(Material * mat); // load uniforms where the location is not -1, bind textures that are not -1
	void loadLight(Light * light, Transform * t, int index);
	void loadLightCount(int count);
	GLuint getProgramID();
};

class ShaderManager {
private:
	int current;
	std::vector<Shader *> shaders;
	GLuint loadShaderFromFile(GLenum type, std::string & filename);
public:
	ShaderManager();
	~ShaderManager();
	int createProgram(std::string & vertexShader, std::string & fragShader);
	int createProgram(std::string & vertexShader, std::string & geometryShader, std::string & fragShader);
	void bindShader(int programIndex);
	void bindMaterial(Material * mat);
	void loadModelMatrix(glm::mat4 *modelMatrix);
	void loadNormalMatrix(glm::mat3 *normalMatrix);
	void loadViewMatrix(glm::mat4 *viewMatrix);
	void loadProjectionMatrix(glm::mat4 *projectionMatrix);
	void loadLight(Light * light, Transform * t, int index);
	void loadLightCount(int count);
	GLuint getProgramID();
	static void loadShaders(ShaderManager* sm);
};

static int hdrProgram;


#endif