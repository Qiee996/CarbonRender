#include "..\Inc\CRTextureManager.h"

TextureManager* TextureManager::ins = nullptr;

TextureManager::TextureManager()
{
	GLubyte D[8][8][3];
	GLubyte N[8][8][3];
	GLubyte S[8][8][3];
	GLubyte nullTexData[8][8][4];
	int i, j;
	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < 8; j++) 
		{
			D[i][j][0] = (GLubyte)255;
			D[i][j][1] = (GLubyte)255;
			D[i][j][2] = (GLubyte)255;
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			N[i][j][0] = (GLubyte)128;
			N[i][j][1] = (GLubyte)128;
			N[i][j][2] = (GLubyte)255;
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			S[i][j][0] = (GLubyte)255;//Roughness
			S[i][j][1] = (GLubyte)255;//Metallic
			S[i][j][2] = (GLubyte)0;
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			nullTexData[i][j][0] = (GLubyte)0;
			nullTexData[i][j][1] = (GLubyte)0;
			nullTexData[i][j][2] = (GLubyte)0;
			nullTexData[i][j][3] = (GLubyte)0;
		}
	}

	glGenTextures(3, defaultTex);
	glBindTexture(GL_TEXTURE_2D, defaultTex[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, D);

	glBindTexture(GL_TEXTURE_2D, defaultTex[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, N);

	glBindTexture(GL_TEXTURE_2D, defaultTex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, S);

	glGenTextures(1, &nullTex);
	glBindTexture(GL_TEXTURE_2D, nullTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullTexData);
}

TextureManager::~TextureManager()
{
	glDeleteTextures(3, defaultTex);

	for (unordered_map<string, GLuint>::iterator i = texturesMap.begin(); i != texturesMap.end(); i++)
		glDeleteTextures(1, &(i->second));

	texturesMap.clear();
	ins = nullptr;
}

TextureManager * TextureManager::Instance()
{
	if (ins == nullptr)
		ins = new TextureManager();

	return ins;
}

GLuint TextureManager::LoadTexture(string dir)
{
	char* fullDir = "Resources\\Textures\\";
	fullDir = FileReader::BindString(fullDir, (char*)dir.c_str());
	if (strstr(fullDir, ".tga") == nullptr)
		fullDir = FileReader::BindString(fullDir, ".tga");
	if (texturesMap.find(fullDir) != texturesMap.end())
		return texturesMap[fullDir];

	GLuint tex = SOIL_load_OGL_texture(fullDir,
		SOIL_LOAD_AUTO, 
		SOIL_CREATE_NEW_ID, 
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);

	if (tex == 0)
		cout << "SOIL loading error: " << SOIL_last_result() << " : " << fullDir << endl;
	else
		texturesMap[fullDir] = tex;

	return tex;
}

GLuint TextureManager::LoadDefaultD()
{
	return defaultTex[0];
}

GLuint TextureManager::LoadDefaultN()
{
	return defaultTex[1];
}

GLuint TextureManager::LoadDefaultS()
{
	return defaultTex[2];
}

GLuint TextureManager::GetNullTex()
{
	return nullTex;
}
