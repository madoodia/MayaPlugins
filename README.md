# MayaPlugins
Learning Maya API by creating cool plugins here

Some files are built from Maya Devkit samples


For using:

- put gaussianNode.mll (or .so) in document/maya<version>/plug-ins folder and
- put AEgaussianTemplate.mel in document/maya<version>/scripts folder

- run maya
- load the plugin
- go to hypershade and create gaussian node in utility list



in `linux`:
- copy plugins folder of maya installation inside maya sdk
- copy all contents of devkit inside maya sdk (one folder up)
- extract `qt-...tar.gz` in `qt-cmake` folder in `cmake` folder
- extract `qt-....tar.gz inside include (without folder)
