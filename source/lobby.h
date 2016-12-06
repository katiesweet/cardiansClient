#ifndef lobby_H
#define lobby_H

#include "availableGames.h"
#include "clientInfo.h"
#include "imageInsert.h"
#include <sstream>
#include <string>
#include <wx/collpane.h>
#include <wx/listctrl.h>
#include <wx/wx.h>

class lobby : public wxPanel {
  clientInfo *screenInfo;
  availableGames *currentGames;
  void receivedMakeGameResponse(std::string, wxCommandEvent &);
  void receivedJoinGameResponse(std::string, wxCommandEvent &);
  void receivedStartGameResponse(std::string);
  void showGeneralDialogBox(std::string);
  wxButton *newGameBut;
  wxButton *joinGameBut;
  wxButton *startGameBut;

public:
  lobby(wxFrame *parent, wxString typeOfGame);
  ~lobby();
  wxString typeOfGame;
  void startGame(wxCommandEvent &);
  void joinGame(wxCommandEvent &);
  void makeGame(wxCommandEvent &);
  void receivedGames(std::string msg);
  void requestGames();
  void OnNewGame(wxCommandEvent &event);
  void OnPaint(wxPaintEvent &event) {
    wxPaintDC paintDC(this);
    paintDC.SetBrush(wxBrush(wxColour(90, 5, 18, wxALPHA_OPAQUE)));
    paintDC.SetPen(wxPen(wxColour(90, 5, 18, wxALPHA_OPAQUE)));
    paintDC.DrawRectangle(0, 0, 2500, 70);
    // paintDC.DrawRectangle(500,0,500,60);
  }

  enum { newGameButton = 1, joinGameButton = 2, startGameButton = 3 };

  wxDECLARE_EVENT_TABLE();
};
#endif
