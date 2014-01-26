#include "TranslationPreview.h"

//(*InternalHeaders(TranslationPreview)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/regex.h>
#include <wx/msgdlg.h>
#include <wx/utils.h>

//(*IdInit(TranslationPreview)
const long TranslationPreview::ID_HTMLWINDOW1 = wxNewId();
const long TranslationPreview::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TranslationPreview,wxDialog)
	//(*EventTable(TranslationPreview)
	//*)
	EVT_HTML_LINK_CLICKED(ID_HTMLWINDOW1,TranslationPreview::OnLinkClick)
END_EVENT_TABLE()

TranslationPreview::TranslationPreview(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TranslationPreview)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetMinSize(wxSize(500,300));
	BoxSizer1->Add(HtmlWindow1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(Button1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TranslationPreview::OnButton1Click);
	//*)
}

TranslationPreview::~TranslationPreview()
{
	//(*Destroy(TranslationPreview)
	//*)
}

void TranslationPreview::OnButton1Click(wxCommandEvent& event)
{
    Destroy();
}

void TranslationPreview::SetCardContent(const wxString& ContentSource) {
    wxString Content = ContentSource;
    Content.Replace (_T("\n"), _T("<BR>"), TRUE);
    Content.Replace (_T("[url]"), _T("<A>"), TRUE); Content.Replace (_T("[/url]"), _T("</A>"), TRUE);
    if (Content.Matches(wxString(_T("*<<*>>*")))) {
        Content.Replace (_T("<<"), _T("<A>"), TRUE); Content.Replace (_T(">>"), _T("</A>"), TRUE); // TODO: remake with regexp
    }
    wxRegEx regex;
    regex.Compile(_T("<A>(([^<>])+)</A>"));
    while (regex.Matches(Content/*,wxRE_ICASE*/)) {
        wxString url = regex.GetMatch(Content,1);
        //wxMessageBox(url);
        regex.ReplaceFirst(&Content, wxString(_T("<A href=\""))+url+_T("\">")+url+_T("</A>"));
    }
    Content.Replace (_T("[b]"), _T("<B>"), TRUE); Content.Replace (_T("[/b]"), _T("</B>"), TRUE);
    Content.Replace (_T("[i]"), _T("<I>"), TRUE); Content.Replace (_T("[/i]"), _T("</I>"), TRUE);
    Content.Replace (_T("[u]"), _T("<U>"), TRUE); Content.Replace (_T("[/u]"), _T("</U>"), TRUE);
    regex.Compile(_T("\\[c ([^[:punct:]]+)\\]([^][]*)\\[/c\\]")); // "[^][]" means symbols not ']' or '['.
    while (regex.Matches(Content)) {
        wxString color = regex.GetMatch(Content,1);
        wxString text = regex.GetMatch(Content,2);
        //wxMessageBox(color+_T(" ")+text);
        regex.ReplaceFirst(&Content, wxString(_T("<FONT color=\""))+color+_T("\">")+text+_T("</FONT>"));
    }
    HtmlWindow1->SetPage(Content);
}

void TranslationPreview::OnLinkClick (wxHtmlLinkEvent& event) {
    wxString url = event.GetLinkInfo().GetHref();
    if (url.StartsWith(_T("http://")) || url.StartsWith(_T("https://"))) {
        wxLaunchDefaultBrowser(url);
    } else {
        event.Skip();
    }
}
