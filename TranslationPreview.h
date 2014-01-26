#ifndef TRANSLATIONPREVIEW_H
#define TRANSLATIONPREVIEW_H

//(*Headers(TranslationPreview)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
//*)

class TranslationPreview: public wxDialog
{
	public:

		TranslationPreview(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TranslationPreview();

		//(*Declarations(TranslationPreview)
		wxButton* Button1;
		wxHtmlWindow* HtmlWindow1;
		//*)

		void SetCardContent(const wxString& ContentSource);

	protected:

		//(*Identifiers(TranslationPreview)
		static const long ID_HTMLWINDOW1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(TranslationPreview)
		void OnButton1Click(wxCommandEvent& event);
		//*)
		void OnLinkClick (wxHtmlLinkEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
