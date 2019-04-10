#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>


#include "Material.h"
#include "Component.h"
#include "ECSEngine.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>

//TO BE DELETED. THIS WAS FOR TESTING MODEL LOADING
const GLint vertexAttrib1 = 0;
const GLint rgbaAttrib1   = 1;
const GLint normAttrib1   = 2;
const GLint tanAttrib1    = 3;
const GLint bitanAttrib1  = 4;
const GLint texAttrib1    = 5;

class Scene;

class LevelLoader{
private:
	int determineShader(Material &m);
	void loadShaders();
	void addUnused(ECSEngine * engine, Scene * sc);
public:
	LevelLoader();
	void openLevel(std::string & directory, ECSEngine * engine); 
	void testLevel(ECSEngine * engine); // hardcoded version of openLevel(). used for testing and allowing development of the game's systems to begin and be tested
};



struct Mesh{
	GLuint VBO;
	GLuint IBO;
	glm::vec4 location;
	int numVertices;
	int indexCount;
	std::string name;
	unsigned int materialIndex;
	bool hasTangents;
	int count = 0; // number of objects that use this Mesh. used to create render-only entities from non used objects
	Mesh();
};

struct LightData{

	std::string name;
	int count = 0;

	glm::vec3 location;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float linearAttenuation;
	float quadraticAttenuation;

};


struct Vertex {
	glm::vec4 position;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	Vertex();
	Vertex(const glm::vec4 &pos, const glm::vec2 &uvCoords, const glm::vec3 &norm, const glm::vec3 &tan, const glm::vec3 &bitan)
	{
		position = pos;
		uv = uvCoords;
		normal = norm;
		tangent = tan;
		bitangent = bitan;
	}
};

struct ComponentWrapper {
	bool hasRenderable = false;
	Renderable r;
	bool hasTransform = false;
	Transform t;
	bool hasLight = false;
	Light l;
	// ComponentWrapper(Transform& t_in, Renderable & r_in)
	// {
	// 	t = t_in;
	// 	r = r_in;
	// }
};


class Scene {
private:
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<LightData> lights;
	TextureLoader texManager;

	void processScene(const aiScene* scene, std::string & filename);
	void createMesh(const aiMesh* m, std::string &name, const aiScene * scene);
	void processMaterials(const aiScene* scene, std::string & filename);
	void processLights(const aiScene* scene);
	void processNodes(aiNode * node, const aiScene* scene);
	aiMatrix4x4 getTransformation(const aiScene * scene, std::string &name);
	aiMatrix4x4 getTransformationHelper(aiNode * node);
	ComponentWrapper * createMeshWrapper(int index, int entityID);
	ComponentWrapper * createLightWrapper(int index, int entityID);

public:
	Scene();
	bool openFile(std::string & filename);
	ComponentWrapper * getMeshByName(std::string & name, int entityID);
	int getUnusedMeshCount();
	ComponentWrapper * getUnusedMesh(int entityID); // gets first unused mesh
	int getUnusedLightCount();
	ComponentWrapper * getUnusedLight(int entityID);
	void print();
	void render();
};

#endif