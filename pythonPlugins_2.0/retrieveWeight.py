# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

"""
After loading the plugin
Select a blendShape node and run: retrieveWeight command
to show you ino about all existing blendShapes
"""

import sys
import maya.OpenMaya as OpenMaya
import maya.OpenMayaMPx as OpenMayaMPx


kCmdName = "retrieveWeight"


class RetrieveWeight(OpenMayaMPx.MPxCommand):
    """
    """

    def __init__(self):
        super(RetrieveWeight, self).__init__()

    @staticmethod
    def cmdCreator():
        return OpenMayaMPx.asMPxPtr(RetrieveWeight())

    def doIt(self, argList):
        """
        """

        sList = OpenMaya.MSelectionList()
        OpenMaya.MGlobal.getActiveSelectionList(sList)
        iter = OpenMaya.MItSelectionList(sList)

        dependNode = OpenMaya.MObject()
        fnDepNode = OpenMaya.MFnDependencyNode()

        while not iter.isDone():
            iter.getDependNode(dependNode)
            fnDepNode.setObject(dependNode)
            print("-" * 10)
            print("Node: {}".format(fnDepNode.name()))
            if dependNode.apiType() == OpenMaya.MFn.kBlendShape:
                weightPlugArray = fnDepNode.findPlug("weight", False)
                if weightPlugArray.isArray():
                    print("WeightPlug name: {}".format(weightPlugArray.name()))
                    print("WeightPlug info: {}".format(weightPlugArray.info()))
                    print(
                        "WeightPlug number of elements: {}".format(
                            weightPlugArray.numElements()
                        )
                    )
                    for i in range(0, weightPlugArray.numElements()):
                        cPlug = weightPlugArray[i]
                        # or
                        elementPlug = weightPlugArray.elementByPhysicalIndex(i)
                        print("blendShape name {}: {}".format(i + 1, cPlug.name()))
                        print("blendShape value {}: {}".format(i + 1, cPlug.asDouble()))
                        print(
                            "blendShape name {}: {}".format(i + 1, elementPlug.name())
                        )
                        print(
                            "blendShape value {}: {}".format(
                                i + 1, elementPlug.asDouble()
                            )
                        )
            else:
                print("This Node [{}] is not blendShape node".format(fnDepNode.name()))
            iter.next()


def initializePlugin(mObj):
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj, "madoodia.com", "1.0.0", "Any")
    try:
        fnPlugin.registerCommand(kCmdName, RetrieveWeight.cmdCreator)
    except:
        sys.stderr.write("Failed to load plugin {}\n".format(kCmdName))
        raise


def uninitializePlugin(mObj):
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj)
    try:
        fnPlugin.deregisterCommand(kCmdName)
    except:
        sys.stderr.write("Failed to unload plugin {}\n".format(kCmdName))
        raise
