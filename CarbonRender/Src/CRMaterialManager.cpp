#include "..\Inc\CRMaterialManager.h"

MaterialManager* MaterialManager::ins = nullptr;

MaterialManager::MaterialManager()
{
	defaultMaterial.SetDiffuse("");
	defaultMaterial.SetNormal("");
	defaultMaterial.SetSpecular("");
}

MaterialManager::~MaterialManager()
{
	for (vector<Material*>::iterator i = materials.begin(); i != materials.end(); i++)
		delete *i;

	ins = nullptr;
}

MaterialManager * MaterialManager::Instance()
{
	if (ins == nullptr)
		ins = new MaterialManager();

	return ins;
}

Material * MaterialManager::CreateNewMaterial()
{
	Material* newMat = new Material();
	materials.emplace_back(newMat);
	
	return newMat;
}

Material * MaterialManager::GetDefaultMaterial()
{
	return &defaultMaterial;
}

Material::Material()
{
	roughness = 0.5f;
	metallic = 0.5f;
	texIns[0] = 0;
	texIns[1] = 0;
	texIns[2] = 0;
	hasDiffuseTex = false;
	hasNormalTex = false;
	hasSpecularTex = false;
	color = float4(1.0f, 1.0f, 1.0f, 1.0f);
}

Material::~Material()
{
}

void Material::SetRoughness(float r)
{
	roughness = Math::Clamp(r, 0.0f, 1.0f);
}

float Material::GetRoughness()
{
	return roughness;
}

void Material::SetMetallic(float m)
{
	metallic = Math::Clamp(m, 0.0f, 1.0f);
}

float Material::GetMetallic()
{
	return metallic;
}

string Material::GetDiffusePath()
{
	return texDirs[0];
}

GLuint Material::GetDiffuse()
{
	return texIns[0];
}

string Material::GetNormalPath()
{
	return texDirs[1];
}

GLuint Material::GetNormal()
{
	return texIns[1];
}

string Material::GetSpecularPath()
{
	return texDirs[2];
}

GLuint Material::GetSpecular()
{
	return texIns[2];
}

float4 Material::GetColor()
{
	return color;
}

bool Material::HasDiffuseTexture()
{
	return hasDiffuseTex;
}

bool Material::HasNormalTexture()
{
	return hasNormalTex;
}

bool Material::HasSpecularTexture()
{
	return hasSpecularTex;
}

void Material::SetDiffuse(string dir)
{
	texDirs[0] = dir;
	if (dir.empty())
		texIns[0] = TextureManager::Instance()->LoadDefaultD();
	else
	{
		texIns[0] = TextureManager::Instance()->LoadTexture(dir);
		if (texIns[0] == 0)
			texIns[0] = TextureManager::Instance()->LoadDefaultD();
		else
			hasDiffuseTex = true;
	}
}

void Material::SetNormal(string dir)
{
	texDirs[1] = dir;
	if (dir.empty())
		texIns[1] = TextureManager::Instance()->LoadDefaultN();
	else
	{
		texIns[1] = TextureManager::Instance()->LoadTexture(dir);
		if (texIns[1] == 0)
			texIns[1] = TextureManager::Instance()->LoadDefaultN();
		else
			hasNormalTex = true;
	}
}

void Material::SetSpecular(string dir)
{
	texDirs[2] = dir;
	if (dir.empty())
		texIns[2] = TextureManager::Instance()->LoadDefaultS();
	else
	{
		texIns[2] = TextureManager::Instance()->LoadTexture(dir);
		if (texIns[2] == 0)
			texIns[3] = TextureManager::Instance()->LoadDefaultS();
		else
			hasSpecularTex = true;
	}
}

void Material::SetColor(float4 c)
{
	color = c;
}
