/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * lwMesh.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 2, 2015
 * 作者: ubuntukylin
 */

#include "lwMesh.h"

lwMesh::lwMesh()
: m_inFile(),
  m_outFile(), m_outType(0),
  m_mesh(0),
  m_geo(0),
  m_mp(0),
  m_rst(NG_OK),
  m_deflection(0.01)
{
	m_mesh = Ng_NewMesh();
//	m_mp = new Ng_Meshing_Parameters();

	//初始化netgen核心库
	Ng_Init();
}

lwMesh::~lwMesh()
{
	if (m_mesh)
		Ng_DeleteMesh(m_mesh);
	if (m_mp)
	{
		delete m_mp;
		m_mp = 0;
	}

	//卸载netgen核心库
	Ng_Exit();
}

bool lwMesh::toX3dDataFile(const String& name)
{
	return Ng_SaveGeometry(m_geo, name.toStdStr());
}

bool lwMesh::toInpFile(const String& name)
{
	return Ng_SaveMesh(nglib::FT_Abaqus, m_mesh, m_geo, name.toStdStr());
}

bool lwMesh::toMeshX3dFile(const String& name)
{
	return Ng_SaveMesh(nglib::FT_X3D, m_mesh, m_geo, name.toStdStr());
}
