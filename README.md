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
- extract `qt-....tar.gz` inside include (without folder)

in `windows`
cos I have error related to finding `"C:/Program Files/Autodesk/Maya2019/bin/Qt5Cored.dll"` in maya bin dir
I have to use external `Qt5 SDK` not `Maya embeded Qt5 SDK`
so:
- extract `qt-....zip` in `include` dir into a folder
- extract `qt-...tar.gz` in `qt-cmake` folder in `cmake` folder
- actually we are using external `Qt5 SDK` so we don't use `devkit/bin`
- and no need to copy plugins folder into devkit