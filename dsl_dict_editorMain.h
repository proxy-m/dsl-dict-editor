/***************************************************************
 * Name:      dsl_dict_editorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Mikhail Proxy (wproxym(at)gmail[dot]com)
 * Created:   2014-01-09
 * Copyright: Mikhail Proxy ()
 * License:
 **************************************************************/

#ifndef DSL_DICT_EDITORMAIN_H
#define DSL_DICT_EDITORMAIN_H

//(*Headers(dsl_dict_editorFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/bmpcbox.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

#include <map>
using namespace std;
#include <wx/hashmap.h>

class dsl_dict_editorFrame: public wxFrame
{
    public:

        dsl_dict_editorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~dsl_dict_editorFrame();

    private:

        //(*Handlers(dsl_dict_editorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void OnComboBox1Selected(wxCommandEvent& event);
        void OnComboBox2Selected(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnComboBox4Selected(wxCommandEvent& event);
        void OnButton8Click(wxCommandEvent& event);
        void OnButton7Click(wxCommandEvent& event);
        void OnButton6Click(wxCommandEvent& event);
        void OnComboBox4TextUpdated(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnTextCtrl3Text1(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnBitmapComboBox1Select(wxCommandEvent& event);
        void OnTextCtrl4Text(wxCommandEvent& event);
        void OnButton9Click(wxCommandEvent& event);
        void OnButton10Click(wxCommandEvent& event);
        void OnTextCtrl1TextEnter(wxCommandEvent& event);
        void OnTextCtrl2TextEnter(wxCommandEvent& event);
        void OnButton11Click(wxCommandEvent& event);
        void OnButton12Click(wxCommandEvent& event);
        //*)

        void OnClose(wxCloseEvent& event);

        void AddStyleTag (const wxString& begin_str, const wxString& end_str);

        //(*Identifiers(dsl_dict_editorFrame)
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_COMBOBOX1;
        static const long ID_COMBOBOX2;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_STATICTEXT3;
        static const long ID_BITMAPCOMBOBOX1;
        static const long ID_COMBOBOX4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON8;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON11;
        static const long ID_PANEL1;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON12;
        static const long idMenuNew;
        static const long idMenuOpen;
        static const long idMenuSave;
        static const long idMenuSaveAs;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(dsl_dict_editorFrame)
        wxTextCtrl* TextCtrl4;
        wxBitmapComboBox* BitmapComboBox1;
        wxButton* Button4;
        wxMenuItem* MenuItem5;
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxMenuItem* MenuItem4;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxButton* Button2;
        wxComboBox* ComboBox4;
        wxButton* Button6;
        wxButton* Button10;
        wxButton* Button11;
        wxButton* Button5;
        wxMenuItem* MenuItem3;
        wxButton* Button3;
        wxButton* Button7;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxButton* Button9;
        wxTextCtrl* TextCtrl2;
        wxComboBox* ComboBox1;
        wxTextCtrl* TextCtrl1;
        wxComboBox* ComboBox2;
        wxStaticText* StaticText4;
        wxTextCtrl* TextCtrl3;
        wxButton* Button8;
        wxButton* Button12;
        //*)

        map<wxString,wxString> LangMap;
        //hashmap<wxString,wxString> WordsWithTranslation;
        //wxHashMap<wxString,wxString> WordsWithTranslation;
        WX_DECLARE_STRING_HASH_MAP(wxString, MyHashMap);
        MyHashMap WordsWithTranslation;
        bool DictWasSaved;
        wxString Path;
        bool ComboBox4AutoTextUpdated; //for MS Windows

        DECLARE_EVENT_TABLE()
};

#endif // DSL_DICT_EDITORMAIN_H
