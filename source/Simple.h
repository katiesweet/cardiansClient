#ifndef SIMPLE_H
#define SIMPLE_H

#include "GameLogic/CrazyEightsGame.hpp"
#include "GameLogic/HeartsGame.hpp"
#include "Networking/ClientNetworkInterface.hpp"
#include "OnlineGameLogic/CrazyEightsOnline.hpp"
#include "OnlineGameLogic/HeartsOnline.hpp"
#include "baseBackground.h"
#include "clientInfo.h"
#include "imageInsert.h"
#include "lobby.h"
#include "login.h"
#include "mainMenu.h"
#include "newUser.h"
#include "playArea.h"
#include <wx/wx.h>

class Simple : public wxFrame {
private:
  bool isConnected;

public:
  Simple(const wxString &title, clientInfo *theClientScreen);
  void switchPage(wxString buttonSwitch);
  io_service ioService;
  ClientNetworkInterface NI;
  wxBoxSizer *pageSizer;
  wxBoxSizer *backgroundSizer;

  login *loginPane;
  mainMenu *mainPane;
  wxButton *buttonText;
  newUser *newUserPane;
  CrazyEightsGame *eightsGame;
  HeartsGame *heartsGame;
  lobby *heartsLobby;
  lobby *eightsLobby;
  CrazyEightsOnline *eightsOnline;
  HeartsOnline *heartsOnline;
  clientInfo *screenInfo;
  void sendServerMsg(std::string);
  // void setServerReceivedMsgFunc(std::function<void(std::string)>);
  std::string getResponse();
};

#endif
