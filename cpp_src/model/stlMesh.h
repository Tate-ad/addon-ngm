/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * stlMesh.h
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 7, 2015
 * 作者: ubuntukylin
 */

#ifndef SRC_MODEL_STLMESH_H_
#define SRC_MODEL_STLMESH_H_

#include "lwMesh.h"

class stlMesh: public lwMesh
{
public:
	stlMesh();
	virtual ~stlMesh();

	virtual bool initial();
	virtual bool intiParameter();
	virtual bool generateMesh();
	virtual void meshRefinement();
	virtual void generateSecondOrder();

	bool isBinary() const {return m_isBinary;}
	void setIsBinary(bool isBinary) {m_isBinary = isBinary;}

private:
	bool m_isBinary;
};

#endif /* SRC_MODEL_STLMESH_H_ */
