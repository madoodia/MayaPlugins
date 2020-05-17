/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "gaussianNode.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
  const MString UserClassify("utility/general");

  MFnPlugin plugin(obj, "madoodia.com", "1.0.0", "Any");

  CHECK_MSTATUS(plugin.registerNode("gaussian",
                                    GaussianNode::id,
                                    GaussianNode::creator,
                                    GaussianNode::initialize,
                                    MPxNode::kDependNode,
                                    &UserClassify));

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
  MFnPlugin plugin(obj);

  CHECK_MSTATUS(plugin.deregisterNode(GaussianNode::id));

  return MS::kSuccess;
}