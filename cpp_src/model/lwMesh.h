/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * lwMesh.h
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 2, 2015
 * 作者: ubuntukylin
 */

#ifndef SRC_MODEL_LWMESH_H_
#define SRC_MODEL_LWMESH_H_

#include <iostream>
#include <fstream>
#include "../tools/String.h"

namespace nglib
{
#include <nglib.h>
}
#include <mpi.h>

using namespace nglib;

class lwMesh
{
public:
    lwMesh();
    virtual ~lwMesh();

    void setInFile(const String &name) {m_inFile = name;}
    const String& getInFile() const {return m_inFile;}
    void setOutFile(const String &name) {m_outFile = name;}
    const String& getOutFile() const {return m_inFile;}
    void setOutType(int type) {m_outType = type;}
    int getOutType() const {return m_outType;}
    Ng_Mesh *getMesh() const {return m_mesh;}
    Ng_Meshing_Parameters *getParameter() const {return m_mp;}
    void setParameter(Ng_Meshing_Parameters *mp) {if (m_mp) delete m_mp; m_mp = mp;};
    double getDeflection() const {return m_deflection;}
    void setDeflection(double deflection) {m_deflection = deflection;}

    virtual bool initial() = 0;
    virtual bool intiParameter() = 0;
    virtual bool generateMesh() = 0;
    virtual void meshRefinement() = 0;
    virtual void generateSecondOrder() = 0;
    virtual bool toX3dDataFile(const String &name);//将几何图形数据保存为x3d文件
    virtual bool toInpFile(const String &name);//将网格数据保存为inp文件
    virtual bool toMeshX3dFile(const String& name);//将网格数据保存为x3d文件

protected:
    String m_inFile;                    //输入文件
    String m_outFile;                    //输出文件
    int m_outType;                        //输出文件类型
    Ng_Mesh *m_mesh;                    //网格数据对象
    void **m_geo;                        //几何图形数据对象
    Ng_Meshing_Parameters *m_mp;        //网格划分参数
    Ng_Result m_rst;                    //操作结果
    double m_deflection;                //OCC模型增量网格化的偏差
};

#endif /* SRC_MODEL_LWMESH_H_ */
