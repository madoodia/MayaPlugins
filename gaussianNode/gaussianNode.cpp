/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "gaussianNode.h"

MTypeId GaussianNode::id(0x00000123);
MObject GaussianNode::aOutValue;
MObject GaussianNode::aInValue;
MObject GaussianNode::aMagnitude;
MObject GaussianNode::aMean;
MObject GaussianNode::aVariance;

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

GaussianNode::GaussianNode()
{
}

GaussianNode::~GaussianNode() {}

void *GaussianNode::creator()
{
  return new GaussianNode;
}

MStatus GaussianNode::initialize()
{
  MFnNumericAttribute nAttr;
  aOutValue = nAttr.create("outValue", "outValue", MFnNumericData::kFloat);
  MAKE_OUTPUT(nAttr);

  aInValue = nAttr.create("inValue", "inValue", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);
  CHECK_MSTATUS(nAttr.setDefault(1.0f));

  aMagnitude = nAttr.create("magnitude", "magnitude", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);
  CHECK_MSTATUS(nAttr.setDefault(0.5f));

  aMean = nAttr.create("mean", "mean", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);
  CHECK_MSTATUS(nAttr.setDefault(0.2f));

  aVariance = nAttr.create("variance", "variance", MFnNumericData::kFloat);
  MAKE_INPUT(nAttr);
  CHECK_MSTATUS(nAttr.setDefault(0.05f));

  CHECK_MSTATUS(addAttribute(aOutValue));
  CHECK_MSTATUS(addAttribute(aInValue));
  CHECK_MSTATUS(addAttribute(aMagnitude));
  CHECK_MSTATUS(addAttribute(aMean));
  CHECK_MSTATUS(addAttribute(aVariance));

  CHECK_MSTATUS(attributeAffects(aInValue, aOutValue));
  CHECK_MSTATUS(attributeAffects(aMagnitude, aOutValue));
  CHECK_MSTATUS(attributeAffects(aMean, aOutValue));
  CHECK_MSTATUS(attributeAffects(aVariance, aOutValue));

  return MS::kSuccess;
}

MStatus GaussianNode::compute(const MPlug &plug, MDataBlock &block)
{
  if (plug != aOutValue)
    return MS::kUnknownParameter;

  float inValue = block.inputValue(aInValue).asFloat();
  float magnitude = block.inputValue(aMagnitude).asFloat();
  float mean = block.inputValue(aMean).asFloat();
  float variance = block.inputValue(aVariance).asFloat();
  if (variance <= 0.0f)
    variance = 0.001f;

  float xMinusB = inValue - mean;
  float output = magnitude * exp(-(xMinusB * xMinusB) / (2.0f * variance));

  MDataHandle hOutput = block.outputValue(aOutValue);
  hOutput.setFloat(output);
  hOutput.setClean();
  block.setClean(plug);

  return MS::kSuccess;
}
