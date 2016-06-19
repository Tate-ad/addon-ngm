/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * stlMesh.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 7, 2015
 * 作者: ubuntukylin
 */

#include "stlMesh.h"

stlMesh::stlMesh()
: m_isBinary(false)
{
}

stlMesh::~stlMesh()
{
}

bool stlMesh::initial()
{
	if (lwMesh::getInFile().empty())
		return false;

	//加载文件
	m_geo = Ng_STL_LoadGeometry(lwMesh::getInFile().toStdStr(), m_isBinary);
	if (!m_geo)
	{
		std::cout << "加载stl文件失败 " << lwMesh::getInFile() << std::endl;
		return false;
	}

	m_rst = Ng_STL_InitSTLGeometry(m_geo);
	if (m_rst != NG_OK)
	{
		std::cout << "初始化stl几何图形时发生错误" << std::endl;
		return false;
	}

	return true;
}

bool stlMesh::intiParameter()
{
	return true;
}

bool stlMesh::generateMesh()
{
	m_rst = Ng_STL_MakeEdges(m_geo, m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "生成网格边失败" << std::endl;
		return false;
	}

	m_rst = Ng_STL_GenerateSurfaceMesh(m_geo, m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "生成网格表面失败" << std::endl;
		return false;
	}

	m_rst = Ng_GenerateVolumeMesh(m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "生成网格体失败" << std::endl;
		return false;
	}

	return true;
}

void stlMesh::meshRefinement()
{
	//网格精细化
	Ng_STL_Uniform_Refinement(m_geo, m_mesh);
}

void stlMesh::generateSecondOrder()
{
	//将网格的一阶单元变为二阶单元
	Ng_STL_Generate_SecondOrder(m_geo, m_mesh);
}
