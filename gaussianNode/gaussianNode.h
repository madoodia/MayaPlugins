#ifndef GAUSSIANNODE_H
#define GAUSSIANNODE_H

#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>

class GaussianNode : public MPxNode
{
public:
  GaussianNode();
  virtual ~GaussianNode();

  virtual MStatus compute(const MPlug &plug, MDataBlock &data);

  static void *creator();
  static MStatus initialize();
};

#endif // GAUSSIANNODE_H