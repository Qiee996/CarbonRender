#ifndef CR_SCENEMANAGER
#define CR_SCENEMANAGER

#include "..\Inc\CRFbxImportManager.h"
#include "..\Inc\CRControllerManager.h"
#include "..\Inc\CRTerrainManager.h"

class SceneManager
{
private:
	SceneManager();
	static SceneManager* ins;
	
	Object sceneRoot;

	void Init();
	void DeleteObject(Object* obj);

public:
	~SceneManager();
	static SceneManager* Instance();
	
	void LoadScene(string sceneName);
	void WriteObj2XMLNode(xml_document<>* sceneDoc, xml_node<>* parent, Object* obj);
	void ReadObjFromXMLNode(xml_node<>* xmlNode, Object* sceneNodeParent);
	void SaveScene(string sceneName);
	void Draw (Object* node, GLuint shaderProgram);
	void DrawScene(GLuint shaderProgram);

	Object* GetRootNode();
	void DeletSceneNode(Object* obj);
};

#endif