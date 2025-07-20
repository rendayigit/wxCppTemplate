#pragma once

#include <wx/wx.h>

// Main frame class
class MainFrame : public wxFrame {
public:
  MainFrame();

private:
  void onAbout(wxCommandEvent &event);
  void onExit(wxCommandEvent &event);

  void onHello(wxCommandEvent &event);
  void updateLabelText(wxKeyEvent& event);

  wxPanel *panel;
  wxBoxSizer *sizer;
  wxStaticText *label;
  wxTextCtrl *textCtrl;
  wxButton *button;
};
