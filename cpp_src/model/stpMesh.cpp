/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * stpMesh.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 2, 2015
 * 作者: ubuntukylin
 */

#include "stpMesh.h"

stpMesh::stpMesh()
{
}

stpMesh::~stpMesh()
{
	Ng_OCC_DeleteGeometry(m_geo);
}

bool stpMesh::initial()
{
	if (lwMesh::getInFile().empty())
		return false;

	//加载文件
	m_geo = Ng_OCC_Load_STEP(lwMesh::getInFile().toStdStr());
	if(!m_geo)
	{
		std::cout << "加载step文件失败 "<<lwMesh::getInFile()<<std::endl;
		return false;
	}

	Ng_OCC_IncrementalMesh(m_geo, this->getDeflection());

	return true;
}

bool stpMesh::intiParameter()
{
	//设置网格大小
	m_rst = Ng_OCC_SetLocalMeshSize(m_geo, m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "设置网格大小失败" << std::endl;
		return false;
	}

	return true;
}

bool stpMesh::generateMesh()
{
//	m_rst = Ng_OCC_GenerateMesh(m_geo, m_mesh, m_mp);
//	if(m_rst != NG_OK)
//	{
//		std::cout << "生成网格失败" << std::endl;
//		return false;
//	}

	m_rst = Ng_OCC_GenerateEdgeMesh(m_geo, m_mesh, m_mp);
	if(m_rst != NG_OK)
	{
		std::cout << "生成网格边失败" << std::endl;
		return false;
	}

	m_rst = Ng_OCC_GenerateSurfaceMesh(m_geo, m_mesh, m_mp);
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

void stpMesh::meshRefinement()
{
	//网格精细化
	Ng_OCC_Uniform_Refinement(m_geo, m_mesh);
}

void stpMesh::generateSecondOrder()
{
	//将网格的一阶单元变为二阶单元
	Ng_OCC_Generate_SecondOrder(m_geo, m_mesh);
}
