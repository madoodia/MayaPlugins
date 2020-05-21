/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#ifndef GAUSSIANNODE_H
#define GAUSSIANNODE_H

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>

class GaussianNode : public MPxNode
{
public:
  GaussianNode();
  virtual ~GaussianNode();

  static void *creator();

  virtual MStatus compute(const MPlug &plug, MDataBlock &data);
  static MStatus initialize();

  // Plugin unique id
  static MTypeId id;

  // MObjects for custom Attributes
  static MObject aOutput;
  static MObject aInput;
  static MObject aMagnitude;
  static MObject aMean;
  static MObject aVariance;
};

#endif // GAUSSIANNODE_H