/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#ifndef INFLATEDEFORMER_H
#define INFLATEDEFORMER_H

#include <maya/MArrayDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MPxDeformerNode.h>

class InflateDeformer : public MPxDeformerNode
{
public:
  InflateDeformer();
  virtual ~InflateDeformer();

  static void *creator();

  virtual MStatus deform(MDataBlock &block,
                         MItGeometry &iter,
                         const MMatrix &matrix,
                         unsigned int multiIndex);
  static MStatus initialize();

  // Plugin unique id
  static MTypeId id;

  // MObjects for custom Attributes
  static MObject aAmount;
};

#endif // INFLATEDEFORMER_H