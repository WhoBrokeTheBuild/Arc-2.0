#include "OBJDocument.h"

void Arc::OBJDocument::loadFile( const string& filename )
{
	m_Filename = filename;
    Buffer buff = Buffer::LoadFromFile(m_Filename);
	loadBuffer(buff);
}

void Arc::OBJDocument::loadString( const string& data )
{
	m_Filename = "";
    Buffer buff = Buffer(data);
	loadBuffer(buff);
}

void Arc::OBJDocument::loadBuffer( Buffer& data )
{
	reset();

	string line;
	OBJObject* pCurrObj = nullptr;

	data.resetReadIndex();

	while ( ! data.endOfBuffer())
	{
		line = data.readNextLine();

		if (line.length() == 0 || line[0] == '#')
			continue;

		ArrayList<string> parts = Arc_StringSplit(line, ' ');

		if (parts.getSize() == 0)
			continue;

		if (parts[0] == "v")
		{
			if (pCurrObj == nullptr)
			{
				pCurrObj = &addObject("Default");
				pCurrObj->setFaceStartInd(m_Faces.getSize());
			}

			float verts[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				verts[i - 1] = Arc_ParseFloat(parts[i]);
			}

			addVertex(Vector3(verts[0], verts[1], verts[2]));
		}
		else if (parts[0] == "vt")
		{
			if (pCurrObj == nullptr)
			{
				pCurrObj = &addObject("Default");
				pCurrObj->setFaceStartInd(m_Faces.getSize());
			}

			float verts[2] = { 0.0f, 0.0f };

			for (unsigned int i = 1; i <= 2; ++i)
			{
				if (i >= parts.getSize())
					break;

				verts[i - 1] = Arc_ParseFloat(parts[i]);
			}

			addTextureVertex(Vector2(verts[0], verts[1]));
		}
		else if (parts[0] == "vn")
		{
			if (pCurrObj == nullptr)
			{
				pCurrObj = &addObject("Default");
				pCurrObj->setFaceStartInd(m_Faces.getSize());
			}

			float verts[3] = { 1.0f, 1.0f, 1.0f };

			for (unsigned int i = 1; i <= 3; ++i)
			{
				if (i >= parts.getSize())
					break;

				verts[i - 1] = Arc_ParseFloat(parts[i]);
			}

			addNormal(Vector3(verts[0], verts[1], verts[2]));
		}
		else if (parts[0] == "f")
		{
			if (pCurrObj == nullptr)
			{
				pCurrObj = &addObject("Default");
				pCurrObj->setFaceStartInd(m_Faces.getSize());
			}

			int vertInds[4] = { -1, -1, -1, -1 };
			int normInds[4] = { -1, -1, -1, -1 };
			int texInds[4] = { -1, -1, -1, -1 };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				if (Arc_StringContains(parts[i], "//"))
				{
					ArrayList<string> subParts = Arc_StringSplit(parts[i], "//");

					if (subParts.getSize() == 0)
						break;

					vertInds[i - 1] = Arc_ParseInt(subParts[0]);

					if (subParts.getSize() == 2)
					{
						normInds[i - 1] = Arc_ParseInt(subParts[1]);
					}
				}
				else if (Arc_StringContains(parts[i], "/"))
				{
					ArrayList<string> subParts = Arc_StringSplit(parts[i], '/');

					if (subParts.getSize() == 0)
						break;

					vertInds[i - 1] = Arc_ParseInt(subParts[0]);

					if (subParts.getSize() >= 2)
					{
						texInds[i - 1] = Arc_ParseInt(subParts[1]);
					}
					
					if (subParts.getSize() >= 3)
					{
						normInds[i - 1] = Arc_ParseInt(subParts[2]);
					}
				}
				else
				{
					vertInds[i - 1] = Arc_ParseInt(parts[i]);
				}
			}

			OBJFace& face = addFace();

			for (int i = 0; i < 4; ++i)
			{
				if (vertInds[i] != -1)
					face.addVertexIndex(vertInds[i] - 1);

				if (normInds[i] != -1)
					face.addNormalIndex(normInds[i] - 1);

				if (texInds[i] != -1)
					face.addTextureVertexIndex(texInds[i] - 1);
			}

		}
		else if (parts[0] == "o")
		{
			if (pCurrObj != nullptr)
				pCurrObj->setFaceEndInd(m_Faces.getSize() - 1);

			pCurrObj = &addObject(parts[1]);

			pCurrObj->setFaceStartInd(m_Faces.getSize());
		}
		else if (parts[0] == "mtllib")
		{
			loadMaterialFile(Arc_Dirname(m_Filename) + "/" + parts[1]);
		}
		else if (parts[0] == "usemtl")
		{
			if (pCurrObj == nullptr)
			{
				pCurrObj = &addObject("Default");
				pCurrObj->setFaceStartInd(m_Faces.getSize());
			}

			pCurrObj->setMaterialName(parts[1]);
		}
	}

	if (pCurrObj != nullptr)
		pCurrObj->setFaceEndInd(m_Faces.getSize() - 1);
}

void Arc::OBJDocument::reset( void )
{
	m_Faces.clear();
	m_Normals.clear();
	m_TexVertices.clear();
	m_Vertices.clear();
	m_Objects.clear();
	m_Materials.clear();
}

Arc::ArrayList<string> Arc::OBJDocument::getObjectNames( void ) const
{
	ArrayList<string> names;

	for (auto it = m_Objects.itConstBegin(); it != m_Objects.itConstEnd(); ++it)
		names.add(it->first);

	return names;
}

void Arc::OBJDocument::resetChildPointers( void )
{
	OBJFace* pFace;
	for (auto it = m_Faces.itBegin(); it != m_Faces.itEnd(); ++it)
	{
		pFace = &(*it);
		pFace->setDocument(this);
	}

	OBJObject* pObj;
	for (auto it = m_Objects.itBegin(); it != m_Objects.itEnd(); ++it)
	{
		pObj = &it->second;
		pObj->setDocument(this);
	}
}

void Arc::OBJDocument::loadMaterialFile( const string& filename )
{
	Buffer buff = Buffer::LoadFromFile(filename);

	string line;
	OBJMaterial* pCurrMtl = nullptr;

	while ( ! buff.endOfBuffer())
	{
		line = buff.readNextLine();

		if (line.length() == 0 || line[0] == '#')
			continue;

		ArrayList<string> parts = Arc_StringSplit(line, ' ');

		if (parts.getSize() == 0)
			continue;

		if (parts[0] == "newmtl")
		{
			pCurrMtl = &addMaterial(parts[1]);
		}
		else if(parts[0] == "Ka")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				color[i - 1] = Arc_ParseFloat(parts[i]);
			}

			pCurrMtl->setAmbientColor(Vector4(color[0], color[1], color[2], color[3]));
		}
		else if(parts[0] == "Kd")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				color[i - 1] = Arc_ParseFloat(parts[i]);
			}

			pCurrMtl->setDiffuseColor(Vector4(color[0], color[1], color[2], color[3]));
		}
		else if(parts[0] == "Ks")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

			for (unsigned int i = 1; i <= 4; ++i)
			{
				if (i >= parts.getSize())
					break;

				color[i - 1] = Arc_ParseFloat(parts[i]);
			}

			pCurrMtl->setSpecularColor(Vector4(color[0], color[1], color[2], color[3]));
		}
		else if (parts[0] == "Ns")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			float specCoeff = Arc_ParseFloat(parts[1]);
			pCurrMtl->setSpecularCoeff(specCoeff);
		}
		else if (parts[0] == "d" || parts[0] == "Tr")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			float dissolved = Arc_ParseFloat(parts[1]);
			pCurrMtl->setDissolved(dissolved);
		}
		else if (parts[0] == "illum")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			int illum = Arc_ParseInt(parts[1]);
			pCurrMtl->setIllumMode(illum);
		}
		else if (parts[0] == "map_Ka")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setAmbientTexMapFilename(parts[1]);
		}
		else if (parts[0] == "map_Kd")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setDiffuseTexMapFilename(parts[1]);
		}
		else if (parts[0] == "map_Ks")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setSpecularTexMapFilename(parts[1]);
		}
		else if (parts[0] == "map_Ns")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setSpecularHilightMapFilename(parts[1]);
		}
		else if (parts[0] == "map_d")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setAlphaMapFilename(parts[1]);
		}
		else if (parts[0] == "map_bump" || parts[0] == "bump")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setBumpMapFilename(parts[1]);
		}
		else if (parts[0] == "disp")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setDisplacementMapFilename(parts[1]);
		}
		else if (parts[0] == "decal")
		{
			if (pCurrMtl == nullptr)
				pCurrMtl = &addMaterial("Default");

			pCurrMtl->setDecalMapFilename(parts[1]);
		}
	}
}