#ifndef FIRSTCOMMAND_H
#define FIRSTCOMMAND_H

#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MPxCommand.h>

class FirstCommand : public MPxCommand
{
public:
  FirstCommand();
  virtual ~FirstCommand();

  virtual MStatus doIt(const MArgList &);

  static void *creator();
};

#endif // FIRSTCOMMAND_H