/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * brepMesh.h
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 7, 2015
 * 作者: ubuntukylin
 */

#ifndef SRC_MODEL_BREPMESH_H_
#define SRC_MODEL_BREPMESH_H_

#include "stpMesh.h"

class brepMesh: public stpMesh
{
public:
	brepMesh();
	virtual ~brepMesh();

	virtual bool initial();
};

#endif /* SRC_MODEL_BREPMESH_H_ */
