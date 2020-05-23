# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

"""
Usage:
- load plugin into maya:
from maya import cmds
cmds.loadPlugin("nodeInfoCmd.py")
- select a node that is connected to others
run:
cmds.nodeInfoCmd()
"""

import sys

import maya.OpenMaya as OpenMaya
import maya.OpenMayaMPx as OpenMayaMPx

kNodeInfoName = "nodeInfoCmd"

kQuietFlag = "-q"
kQuietLongFlag = "-quiet"


class NodeInfoCmd(OpenMayaMPx.MPxCommand):
    """
    Main Class of the plugin for getting info of the node.
    """

    def __init__(self):
        super(NodeInfoCmd, self).__init__()
        self.quiet = 0

    def doIt(self, argsList):
        """        
        Virtual method for doing the main job when command is run.
        """

        # Parsing the arguments
        argData = OpenMaya.MArgDatabase(self.syntax(), argsList)
        if argData.isFlagSet(kQuietFlag):
            self.quiet = 1

        sList = OpenMaya.MSelectionList()
        OpenMaya.MGlobal.getActiveSelectionList(sList)

        iter = OpenMaya.MItSelectionList(sList)

        dependNode = OpenMaya.MObject()
        fnDependNode = OpenMaya.MFnDependencyNode()

        while iter.isDone() == 0:

            iter.getDependNode(dependNode)
            fnDependNode.setObject(dependNode)

            nodeName = fnDependNode.name()
            print("-------------------\n")
            print("{} is of type {}\n".format(nodeName, dependNode.apiTypeStr()))
            try:
                connectedPlugs = OpenMaya.MPlugArray()
                try:
                    fnDependNode.getConnections(connectedPlugs)
                except:
                    pass

                numberOfPlugs = connectedPlugs.length()
                if not self.quiet:
                    print("Number of Connections found: {}\n".format(numberOfPlugs))

                for i in range(0, numberOfPlugs):
                    plug = connectedPlugs[i]
                    pInfo = plug.info()
                    if not self.quiet:
                        print("Connected plug info: {}\n".format(pInfo))

                    array = OpenMaya.MPlugArray()
                    plug.connectedTo(array, 1, 0)
                    for i in range(0, array.length()):
                        pNode = array[i].node()
                        if not self.quiet:
                            fnConnectedNode = OpenMaya.MFnDependencyNode(pNode)
                            print(
                                "This plug is the destination of Node: {}\n".format(
                                    fnConnectedNode.name()
                                )
                            )
            except:
                sys.stderr.write("Failed to get connections: {}".format(kNodeInfoName))

            iter.next()

        print("-------------------\n")


def cmdCreator():
    """
    Command Creator.
    
    Will create an instance of the class for registering the plugin.
    """
    return OpenMayaMPx.asMPxPtr(NodeInfoCmd())


def syntaxCreator():
    """
    Syntax Creator.
    
    For checking all flags come with the command.
    """
    syntax = OpenMaya.MSyntax()
    syntax.addFlag(kQuietFlag, kQuietLongFlag)
    return syntax


def initializePlugin(mObj):
    """
    Initializing (loading) the Plugin in maya
    """
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj, "madoodia.com", "1.0.0", "Any")
    try:
        fnPlugin.registerCommand(kNodeInfoName, cmdCreator, syntaxCreator)
    except:
        sys.stderr.write("Failed to Register Command {}\n".format(kNodeInfoName))
        raise


def uninitializePlugin(mObj):
    """
    Uninitializing (unloading) the Plugin in maya
    """
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj)
    try:
        fnPlugin.deregisterCommand(kNodeInfoName)
    except:
        sys.stderr.write("Failed to Deregister Command {}\n".format(kNodeInfoName))
        raise
