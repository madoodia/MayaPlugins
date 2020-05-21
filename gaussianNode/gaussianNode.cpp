/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "gaussianNode.h"

MTypeId GaussianNode::id(0x00001900);

MObject GaussianNode::aOutput;
MObject GaussianNode::aInput;
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
  aOutput = nAttr.create("output", "output", MFnNumericData::kFloat);
  MAKE_OUTPUT(nAttr);

  aInput = nAttr.create("input", "input", MFnNumericData::kFloat);
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

  CHECK_MSTATUS(addAttribute(aOutput));
  CHECK_MSTATUS(addAttribute(aInput));
  CHECK_MSTATUS(addAttribute(aMagnitude));
  CHECK_MSTATUS(addAttribute(aMean));
  CHECK_MSTATUS(addAttribute(aVariance));

  CHECK_MSTATUS(attributeAffects(aInput, aOutput));
  CHECK_MSTATUS(attributeAffects(aMagnitude, aOutput));
  CHECK_MSTATUS(attributeAffects(aMean, aOutput));
  CHECK_MSTATUS(attributeAffects(aVariance, aOutput));

  return MS::kSuccess;
}

MStatus GaussianNode::compute(const MPlug &plug, MDataBlock &block)
{
  if (plug != aOutput)
    return MS::kUnknownParameter;

  float input = block.inputValue(aInput).asFloat();
  float magnitude = block.inputValue(aMagnitude).asFloat();
  float mean = block.inputValue(aMean).asFloat();
  float variance = block.inputValue(aVariance).asFloat();
  if (variance <= 0.0f)
    variance = 0.001f;

  float xMinusB = input - mean;
  float output = magnitude * exp(-(xMinusB * xMinusB) / (2.0f * variance));

  MDataHandle hOutput = block.outputValue(aOutput);
  hOutput.setFloat(output);
  hOutput.setClean();
  block.setClean(plug);

  return MS::kSuccess;
}
