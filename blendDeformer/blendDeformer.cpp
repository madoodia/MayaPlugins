/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "blendDeformer.h"

MTypeId BlendDeformer::id(0x00001901);

MObject BlendDeformer::aMesh;
MObject BlendDeformer::aWeight;

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

BlendDeformer::BlendDeformer()
{
}

BlendDeformer::~BlendDeformer() {}

void *BlendDeformer::creator()
{
  return new BlendDeformer;
}

MStatus BlendDeformer::initialize()
{
  MFnNumericAttribute nAttr;
  MFnTypedAttribute tAttr;

  aMesh = tAttr.create("blendMesh", "blendMesh", MFnData::kMesh);

  aWeight = nAttr.create("blendWeight", "blendWeight", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);
  nAttr.setMin(0.0f);
  nAttr.setMax(1.0f);

  CHECK_MSTATUS(addAttribute(aMesh));
  CHECK_MSTATUS(addAttribute(aWeight));

  CHECK_MSTATUS(attributeAffects(aMesh, outputGeom));
  CHECK_MSTATUS(attributeAffects(aWeight, outputGeom));

  // Make it paintable
  MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer blendDeformer weights;");

  return MS::kSuccess;
}

MStatus BlendDeformer::deform(MDataBlock &block,
                              MItGeometry &iter,
                              const MMatrix &matrix,
                              unsigned int multiIndex)
{
  MDataHandle hMesh = block.inputValue(aMesh);
  MObject oMesh = hMesh.asMesh();

  if (oMesh.isNull())
    return MS::kSuccess;

  MFnMesh fnMesh(oMesh);
  MPointArray points;
  fnMesh.getPoints(points);

  float weight = block.inputValue(aWeight).asFloat();
  float enve = block.inputValue(envelope).asFloat();
  MPoint point;
  float pw;

  for (; !iter.isDone(); iter.next())
  {
    point = iter.position();
    pw = weightValue(block, multiIndex, iter.index());
    point += (points[iter.index()] - point) * weight * enve * pw;
    iter.setPosition(point);
  }

  return MS::kSuccess;
}
