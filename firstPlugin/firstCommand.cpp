#include "firstCommand.h"

FirstCommand::FirstCommand() {}

FirstCommand::~FirstCommand() {}

MStatus FirstCommand::doIt(const MArgList &)
{
  MGlobal::displayInfo("This is the First Command I created!");

  return MS::kSuccess;
}

void *FirstCommand::creator()
{
  return new FirstCommand;
}
