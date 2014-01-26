/***************************************************************
 * Name:      dsl_dict_editorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Mikhail Proxy (wproxym(at)gmail[dot]com)
 * Created:   2014-01-09
 * Copyright: Mikhail Proxy ()
 * License:
 **************************************************************/

#include "dsl_dict_editorApp.h"

//(*AppHeaders
#include "dsl_dict_editorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(dsl_dict_editorApp);

bool dsl_dict_editorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	dsl_dict_editorFrame* Frame = new dsl_dict_editorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
