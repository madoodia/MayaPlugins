#include "gaussianNode.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
  MStatus status;

  MFnPlugin plugin(obj, "madoodia.com", "1.0.0", "Any");

  status = plugin.registerNode("hello", GaussianNode::creator);

  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
  MStatus status;

  MFnPlugin plugin(obj);

  status = plugin.deregisterNode("hello");

  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}