/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "inflateDeformer.h"

MTypeId InflateDeformer::id(0x00001902);

MObject InflateDeformer::aAmount;

#define MAKE_INPUT(attr)                 \
  CHECK_MSTATUS(attr.setKeyable(true));  \
  CHECK_MSTATUS(attr.setStorable(true)); \
  CHECK_MSTATUS(attr.setReadable(true)); \
  CHECK_MSTATUS(attr.setWritable(true));

#define MAKE_OUTPUT(attr)                 \
  CHECK_MSTATUS(attr.setKeyable(false));  \
  CHECK_MSTATUS(attr.setStorable(false)); \
  CHECK_MSTATUS(attr.setReadable(true));  \
  CHECK_MSTATUS(attr.setWritable(false));

InflateDeformer::InflateDeformer()
{
}

InflateDeformer::~InflateDeformer() {}

void *InflateDeformer::creator()
{
  return new InflateDeformer;
}

MStatus InflateDeformer::initialize()
{
  MFnNumericAttribute nAttr;

  aAmount = nAttr.create("amount", "amount", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);

  CHECK_MSTATUS(addAttribute(aAmount));

  CHECK_MSTATUS(attributeAffects(aAmount, outputGeom));

  // Make it paintable
  MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer inflateDeformer weights;");

  return MS::kSuccess;
}

MStatus InflateDeformer::deform(MDataBlock &block,
                                MItGeometry &iter,
                                const MMatrix &matrix,
                                unsigned int multiIndex)
{
  MArrayDataHandle hInput = block.outputArrayValue(input);
  CHECK_MSTATUS(hInput.jumpToElement(multiIndex));

  MDataHandle hInputElement = hInput.outputValue();
  MObject oInput = hInputElement.child(inputGeom).asMesh();

  MFnMesh fnMesh(oInput);
  MFloatVectorArray normals;
  fnMesh.getVertexNormals(false, normals);

  float amount = block.inputValue(aAmount).asFloat();
  float enve = block.inputValue(envelope).asFloat();
  MPoint point;
  float pw;

  for (; !iter.isDone(); iter.next())
  {
    point = iter.position();
    pw = weightValue(block, multiIndex, iter.index());
    point += normals[iter.index()] * amount * enve * pw;
    iter.setPosition(point);
  }

  return MS::kSuccess;
}
