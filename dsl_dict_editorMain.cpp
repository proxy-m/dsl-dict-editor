/***************************************************************
 * Name:      dsl_dict_editorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mikhail Proxy (wproxym(at)gmail[dot]com)
 * Created:   2014-01-09
 * Copyright: Mikhail Proxy ()
 * License:
 **************************************************************/

#include "dsl_dict_editorMain.h"
#include <wx/msgdlg.h>
#include "TranslationPreview.h"

//(*InternalHeaders(dsl_dict_editorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <map>
#include <iterator>
#include <list>
using namespace std;
#include <wx/hashmap.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/arrstr.h>
#include <wx/dcmemory.h>
#include <wx/brush.h>
#include <wx/textdlg.h>

#define wx2_8_H_CPP

#ifdef wx2_8_H_CPP
#include <wx/tokenzr.h>
wxArrayString wxSplit(const wxString& str, const wxChar sep, const wxChar escape = wxT( '\\' ))
{
    if ( escape == wxT('\0') )
    {
        // simple case: we don't need to honour the escape character
        return wxStringTokenize(str, sep, wxTOKEN_RET_EMPTY_ALL);
    }

    wxArrayString ret;
    wxString curr;
    wxChar prev = wxT('\0');

    for ( wxString::const_iterator i = str.begin(),end = str.end();
          i != end; ++i )
    {
        const wxChar ch = *i;

        if ( ch == sep )
        {
            if ( prev == escape )
            {
                // remove the escape character and don't consider this
                // occurrence of 'sep' as a real separator
                *curr.rbegin() = sep;
            }
            else // real separator
            {
                ret.push_back(curr);
                curr.clear();
            }
        }
        else // normal character
        {
            curr += ch;
        }

        prev = ch;
    }

    // add the last token
    if ( !curr.empty() || prev == sep )
        ret.Add(curr);

    return ret;
}
#endif

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(dsl_dict_editorFrame)
const long dsl_dict_editorFrame::ID_STATICTEXT4 = wxNewId();
const long dsl_dict_editorFrame::ID_TEXTCTRL3 = wxNewId();
const long dsl_dict_editorFrame::ID_STATICTEXT1 = wxNewId();
const long dsl_dict_editorFrame::ID_STATICTEXT2 = wxNewId();
const long dsl_dict_editorFrame::ID_COMBOBOX1 = wxNewId();
const long dsl_dict_editorFrame::ID_COMBOBOX2 = wxNewId();
const long dsl_dict_editorFrame::ID_TEXTCTRL1 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON1 = wxNewId();
const long dsl_dict_editorFrame::ID_TEXTCTRL2 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON2 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON3 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON4 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON9 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON10 = wxNewId();
const long dsl_dict_editorFrame::ID_STATICTEXT3 = wxNewId();
const long dsl_dict_editorFrame::ID_BITMAPCOMBOBOX1 = wxNewId();
const long dsl_dict_editorFrame::ID_COMBOBOX4 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON5 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON8 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON6 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON7 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON11 = wxNewId();
const long dsl_dict_editorFrame::ID_PANEL1 = wxNewId();
const long dsl_dict_editorFrame::ID_TEXTCTRL4 = wxNewId();
const long dsl_dict_editorFrame::ID_BUTTON12 = wxNewId();
const long dsl_dict_editorFrame::idMenuNew = wxNewId();
const long dsl_dict_editorFrame::idMenuOpen = wxNewId();
const long dsl_dict_editorFrame::idMenuSave = wxNewId();
const long dsl_dict_editorFrame::idMenuSaveAs = wxNewId();
const long dsl_dict_editorFrame::idMenuQuit = wxNewId();
const long dsl_dict_editorFrame::idMenuAbout = wxNewId();
const long dsl_dict_editorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dsl_dict_editorFrame,wxFrame)
    //(*EventTable(dsl_dict_editorFrame)
    //*)
END_EVENT_TABLE()

dsl_dict_editorFrame::dsl_dict_editorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(dsl_dict_editorFrame)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Dictionary name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer10->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl3 = new wxTextCtrl(Panel1, ID_TEXTCTRL3, _("NoNameDict"), wxDefaultPosition, wxSize(150,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer10->Add(TextCtrl3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("From language:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("To language:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    ComboBox1 = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
    ComboBox1->SetToolTip(_("select source language"));
    BoxSizer3->Add(ComboBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox2 = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ComboBox2->SetToolTip(_("select translation language"));
    BoxSizer3->Add(ComboBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(115,24), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetToolTip(_("select \"Other\" in upper combobox, then you can input source language here and press Enter to trying select it from upper combobox"));
    BoxSizer4->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("<->"), wxDefaultPosition, wxSize(90,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetToolTip(_("swap languages"));
    BoxSizer4->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(115,24), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl2->SetToolTip(_("select \"Other\" in upper combobox, then you can input translation language here and press Enter to trying select it from upper combobox"));
    BoxSizer4->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Bold"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2->SetToolTip(_("boldfaced font"));
    BoxSizer5->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(Panel1, ID_BUTTON3, _("Italic"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button3->SetToolTip(_("italics font"));
    BoxSizer5->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(Panel1, ID_BUTTON4, _("Underlined"), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button4->SetToolTip(_("underlined font"));
    BoxSizer5->Add(Button4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button9 = new wxButton(Panel1, ID_BUTTON9, _("URL"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Button9->SetToolTip(_("insert link to web page (URL)"));
    BoxSizer5->Add(Button9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button10 = new wxButton(Panel1, ID_BUTTON10, _("<< >>"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    Button10->SetToolTip(_("insert link to other dictionary card"));
    BoxSizer5->Add(Button10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Color:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer6->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapComboBox1 = new wxBitmapComboBox(Panel1, ID_BITMAPCOMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0, wxDefaultValidator, _T("ID_BITMAPCOMBOBOX1"));
    BitmapComboBox1->SetToolTip(_("set text color"));
    BoxSizer6->Add(BitmapComboBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    ComboBox4 = new wxComboBox(Panel1, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_COMBOBOX4"));
    ComboBox4->SetToolTip(_("if you want to search or add a word, then input it here first. if you want to see all source words, then leave this field blank and press \"Search part\""));
    BoxSizer7->Add(ComboBox4, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button5 = new wxButton(Panel1, ID_BUTTON5, _("Search word"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer7->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button8 = new wxButton(Panel1, ID_BUTTON8, _("Search part"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer7->Add(Button8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    Button6 = new wxButton(Panel1, ID_BUTTON6, _("Save translation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button6->SetToolTip(_("firstly save every traslation (card). then save dictionary in menu."));
    BoxSizer9->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button7 = new wxButton(Panel1, ID_BUTTON7, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Button7->SetToolTip(_("remove word (card)"));
    BoxSizer9->Add(Button7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button11 = new wxButton(Panel1, ID_BUTTON11, _("Dupticate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button11->SetToolTip(_("duplicate card translation with another key word (source word)"));
    BoxSizer9->Add(Button11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(BoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer8);
    BoxSizer8->Fit(Panel1);
    BoxSizer8->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 2, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(404,139), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer1->Add(TextCtrl4, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer11 = new wxBoxSizer(wxVERTICAL);
    Button12 = new wxButton(this, ID_BUTTON12, _("Preview"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer11->Add(Button12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem6 = new wxMenuItem(Menu1, idMenuNew, _("New\tCtrl-N"), _("New dictionary"), wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem4 = new wxMenuItem(Menu1, idMenuOpen, _("Open\tCtrl-O"), _("Open dictionary"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem3 = new wxMenuItem(Menu1, idMenuSave, _("Save\tCtrl-S"), _("Save dictionary"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem5 = new wxMenuItem(Menu1, idMenuSaveAs, _("Save as ..."), _("Save dictionary as other file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl3Text1);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnComboBox1Selected);
    Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnComboBox2Selected);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl1Text);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl1TextEnter);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton1Click);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl2Text);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl2TextEnter);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton3Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton4Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton9Click);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton10Click);

    Connect(ID_BITMAPCOMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnBitmapComboBox1Select);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnComboBox4Selected);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnComboBox4TextUpdated);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton5Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton5Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton8Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton6Click);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton7Click);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton11Click);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnTextCtrl4Text);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnButton12Click);
    Connect(idMenuNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnNew);
    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnOpen);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnSave);
    Connect(idMenuSaveAs,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnSaveAs);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&dsl_dict_editorFrame::OnAbout);
    //*)

    Connect(wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&dsl_dict_editorFrame::OnClose);

    LangMap[_T("Африкаанс")]=_T("Afrikaans");
    LangMap[_T("Баскский")]=_T("Basque");
    LangMap[_T("Белорусский")]=_T("Belarusian");
    LangMap[_T("Болгарский")]=_T("Bulgarian");
    LangMap[_T("Чешский")]=_T("Czech");
    LangMap[_T("Датский")]=_T("Danish");
    LangMap[_T("Голландский")]=_T("Dutch");
    LangMap[_T("Греческий")]=_T("Greek");
    LangMap[_T("Английский")]=_T("English");
    LangMap[_T("Финский")]=_T("Finnish");
    LangMap[_T("Французский")]=_T("French");
    LangMap[_T("Немецкий (стар.)")]=_T("German");
    LangMap[_T("Немецкий")]=_T("GermanNewSpelling");
    LangMap[_T("Венгерский")]=_T("Hungarian");
    LangMap[_T("Исландский")]=_T("Icelandic");
    LangMap[_T("Индонезийский")]=_T("Indonesian");
    LangMap[_T("Итальянский")]=_T("Italian");
    LangMap[_T("Казахский")]=_T("Kazakh");
    LangMap[_T("Китайский")]=_T("Chinese");
    LangMap[_T("Китайский (традиц.)")]=_T("ChinesePRC");
    LangMap[_T("Латинский")]=_T("Latin");
    LangMap[_T("Латышский")]=_T("Latvian");
    LangMap[_T("Литовский")]=_T("Lithuanian");
    LangMap[_T("Норвежский (букмол)")]=_T("NorwegianBokmal");
    LangMap[_T("Норвежский (нюнорск)")]=_T("NorwegianNynorsk");
    LangMap[_T("Польский")]=_T("Polish");
    LangMap[_T("Португальский")]=_T("Portuguese");
    LangMap[_T("Румынский")]=_T("Romanian");
    LangMap[_T("Русский")]=_T("Russian");
    LangMap[_T("Сербский (кириллица)")]=_T("SerbianCyrillic");
    LangMap[_T("Словацкий")]=_T("Slovak");
    LangMap[_T("Словенский")]=_T("Slovenian");
    LangMap[_T("Испанский (междунар)")]=_T("SpanishModernSort");
    LangMap[_T("Испанский (традицио)")]=_T("SpanishTraditionalSort");
    LangMap[_T("Суахили")]=_T("Swahili");
    LangMap[_T("Шведский")]=_T("Swedish");
    LangMap[_T("Татарский")]=_T("Tatar");
    LangMap[_T("Турецкий")]=_T("Turkish");
    LangMap[_T("Украинский")]=_T("Ukrainian");
    LangMap[_T("Эстонский")]=_T("Estonian");
    LangMap[_T("Other")]=_T("Other");

    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        ComboBox1->Append(key);
        ComboBox2->Append(key);
    }

    ComboBox1->SetSelection(ComboBox1->FindString(_T("Английский")));
    TextCtrl1->SetEditable(FALSE);
    TextCtrl1->SetValue(LangMap[ComboBox1->GetValue()]);
    ComboBox2->SetSelection(ComboBox2->FindString(_T("Русский")));
    TextCtrl2->SetEditable(FALSE);
    TextCtrl2->SetValue(LangMap[ComboBox2->GetValue()]);

    list<wxString> Colors;
    Colors.push_back (_T("black"));
    Colors.push_back (_T("gray"));
    Colors.push_back (_T("white"));
    Colors.push_back (_T("blue"));
    Colors.push_back (_T("cyan"));
    Colors.push_back (_T("green"));
    Colors.push_back (_T("yellow"));
    Colors.push_back (_T("orange"));
    Colors.push_back (_T("red"));
    Colors.push_back (_T("pink"));
    Colors.push_back (_T("violet"));

    for (list<wxString>::const_iterator i=Colors.begin(); i!=Colors.end(); ++i) {
        wxString color = *i;
        wxBitmap bitmap;
        bitmap.Create(16,16);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.SetBackground(wxBrush(wxColour(color)));
        memDC.Clear();
        BitmapComboBox1->Append (color, bitmap);
    }

    ComboBox4AutoTextUpdated = FALSE;

    DictWasSaved = TRUE;

}

dsl_dict_editorFrame::~dsl_dict_editorFrame()
{
    //(*Destroy(dsl_dict_editorFrame)
    //*)
}

void dsl_dict_editorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void dsl_dict_editorFrame::OnClose(wxCloseEvent& event)
{
    if (!DictWasSaved && event.CanVeto()) {
         if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            //event.Skip(FALSE);
            event.Veto();
            return;
         }
    }
    Destroy();
}

void dsl_dict_editorFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void dsl_dict_editorFrame::OnComboBox1Selected(wxCommandEvent& event)
{
    wxString key = ComboBox1->GetValue();
    if (key != _T("Other"))
    {
        TextCtrl1->SetEditable(FALSE);
        TextCtrl1->SetValue(LangMap[key]);
    } else {
        TextCtrl1->SetEditable(TRUE);
        TextCtrl1->SetValue(_T(""));
        TextCtrl1->SetFocus();
    }
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnComboBox2Selected(wxCommandEvent& event)
{
    wxString key = ComboBox2->GetValue();
    if (key != _T("Other"))
    {
        TextCtrl2->SetEditable(FALSE);
        TextCtrl2->SetValue(LangMap[key]);
    } else {
        TextCtrl2->SetEditable(TRUE);
        TextCtrl2->SetValue(_T(""));
        TextCtrl2->SetFocus();
    }
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnButton1Click(wxCommandEvent& event)
{
    int i_tmp = ComboBox1->GetSelection();
    ComboBox1->SetSelection(ComboBox2->GetSelection());
    ComboBox2->SetSelection(i_tmp);

    wxString str_tmp = TextCtrl1->GetValue();
    bool b_tmp = TextCtrl1->IsEditable();
    TextCtrl1->SetValue(TextCtrl2->GetValue());
    TextCtrl1->SetEditable(TextCtrl2->IsEditable());
    TextCtrl2->SetValue(str_tmp);
    TextCtrl2->SetEditable(b_tmp);
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnOpen(wxCommandEvent& event)
{
    if (!DictWasSaved)
    {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO )
        {
            return;
        } //else: proceed asking to the user the new file to open
    }

    wxFileDialog openFileDialog(this, _("Open DSL file"), _T(""), _T(""), _T("DSL files (*.dsl)|*.dsl"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return; // the user changed idea...
    }

    wxString NewPath = openFileDialog.GetPath();
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(NewPath);
    if (!input_stream.IsOk())
    {
        wxMessageBox (wxString(_("Cannot open file: '"))+NewPath+_T("'"), _T("Error opening of file"), wxICON_ERROR | wxOK, this);
        return;
    }

    StatusBar1->SetStatusText(_("Reading from file ..."));

    Path = NewPath;
    WordsWithTranslation.clear();

    wxTextInputStream text_stream(input_stream, _T("\r\n"), wxConvUTF8 );

    bool file_begin = TRUE;

    wxString SourceWord = wxEmptyString;
    bool IsCommentNow = FALSE;
    wxString line1, line2;

    bool wasValue = FALSE;
    list<wxString> keys;

    while(!input_stream.Eof())
    {
        wxString line = text_stream.ReadLine();
        ////wxMessageBox (wxString(_("'"))+line+_T("'"), _T("Info"), wxICON_ERROR | wxOK, this);
        if (file_begin && (line[0]!=L'\uFEFF'))
        {
            wxMessageBox (wxString(_("UTF-8 BOM (byte order mark) not found: L'\\uFEFF' (\\xEF\\xBB\\xBF)")), _T("Warning"), wxICON_WARNING | wxOK, this);
        }
        else if (file_begin)
        {
            line = line.SubString(1,line.size()-1);
        }
        if (file_begin)
        {
            file_begin = FALSE;
        }
        bool was = FALSE;
        int CommentPos;
        while (TRUE)
        {
            while (!IsCommentNow)
            {
                was = TRUE;
                if (!IsCommentNow)
                {
                    CommentPos = line.Find(_T("{{"));
                    if (CommentPos>=0)
                    {
                        IsCommentNow = TRUE;
                        if (CommentPos>0)
                        {
                            line1 = line.SubString(0,CommentPos-1);
                        }
                        else
                        {
                            line1 = wxEmptyString;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                if (IsCommentNow)
                {
                    CommentPos = line.Find(_T("}}"));
                    if (CommentPos>=0)
                    {
                        IsCommentNow = FALSE;
                        if (int(line.size())>CommentPos+2)
                        {
                            line2 = line.SubString(CommentPos+2,line.size()-1);
                        }
                        else
                        {
                            line2 = wxEmptyString;
                        }
                    }
                    else
                    {
                        line2 = wxEmptyString;
                        line = line1;
                        break;
                    }
                    line = line1 + line2;
                }
            }
            if (!was && IsCommentNow)
            {
                CommentPos = line.Find(_T("}}"));
                if (CommentPos>=0)
                {
                    IsCommentNow = FALSE;
                    if (int(line.size())>CommentPos+2)
                    {
                        line2 = line.SubString(CommentPos+2,line.size()-1);
                    }
                    else
                    {
                        line2 = wxEmptyString;
                    }
                }
                else
                {
                    line2 = wxEmptyString;
                    line = line1;
                    break;
                }
                line = line1 + line2;
            }
            else
            {
                break;
            }
        }
        if (!IsCommentNow)
        {
            if (line.size()>0 && line[0]==_T('#'))
            {
                ////wxMessageBox (wxString(_("'"))+line+_T("'"), _T("Info"), wxICON_ERROR | wxOK, this);
                if (line.SubString(1,4) == _T("NAME"))
                {
                    TextCtrl3->SetValue(line.SubString(7,line.size()-2));
                }
                else if (line.SubString(1,14) == _T("INDEX_LANGUAGE"))
                {
                    wxString lang = line.SubString(17,line.size()-2);
                    bool good = FALSE;
                    if (lang != _T("Other"))
                    {
                        for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
                        {
                            wxString value = iter->second;
                            if (lang == value)
                            {
                                ComboBox1->SetSelection(ComboBox1->FindString(iter->first));
                                TextCtrl1->SetEditable(FALSE);
                                TextCtrl1->SetValue(lang);
                                good = TRUE;
                                break;
                            }
                        }
                    }
                    if (!good)
                    {
                        ComboBox1->SetSelection(ComboBox1->FindString(_T("Other")));
                        TextCtrl1->SetEditable(TRUE);
                        TextCtrl1->SetValue(lang);
                    }
                }
                else if (line.SubString(1,17) == _T("CONTENTS_LANGUAGE"))
                {
                    wxString lang = line.SubString(20,line.size()-2);
                    bool good = FALSE;
                    if (lang != _T("Other"))
                    {
                        for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
                        {
                            wxString value = iter->second;
                            if (lang == value)
                            {
                                ComboBox2->SetSelection(ComboBox2->FindString(iter->first));
                                TextCtrl2->SetEditable(FALSE);
                                TextCtrl2->SetValue(lang);
                                good = TRUE;
                                break;
                            }
                        }
                    }
                    if (!good)
                    {
                        ComboBox2->SetSelection(ComboBox2->FindString(_T("Other")));
                        TextCtrl2->SetEditable(TRUE);
                        TextCtrl2->SetValue(lang);
                    }
                }
            }
            else if (line.size()==0 || line[0]!=_T(' '))
            {
                if (line.size()!=0)
                {
                    if (wasValue) {
                        keys.clear();
                        wasValue = FALSE;
                    }
                    keys.push_back(line);
                    SourceWord = line;
                    WordsWithTranslation[SourceWord] = _T("");
                }
            }
            else
            {
                wasValue = TRUE;
                line = line.SubString(1,line.size()-1);
                for (list<wxString>::const_iterator i=keys.begin(); i!=keys.end(); ++i) {
                    if (*i == wxEmptyString)
                    {
                        wxMessageBox (wxString(_("Empty source word found")), _T("File format is incorrect"), wxICON_ERROR | wxOK, this);
                    }
                    else
                    {
                        if (WordsWithTranslation[*i] != _T(""))
                        {
                            WordsWithTranslation[*i] += _T("\r\n");
                        }
                        WordsWithTranslation[*i] += line;
                    }
                }
            }
        }
    }
    ComboBox4->Clear();
    ComboBox4->SetValue(wxEmptyString);
    TextCtrl4->SetValue(wxEmptyString);
    StatusBar1->SetStatusText(_("Reading from file finished."));
    DictWasSaved = TRUE;
}

void dsl_dict_editorFrame::OnButton5Click(wxCommandEvent& event)
{ // "Search word" button
    //wxMessageBox(_("Search word or Enter")); ////
    wxString SourceWord = ComboBox4->GetValue();
    /*if (SourceWord.Matches(_T("*\\**")) || SourceWord.Matches(_T("*\\?*"))) {
        OnButton8Click(event);
        return;
    }*/
    for (size_t i=0; i<SourceWord.size(); ++i) {
        wxChar h = SourceWord.GetChar(i);
        if (h==_T('*') || h==_T('?')) {
            OnButton8Click(event);
            return;
        }
    }
    wxString Translation = WordsWithTranslation[SourceWord];
    ComboBox4->Clear();
    if (Translation != _T("")) {
        ComboBox4->Append(SourceWord);
        TextCtrl4->SetValue(Translation);
        TextCtrl4->SetFocus();
    } else {
        ComboBox4->SetValue(_T(""));
        TextCtrl4->SetValue(_T(""));
        WordsWithTranslation.erase(SourceWord); //
    }
}

void dsl_dict_editorFrame::OnComboBox4Selected(wxCommandEvent& event)
{
    //wxMessageBox(_("On select")); ////
    #if defined(__WXMSW__)
    ComboBox4AutoTextUpdated = TRUE;
    #endif
    wxString SourceWord = ComboBox4->GetValue();
    wxString Translation = WordsWithTranslation[SourceWord];
    TextCtrl4->SetValue(Translation);
    TextCtrl4->SetFocus();
}

void dsl_dict_editorFrame::OnButton8Click(wxCommandEvent& event)
{ // "Search part" button
    //wxMessageBox(_("Search part")); ////
    TextCtrl4->SetValue(_T(""));
    bool good = FALSE;
    wxString SourceWord = wxString(_T("*"))+(ComboBox4->GetValue())+wxString(_T("*"));
    ComboBox4->Clear();
    for(MyHashMap::const_iterator iter = WordsWithTranslation.begin(); iter != WordsWithTranslation.end(); ++iter)
    {
        wxString key = iter->first;
        if (key.Matches(SourceWord)) {
            ComboBox4->Append(key);
            good = TRUE;
        }
    }
    if (!good) {
       ComboBox4->SetValue(_T(""));
    }
    ComboBox4->SetFocus();
}

void dsl_dict_editorFrame::OnButton7Click(wxCommandEvent& event)
{
    wxString SourceWord = ComboBox4->GetValue();
    if (SourceWord == wxEmptyString) {
        wxMessageBox (wxString(_("Source word is empty string")), _T("Problem with source word"), wxICON_WARNING | wxOK, this);
        return;
    }
    if (wxMessageBox(_("Word with translation will be removed from dictionary! Are you sure?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
        return;
    }

    int n = ComboBox4->FindString(SourceWord);
    if (n != wxNOT_FOUND) {
        ComboBox4->Delete(n);
    }
    ComboBox4->SetValue(wxEmptyString);
    TextCtrl4->SetValue(wxEmptyString);
    WordsWithTranslation.erase(SourceWord);
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnButton6Click(wxCommandEvent& event)
{ //Save translation
    wxString SourceWord = ComboBox4->GetValue();
    if (SourceWord == wxEmptyString) {
        wxMessageBox (wxString(_("Source word is empty string")), _T("Problem with source word"), wxICON_WARNING | wxOK, this);
        return;
    }

    wxString Translation = TextCtrl4->GetValue();
    ComboBox4->Clear();
    ComboBox4->Append(SourceWord);
    ComboBox4->SetValue(SourceWord);
    WordsWithTranslation[SourceWord] = Translation;
    TextCtrl4->SetFocus();
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnComboBox4TextUpdated(wxCommandEvent& event)
{
    if (!ComboBox4AutoTextUpdated) {
        //wxMessageBox(_("On text updated, then empty string")); ////
        TextCtrl4->SetValue(wxEmptyString);
    } else {
        ComboBox4AutoTextUpdated = FALSE;
    }
}

void dsl_dict_editorFrame::OnSave(wxCommandEvent& event)
{
    if (DictWasSaved) {
        return; //
    }
    if (Path == wxEmptyString) {
        OnSaveAs(event);
        return;
    }

    wxFileOutputStream output_stream(Path);
    if (!output_stream.IsOk()) {
        wxMessageBox (wxString(_("Cannot save current contents in file: '"))+Path+_T("'"), _T("Error opening of file"), wxICON_ERROR | wxOK, this);
        return;
    }

    StatusBar1->SetStatusText(_("Writing to file ..."));

    wxStringInputStream str_bom(L'\uFEFF');
    output_stream.Write(str_bom);
    wxStringInputStream str_name(wxString(_T("#NAME \""))+TextCtrl3->GetValue()+_T("\"\r\n"));
    output_stream.Write(str_name);
    wxStringInputStream str_from(wxString(_T("#INDEX_LANGUAGE \""))+TextCtrl1->GetValue()+_T("\"\r\n"));
    output_stream.Write(str_from);
    wxStringInputStream str_to(wxString(_T("#CONTENTS_LANGUAGE \""))+TextCtrl2->GetValue()+_T("\"\r\n"));
    output_stream.Write(str_to);
    wxStringInputStream str_spacer (wxString(_T("\r\n")));
    output_stream.Write(str_spacer);
    for(MyHashMap::const_iterator iter = WordsWithTranslation.begin(); iter != WordsWithTranslation.end(); ++iter)
    {
        wxStringInputStream str_key (iter->first+_T("\r\n"));
        output_stream.Write(str_key);
        wxString str_value = iter->second;
        int j = str_value.size()-1;
        int j_begin = j;
        while (j>=0 && (str_value[j]=='\r' || str_value[j]=='\n')) {
            --j;
        }
        if (j>=0) {
            if (j<j_begin) {
                str_value = str_value.SubString(0,j);
            }
        } else {
            str_value = wxEmptyString;
        }
        wxArrayString a = wxSplit (str_value, _T('\n'));
        for (wxArrayString::const_iterator i=a.begin(); i!=a.end(); ++i) {
            wxString str = *i;
            if (str.size()>0 && str[str.size()-1]=='\r') {
                if (str.size()>1) {
                    str = str.SubString(0,str.size()-2);
                } else {
                    str = wxEmptyString;
                }
            }
            wxStringInputStream s(wxString(_T(' '))+str+_T("\r\n"));
            output_stream.Write(s);
        }
        wxStringInputStream str_spacer (wxString(_T("\r\n")));
        output_stream.Write(str_spacer);
    }
    output_stream.Close();
    StatusBar1->SetStatusText(_("Writing to file finished."));
    DictWasSaved = TRUE;
}

void dsl_dict_editorFrame::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save DSL file"), _T(""), _T(""),
        _T("DSL files (*.dsl)|*.dsl"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return; // the user changed idea...
    }
    Path = saveFileDialog.GetPath();
    DictWasSaved = FALSE;
    OnSave(event);
}

void dsl_dict_editorFrame::OnTextCtrl3Text1(wxCommandEvent& event)
{
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnTextCtrl2Text(wxCommandEvent& event)
{
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnNew(wxCommandEvent& event)
{
    if (!DictWasSaved) {
         if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            return;
         } //else: proceed asking to the user the new file to open
    }

    WordsWithTranslation.clear();
    Path = _T("");

    ComboBox4->Clear();
    ComboBox4->SetValue(wxEmptyString);
    TextCtrl4->SetValue(wxEmptyString);

    ComboBox1->SetSelection(ComboBox1->FindString(_T("Английский")));
    TextCtrl1->SetEditable(FALSE);
    TextCtrl1->SetValue(LangMap[ComboBox1->GetValue()]);
    ComboBox2->SetSelection(ComboBox2->FindString(_T("Русский")));
    TextCtrl2->SetEditable(FALSE);
    TextCtrl2->SetValue(LangMap[ComboBox2->GetValue()]);

    TextCtrl3->SetValue(_T("NoNameDict"));

    DictWasSaved = TRUE;
}

void dsl_dict_editorFrame::AddStyleTag (const wxString& begin_str, const wxString& end_str) {
    TextCtrl4->SetEditable (FALSE);
    long from, to;
    TextCtrl4->GetSelection (&from, &to);
    wxString old_str, new_str;
    old_str = TextCtrl4->GetRange (from, to);
    new_str = begin_str + old_str + end_str;
    TextCtrl4->Replace (from, to, new_str);
    TextCtrl4->SetEditable (TRUE);
    TextCtrl4->SetInsertionPoint (from);
    TextCtrl4->SetFocus();
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnButton2Click(wxCommandEvent& event)
{
    AddStyleTag (_T("[b]"), _T("[/b]"));
}

void dsl_dict_editorFrame::OnButton3Click(wxCommandEvent& event)
{
    AddStyleTag (_T("[i]"), _T("[/i]"));
}

void dsl_dict_editorFrame::OnButton4Click(wxCommandEvent& event)
{
    AddStyleTag (_T("[u]"), _T("[/u]"));
}

void dsl_dict_editorFrame::OnBitmapComboBox1Select(wxCommandEvent& event)
{
    AddStyleTag (wxString(_T("[c "))+BitmapComboBox1->GetValue()+_T("]"), _T("[/c]"));
    //BitmapComboBox1->SetValue(wxEmptyString);
    BitmapComboBox1->SetSelection(wxNOT_FOUND);
}

void dsl_dict_editorFrame::OnTextCtrl4Text(wxCommandEvent& event)
{
    //ComboBox4AutoTextUpdated = FALSE;
}

void dsl_dict_editorFrame::OnButton9Click(wxCommandEvent& event)
{
    TextCtrl4->SetEditable (FALSE);
    long from, to;
    TextCtrl4->GetSelection (&from, &to);
    if (from == to) {
        wxString URL = wxGetTextFromUser (_("Input URL here: "), _("URL"));
        if (URL != wxEmptyString) {
            if (URL.SubString(0,6)!=_T("http://") && URL.SubString(0,7)!=_T("https://")) {
                URL = wxString(_T("http://")) + URL;
            }
            TextCtrl4->Replace (from, to, wxString(_T("[url]"))+URL+_T("[/url]"));
        }
        TextCtrl4->SetEditable (TRUE);
        if (URL != wxEmptyString) {
            TextCtrl4->SetInsertionPoint (from);
            TextCtrl4->SetFocus();
            DictWasSaved = FALSE;
        }
    } else {
        AddStyleTag (_T("[url]"), _T("[/url]"));
    }
}

void dsl_dict_editorFrame::OnButton10Click(wxCommandEvent& event)
{
    AddStyleTag (_T("<<"), _T(">>"));
}

void dsl_dict_editorFrame::OnTextCtrl1TextEnter(wxCommandEvent& event)
{
    if (!TextCtrl1->IsEditable() || TextCtrl1->GetValue()==wxEmptyString || TextCtrl1->GetValue()==_T("Other")) {
        return;
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (value == TextCtrl1->GetValue()) {
            ComboBox1->SetSelection (ComboBox1->FindString(key));
            TextCtrl1->SetEditable(FALSE);
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (value.Lower().Matches(/*wxString(_T("*"))+*/TextCtrl1->GetValue().Lower()+_T("*"))) {
            ComboBox1->SetSelection (ComboBox1->FindString(key));
            TextCtrl1->SetValue(value);
            if (value!=_T("Other")) {
                TextCtrl1->SetEditable(FALSE);
            }
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (key == TextCtrl1->GetValue()) {
            ComboBox1->SetSelection (ComboBox1->FindString(key));
            TextCtrl1->SetValue(value);
            TextCtrl1->SetEditable(FALSE);
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (key.Lower().Matches(/*wxString(_T("*"))+*/TextCtrl1->GetValue().Lower()+_T("*"))) {
            ComboBox1->SetSelection (ComboBox1->FindString(key));
            TextCtrl1->SetValue(value);
            if (value!=_T("Other")) {
                TextCtrl1->SetEditable(FALSE);
            }
            return;
        }
    }
}

void dsl_dict_editorFrame::OnTextCtrl2TextEnter(wxCommandEvent& event)
{
    if (!TextCtrl2->IsEditable() || TextCtrl2->GetValue()==wxEmptyString || TextCtrl2->GetValue()==_T("Other")) {
        return;
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (value == TextCtrl2->GetValue()) {
            ComboBox2->SetSelection (ComboBox2->FindString(key));
            TextCtrl2->SetEditable(FALSE);
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (value.Lower().Matches(/*wxString(_T("*"))+*/TextCtrl2->GetValue().Lower()+_T("*"))) {
            ComboBox2->SetSelection (ComboBox2->FindString(key));
            TextCtrl2->SetValue(value);
            if (value!=_T("Other")) {
                TextCtrl2->SetEditable(FALSE);
            }
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (key == TextCtrl2->GetValue()) {
            ComboBox2->SetSelection (ComboBox2->FindString(key));
            TextCtrl2->SetValue(value);
            TextCtrl2->SetEditable(FALSE);
            return;
        }
    }
    for(map<wxString,wxString>::const_iterator iter = LangMap.begin(); iter != LangMap.end(); ++iter)
    {
        wxString key = iter->first;
        wxString value = iter->second;
        if (key.Lower().Matches(/*wxString(_T("*"))+*/TextCtrl2->GetValue().Lower()+_T("*"))) {
            ComboBox2->SetSelection (ComboBox2->FindString(key));
            TextCtrl2->SetValue(value);
            if (value!=_T("Other")) {
                TextCtrl2->SetEditable(FALSE);
            }
            return;
        }
    }
}

void dsl_dict_editorFrame::OnButton11Click(wxCommandEvent& event)
{
    wxString key = ComboBox4->GetValue();
    wxString value = WordsWithTranslation[key];
    if (key==wxEmptyString || value==wxEmptyString) {
        return;
    }
    wxString NewSourceWord = wxGetTextFromUser (_("input new source word here: "), _("new source word"));
    if (NewSourceWord == wxEmptyString) {
        return;
    }
    wxString old = WordsWithTranslation[NewSourceWord];
    if (old != wxEmptyString) {
        if (wxMessageBox(wxString(_("Replace old translation of '"))+NewSourceWord+_("'\n from \n'")+old+_("'\n to \n'")+value+_("'\n"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            return;
        }
    }
    WordsWithTranslation[NewSourceWord] = value;
    ComboBox4->Clear();
    ComboBox4->Append(key);
    ComboBox4->Append(NewSourceWord);
    ComboBox4->SetValue(NewSourceWord);
    TextCtrl4->SetValue(value);
    DictWasSaved = FALSE;
}

void dsl_dict_editorFrame::OnButton12Click(wxCommandEvent& event)
{
    TranslationPreview* preview = new TranslationPreview(this);
    preview->SetCardContent(TextCtrl4->GetValue());
    preview->Show();
}
