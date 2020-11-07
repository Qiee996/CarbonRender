#ifndef CR_SKYPASS
#define CR_SKYPASS

#include "..\Inc\CRRenderPass.h"
#include "..\Inc\CRFbxImportManager.h"
#include "..\Inc\CRCameraManager.h"
#include "..\Inc\CRWeatherSystem.h"

class SkyRenderPass : public RenderPass
{
private:
	MeshObject sphere;
	int cubeSize = 512;
	GLuint fboCube;
	GLuint milkwayTex;

	void GetReady4Render(PassOutput* input);
	void Render(PassOutput* input);
public:
	void Init();
};

#endif