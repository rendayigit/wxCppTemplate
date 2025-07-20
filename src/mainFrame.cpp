#include "mainFrame.hpp"

#include <wx/defs.h>
#include <wx/textctrl.h>

constexpr int MAIN_WINDOW_SIZE_X = 450;
constexpr int MAIN_WINDOW_SIZE_Y = 340;

const char *HELLO_MESSAGE = "Hello from wxWidgets!";

// Main frame constructor
MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Template Wx Cpp GUI Application", wxDefaultPosition,
              wxSize(MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y)) {

  // Create menu bar
  auto *menuFile = new wxMenu;
  auto *helloMenuItem = menuFile->Append(wxID_ANY, "&Hello...\tCtrl-H", "Show hello dialog");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  auto *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  // Create status bar
  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");

  // Create main panel
  panel = new wxPanel(this, wxID_ANY);

  // Create a simple layout with a text control and button
  sizer = new wxBoxSizer(wxVERTICAL); // NOLINT(cppcoreguidelines-prefer-member-initializer)

  label = new wxStaticText(panel, wxID_ANY, HELLO_MESSAGE);
  sizer->Add(label, 0, wxALL | wxCENTER, wxSizerFlags::GetDefaultBorder());

  textCtrl = new wxTextCtrl(panel, wxID_ANY, HELLO_MESSAGE, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizer->Add(textCtrl, 1, wxALL | wxEXPAND, wxSizerFlags::GetDefaultBorder()); // NOLINT(bugprone-suspicious-enum-usage)

  button = new wxButton(panel, wxID_ANY, "Say Hello");
  sizer->Add(button, 0, wxALL | wxCENTER, wxSizerFlags::GetDefaultBorder());

  panel->SetSizer(sizer);

  Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::onAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainFrame::onHello, this, helloMenuItem->GetId());

  Bind(wxEVT_BUTTON, &MainFrame::onHello, this, button->GetId());
  textCtrl->Bind(wxEVT_CHAR, &MainFrame::updateLabelText, this);
}

void MainFrame::onExit(wxCommandEvent &event) {
  Close(true);
  event.Skip();
}

void MainFrame::onAbout(wxCommandEvent &event) { // NOLINT(readability-convert-member-functions-to-static)
  wxMessageBox(HELLO_MESSAGE, "About", wxOK | wxICON_INFORMATION); // NOLINT(hicpp-signed-bitwise)
  event.Skip();
}

void MainFrame::onHello(wxCommandEvent &event) { // NOLINT(readability-convert-member-functions-to-static)
  wxLogMessage(HELLO_MESSAGE);
  event.Skip();
}

void MainFrame::updateLabelText(wxKeyEvent &event) {
  label->SetLabel(textCtrl->GetValue());
  event.Skip();
}