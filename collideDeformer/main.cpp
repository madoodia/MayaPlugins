/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

/*
Running:
After loading the plugin into maya
Select the main geo and run this maya command:
deformer -type inflateDeformer
then open connection editor and connect 
outMesh of blendShape to mesh property of the deformer
*/

#include "collideDeformer.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{

  MFnPlugin plugin(obj, "madoodia.com", "1.0.0", "Any");

  CHECK_MSTATUS(plugin.registerNode("collideDeformer",
                                    CollideDeformer::id,
                                    CollideDeformer::creator,
                                    CollideDeformer::initialize,
                                    MPxNode::kDeformerNode));

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
  MFnPlugin plugin(obj);

  CHECK_MSTATUS(plugin.deregisterNode(CollideDeformer::id));

  return MS::kSuccess;
}