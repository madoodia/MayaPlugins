#include "firstCommand.h"

#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
  MStatus status;

  MFnPlugin plugin(obj, "madoodia.com", "1.0.0", "Any");

  status = plugin.registerCommand("hello", FirstCommand::creator);

  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
  MStatus status;

  MFnPlugin plugin(obj);

  status = plugin.deregisterCommand("hello");

  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}