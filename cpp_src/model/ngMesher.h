/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * ngMesher.h
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 5, 2015
 * 作者: ubuntukylin
 */

#ifndef SRC_NGMESHER_H_
#define SRC_NGMESHER_H_

#include "lwMesh.h"

class ngMesher
{
public:
    ngMesher();
    virtual ~ngMesher();

    bool loadFile(const String &name, int type = 0);
    bool toInpFile(const String &name);
    bool toGeometryX3dFile(const String &name);
    bool initial();
    bool isIsRefinement() const {return m_isRefinement;}
    bool isIsSecondOrder() const {return m_isSecondOrder;}

    void setIsSecondOrder(bool isSecondOrder) {m_isSecondOrder = isSecondOrder;}
    void setDeflection(double deflection = 0.01);
    void setIsRefinement(bool isRefinement) {m_isRefinement = isRefinement;}
    void setParameter(Ng_Meshing_Parameters *mp) {if (m_mesh) m_mesh->setParameter(mp);};

private:
    lwMesh *m_mesh;
    bool m_isSecondOrder;
    bool m_isRefinement;
};

#endif /* SRC_NGMESHER_H_ */
