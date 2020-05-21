/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#ifndef BLENDDEFORMER_H
#define BLENDDEFORMER_H

#include <maya/MDataBlock.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MPointArray.h>
#include <maya/MPxDeformerNode.h>

class BlendDeformer : public MPxDeformerNode
{
public:
  BlendDeformer();
  virtual ~BlendDeformer();

  static void *creator();

  virtual MStatus deform(MDataBlock &block,
                         MItGeometry &iter,
                         const MMatrix &matrix,
                         unsigned int multiIndex);
  static MStatus initialize();

  // Plugin unique id
  static MTypeId id;

  // MObjects for custom Attributes
  static MObject aMesh;
  static MObject aWeight;
};

#endif // BLENDDEFORMER_H