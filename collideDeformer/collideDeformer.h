/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#ifndef COLLIDEDEFORMER_H
#define COLLIDEDEFORMER_H

#include <maya/MArrayDataHandle.h>
#include <maya/MDagModifier.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MPxDeformerNode.h>

class CollideDeformer : public MPxDeformerNode
{
public:
  CollideDeformer();
  virtual ~CollideDeformer();

  static void *creator();

  virtual MStatus deform(MDataBlock &block,
                         MItGeometry &iter,
                         const MMatrix &matrix,
                         unsigned int multiIndex);
  static MStatus initialize();

  virtual MObject &accessoryAttribute() const;
  virtual MStatus accessoryNodeSetup(MDagModifier &mod);

  // Plugin unique id
  static MTypeId id;

  // MObjects for custom Attributes
  static MObject aCollide;
};

#endif // COLLIDEDEFORMER_H