# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

import sys
import maya.OpenMaya as OpenMaya
import maya.OpenMayaMPx as OpenMayaMPx


kPluginName = "sceneCallBackCmd"

IDs = OpenMaya.MCallbackIdArray()


def removeCallbacks():
    """"""
    for i in range(0, IDs.length()):
        try:
            OpenMaya.MMessage.removeCallback(IDs[i])
        except:
            sys.stderr.write("Failed to remove callback {}".format(IDs[i]))
            raise


def sceneMsgCmd():
    """"""
    IDs.clear()


def openCallback(data):
    """"""
    print("The function registered for MSceneMessage.kBeforeOpen is executed")


def newCallback(data):
    """"""
    print("The function registered for MSceneMessage.kAfterNew is executed")


def saveCheckCallback(retCode, data):
    """"""
    print("The function registered for MSceneMessage.kBeforeSaveCheck is executed")
    retCode = False
    print("Abort current operation")


class SceneMsgCmd(OpenMayaMPx.MPxCommand):
    """"""

    def __init__(self):
        super(SceneMsgCmd, self).__init__()

    def doIt(self, argsList):
        return self.redoIt()

    def redoIt(self):
        openCallbackId = OpenMaya.MSceneMessage.addCallback(
            OpenMaya.MSceneMessage.kBeforeOpen, openCallback, self
        )
        IDs.append(openCallbackId)

        newCallbackId = OpenMaya.MSceneMessage.addCallback(
            OpenMaya.MSceneMessage.kAfterNew, newCallback, self
        )
        IDs.append(newCallbackId)

        saveCheckCallbackId = OpenMaya.MSceneMessage.addCheckCallback(
            OpenMaya.MSceneMessage.kBeforeSaveCheck, saveCheckCallback, self
        )
        IDs.append(saveCheckCallbackId)

    def undoIt(self):
        if IDs.length() != 0:
            removeCallback()

    def isUndoable(self):
        return True


def cmdCreator():
    return OpenMayaMPx.asMPxPtr(SceneMsgCmd())


def initializePlugin(mObj):
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj, "madoodia.com", "1.0.0", "Any")
    try:
        fnPlugin.registerCommand(kPluginName, cmdCreator)
    except:
        sys.stderr.write("Failed to load plugin")
        raise


def uninitializePlugin(mObj):
    fnPlugin = OpenMayaMPx.MFnPlugin(mObj)
    try:
        fnPlugin.deregisterCommand(kPluginName)
    except:
        sys.stderr.write("Failed to unload plugin")
        raise
