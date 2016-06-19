/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * csgMesh.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 8, 2015
 * 作者: ubuntukylin
 */

#include "csgMesh.h"

csgMesh::csgMesh()
{
}

csgMesh::~csgMesh()
{
}

bool csgMesh::initial()
{
	if (lwMesh::getInFile().empty())
		return false;

	//加载文件
	m_geo = Ng_CSG_LoadGeometry(lwMesh::getInFile().toStdStr());
	if(!m_geo)
	{
		std::cout << "加载csg文件失败 "<<lwMesh::getInFile()<<std::endl;
		return false;
	}

	return true;
}

bool csgMesh::intiParameter()
{
	//设置网格大小
//	m_rst = Ng_OCC_SetLocalMeshSize(m_geo, m_mesh, m_mp);
//	if(m_rst != NG_OK)
//	{
//		std::cout << "设置网格大小失败" << std::endl;
//		return false;
//	}

	return true;
}

bool csgMesh::generateMesh()
{
	m_rst = Ng_CSG_GenerateMesh(m_geo, m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "生成网格失败" << std::endl;
		return false;
	}

//	m_rst = Ng_GenerateVolumeMesh(m_mesh, m_mp);
//	if(m_rst != NG_OK)
//	{
//		std::cout << "生成网格体失败" << std::endl;
//		return false;
//	}

	return true;
}

void csgMesh::meshRefinement()
{
	//网格精细化
	Ng_CSG_Uniform_Refinement(m_geo, m_mesh);
}

void csgMesh::generateSecondOrder()
{
	//将网格的一阶单元变为二阶单元
	Ng_CSG_Generate_SecondOrder(m_geo, m_mesh);
}
