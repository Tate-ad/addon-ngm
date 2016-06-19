/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * stpMesh.h
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 2, 2015
 * 作者: ubuntukylin
 */

#ifndef SRC_MODEL_STPMESH_H_
#define SRC_MODEL_STPMESH_H_

#include "lwMesh.h"

class stpMesh: public lwMesh
{
public:
	stpMesh();
	virtual ~stpMesh();

	virtual bool initial();
	virtual bool intiParameter();
	virtual bool generateMesh();
	virtual void meshRefinement();
	virtual void generateSecondOrder();
};

#endif /* SRC_MODEL_STPMESH_H_ */
