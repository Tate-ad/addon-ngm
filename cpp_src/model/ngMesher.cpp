/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * ngMesher.cpp
 * 描述：
 *
 * 版本：1.0
 * 创建时间: Sep 5, 2015
 * 作者: ubuntukylin
 */

#include "ngMesher.h"
#include "ngEnum.h"
#include "stpMesh.h"
#include "igesMesh.h"
#include "brepMesh.h"
#include "stlMesh.h"
#include "csgMesh.h"

ngMesher::ngMesher()
: m_mesh(0),
  m_isSecondOrder(false),
  m_isRefinement(false)
{
//    MPI_Init(&argc, &argv);
}

ngMesher::~ngMesher()
{
    delete m_mesh;

//    MPI_Finalize();
}

bool ngMesher::loadFile(const String& name, int type)
{
    if (m_mesh)
    {
        delete m_mesh;
        m_mesh = 0;
    }

    if (type == nglib::FT_None)
    {
        String ext = name.right(name.length() - name.find_last_of('.'));
        if (ext.compareNoCase(".stl"))
            type = nglib::FT_STL;
        else if (ext.compareNoCase(".stlb"))
            type = nglib::FT_STLE;
        else if (ext.compareNoCase(".geo") || ext.compareNoCase(".ngg"))
            type = nglib::FT_GEO;
        else if (ext.compareNoCase(".sat"))
            type = nglib::FT_ACIS;
        else if (ext.compareNoCase(".stp") || ext.compareNoCase(".step"))
            type = nglib::FT_STEP;
        else if (ext.compareNoCase(".igs") || ext.compareNoCase(".iges"))
            type = nglib::FT_IGES;
        else if (ext.compareNoCase(".brep"))
            type = nglib::FT_BREP;
    }

    switch (type)
    {
        case nglib::FT_STL:
            m_mesh = new stlMesh();
            break;
        case nglib::FT_STLE:
            m_mesh = new stlMesh();
            ((stlMesh*)m_mesh)->setIsBinary(true);
            break;
        case nglib::FT_GEO:
            m_mesh = new csgMesh();
            break;
        case nglib::FT_ACIS:
            break;
        case nglib::FT_STEP:
            m_mesh = new stpMesh();
            break;
        case nglib::FT_IGES:
            m_mesh = new igesMesh();
            break;
        case nglib::FT_BREP:
            m_mesh = new brepMesh();
            break;
        default:
            break;
    }

    if (m_mesh)
    {
        m_mesh->setInFile(name);
        return true;
    }

    return false;
}

bool ngMesher::toInpFile(const String& name)
{
    String namebase;

    if (name.empty())
        return false;

    namebase = name.left(name.find_last_of('.'));

    if (m_mesh)
    {
        if (!m_mesh->intiParameter())
            return false;

        if (!m_mesh->generateMesh())
            return false;

        if (m_isRefinement)
        {
            m_mesh->meshRefinement();
        }
        if (m_isSecondOrder)
        {
            m_mesh->generateSecondOrder();
        }

        m_mesh->toInpFile(name);
        m_mesh->toMeshX3dFile(namebase + ".x3d");

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Job finished" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }

    return false;
}

bool ngMesher::toGeometryX3dFile(const String& name)
{
    if (m_mesh)
        return m_mesh->toX3dDataFile(name);

    return false;
}

bool ngMesher::initial()
{
    if (m_mesh)
        return m_mesh->initial();

    return false;
}

void ngMesher::setDeflection(double deflection)
{
    if (m_mesh)
        m_mesh->setDeflection(deflection);
}
