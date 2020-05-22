/*
# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #
*/

#include "collideDeformer.h"

MTypeId CollideDeformer::id(0x00001903);

MObject CollideDeformer::aCollide;

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

CollideDeformer::CollideDeformer()
{
}

CollideDeformer::~CollideDeformer() {}

void *CollideDeformer::creator()
{
  return new CollideDeformer;
}

MStatus CollideDeformer::initialize()
{
  MFnMatrixAttribute mAttr;

  aCollide = mAttr.create("collide", "collide");

  CHECK_MSTATUS(addAttribute(aCollide));
  CHECK_MSTATUS(attributeAffects(aCollide, outputGeom));

  return MS::kSuccess;
}

MStatus CollideDeformer::deform(MDataBlock &block,
                                MItGeometry &iter,
                                const MMatrix &matrix,
                                unsigned int multiIndex)
{
  MMatrix collideMatrix = block.inputValue(aCollide).asMatrix();
  MMatrix collideMatrixInverse = collideMatrix.inverse();
  MMatrix worldToLocalMatrix = matrix.inverse();

  float enve = block.inputValue(envelope).asFloat();
  MPoint point;

  for (; !iter.isDone(); iter.next())
  {
    point = iter.position();
    point *= matrix;
    point *= collideMatrixInverse;
    if (MVector(point).length() < 1.0f)
    {
      point = MVector(point).normal();
    }
    point *= collideMatrix;
    point *= worldToLocalMatrix;

    iter.setPosition(point);
  }

  return MS::kSuccess;
}

MObject &CollideDeformer::accessoryAttribute() const
{
  return aCollide;
}

MStatus CollideDeformer::accessoryNodeSetup(MDagModifier &mod)
{
  MObject oLocator = mod.createNode("locator", MObject::kNullObj);

  MFnDependencyNode fnLocator(oLocator);

  MPlug pWorldMatrix = fnLocator.findPlug("worldMatrix", false);
  CHECK_MSTATUS(pWorldMatrix.selectAncestorLogicalIndex(0, pWorldMatrix.attribute()));

  MObject oThis = thisMObject();
  MPlug pCollide(oThis, aCollide);

  mod.connect(pWorldMatrix, pCollide);

  return MS::kSuccess;
}