#include "gaussianNode.h"

GaussianNode::GaussianNode() {}

GaussianNode::~GaussianNode() {}

MStatus GaussianNode::compute(const MPlug &plug, MDataBlock &data)
{
  MGlobal::displayInfo("This is the First Command I created!");

  return MS::kSuccess;
}

void *GaussianNode::creator()
{
  return new GaussianNode;
}

MStatus GaussianNode::initialize()
{
  MStatus status;

  return MS::kSuccess;
}
