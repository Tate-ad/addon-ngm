/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * brepMesh.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 7, 2015
 * 作者: ubuntukylin
 */

#include "brepMesh.h"

brepMesh::brepMesh()
{
}

brepMesh::~brepMesh()
{
}

bool brepMesh::initial()
{
	if (lwMesh::getInFile().empty())
		return false;

	//加载文件
	m_geo = Ng_OCC_Load_BREP(lwMesh::getInFile().toStdStr());
	if(!m_geo)
	{
		std::cout << "加载step文件失败 "<<lwMesh::getInFile()<<std::endl;
		return false;
	}

	Ng_OCC_IncrementalMesh(m_geo, this->getDeflection());

	return true;
}
