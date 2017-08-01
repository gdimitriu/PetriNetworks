========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : PetriNetwork
========================================================================

	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.

    Petri Network is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Petri Network is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Petri Network; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  


AppWizard has created this PetriNetwork application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your PetriNetwork application.

PetriNetwork.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

PetriNetwork.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CPetriNetworkApp application class.

PetriNetwork.cpp
    This is the main application source file that contains the application
    class CPetriNetworkApp.

PetriNetwork.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

PetriNetwork.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\PetriNetwork.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file PetriNetwork.rc.

res\PetriNetwork.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.

PetriNetwork.reg
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.



/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in PetriNetwork.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

For the child frame window:

ChildFrm.h, ChildFrm.cpp
    These files define and implement the CChildFrame class, which
    supports the child windows in an MDI application.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

PetriNetworkDoc.h, PetriNetworkDoc.cpp - the document
    These files contain your CPetriNetworkDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CPetriNetworkDoc::Serialize).

PetriNetworkView.h, PetriNetworkView.cpp - the view of the document
    These files contain your CPetriNetworkView class.
    CPetriNetworkView objects are used to view CPetriNetworkDoc objects.

res\PetriNetworkDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CPetriNetworkDoc class.  This icon is included by the main
    resource file PetriNetwork.rc.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named PetriNetwork.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////

 This simulator simulate three of most common Petri Network: mPN (Mark Petri 
Network),mJPN (Mark Jump Petri Network) mTPN (Mark Timing Petri Network).
And some basic functions for graphs and digraphs like: cyclicity, conexity, 
Minimum cost tree, Eulerian graph and obtain the Eulerian cycle.
 The simulator was made in Visual C++ 6.0 as Multiple Interface Document.
 The purpose other purpose of this simulator, except the use in the laboratory, 
it is a starting platform for a more comprehensive simulator for PN and Graphs. 
For PN with automate generation of accessibility tree and cover graphs, 
eventually with transition graphs for timing network.
 This simulator have two capability: one is to take a PN from a file and 
realise the graphical PN who can modify and simulate and second is to make the 
PN from scratch in full graphical capability like commercial VISIO.
