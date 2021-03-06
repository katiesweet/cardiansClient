#include "heartsArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>
#include <vector>

heartsArea::heartsArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = new clientInfo();
  setUpScreen(parent);
}

heartsArea::heartsArea(wxFrame *parent, clientInfo *client)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = client;
  setUpScreen(parent);
}

void heartsArea::setUpScreen(wxFrame *parent) {
  Card *dummyCard = new Card(HEARTS, TWO);
  int cardBackType = screenInfo->getcardBackType();

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 13;

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  leftFieldArea = new wxBoxSizer(wxVERTICAL);
  midFieldArea = new wxBoxSizer(wxVERTICAL);
  rightFieldArea = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *playerOneLabel = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerTwoLabel = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerThreeLabel = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *userLabel = new wxBoxSizer(wxHORIZONTAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);
  theMainSizer = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetLabel("topLogo");
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  wxStaticText *playerOneInfo = new wxStaticText(
      this->GetParent(), wxID_ANY, "Rocket\nRaccoon", wxDefaultPosition,
      wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  wxStaticText *playerTwoInfo = new wxStaticText(
      this->GetParent(), wxID_ANY, "Star Lord", wxDefaultPosition,
      wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  wxStaticText *playerThreeInfo =
      new wxStaticText(this->GetParent(), wxID_ANY, "Groot", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  wxStaticText *userInfo =
      new wxStaticText(this->GetParent(), wxID_ANY, "You", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  playerOneInfo->SetForegroundColour(wxColour(255, 255, 255));
  playerTwoInfo->SetForegroundColour(wxColour(255, 255, 255));
  playerThreeInfo->SetForegroundColour(wxColour(255, 255, 255));
  userInfo->SetForegroundColour(wxColour(255, 255, 255));

  playerOneLabel->Add(playerOneInfo);
  playerTwoLabel->Add(playerTwoInfo);
  playerThreeLabel->Add(playerThreeInfo);
  userLabel->Add(userInfo);

  playerCard *yourCard = new playerCard(
      this, dummyCard, screenInfo->getLargeCardSize(), cardBackType, TRUE);
  handCards.push_back(yourCard);
  yourHand->Add(yourCard);
  for (int i = 0; i < 13; i++) {
    playerCard *card = new playerCard(
        this, dummyCard, screenInfo->getSmallCardSize(), 14, FALSE);
    handCards.push_back(card);
    yourHand->Add(card);
    if (i >= thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }
  yourHand->ShowItems(false);

  playerCard *card1 = new playerCard(this, 2, cardBackType,
                                     screenInfo->getLargeHorCardSize(), TRUE);
  playerOne->Add(card1);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this, 2, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerOne->Add(card);
    if (i >= playerOneHandSize) {
      playerOne->Hide(i);
    }
  }

  playerCard *card2 = new playerCard(this, 3, cardBackType,
                                     screenInfo->getLargeCardSize(), TRUE);
  playerTwo->Add(card2);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this, 3, cardBackType,
                                      screenInfo->getSmallCardSize(), false);
    playerTwo->Add(card);
    if (i >= playerTwoHandSize) {
      playerTwo->Hide(i);
    }
  }

  playerCard *card3 = new playerCard(this->GetParent(), 4, cardBackType,
                                     screenInfo->getLargeHorCardSize(), TRUE);
  playerThree->Add(card3);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this, 4, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerThree->Add(card);
    if (i >= playerThreeHandSize) {
      playerThree->Hide(i);
    }
  }

  playerZeroChoice = new playerCard(this, 1, cardBackType,
                                    screenInfo->getLargeCardSize(), TRUE);
  playerOneChoice = new playerCard(this, 2, cardBackType,
                                   screenInfo->getLargeCardSize(), TRUE);
  playerTwoChoice = new playerCard(this, 3, cardBackType,
                                   screenInfo->getLargeCardSize(), TRUE);
  playerThreeChoice = new playerCard(this, 4, cardBackType,
                                     screenInfo->getLargeCardSize(), TRUE);

  leftFieldArea->AddSpacer(screenInfo->hSideVFieldSpacer());
  leftFieldArea->Add(playerOneChoice); //,
  //  wxALIGN_LEFT | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  leftFieldArea->AddSpacer(screenInfo->hSideVFieldSpacer());

  midFieldArea->Add(playerTwoChoice);
  // wxSizerFlags().ReserveSpaceEvenIfHidden());
  midFieldArea->AddSpacer(120);
  midFieldArea->Add(playerZeroChoice);
  // wxALIGN_LEFT | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  midFieldArea->AddSpacer(screenInfo->hSpaceBetweenCardAndHand());

  rightFieldArea->AddSpacer(screenInfo->hSideVFieldSpacer());
  rightFieldArea->Add(playerThreeChoice);
  // wxALIGN_LEFT | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  rightFieldArea->AddSpacer(screenInfo->hSideVFieldSpacer());

  fieldArea->Add(leftFieldArea);
  fieldArea->AddSpacer(screenInfo->hSideFieldSpacer());
  fieldArea->Add(midFieldArea);
  fieldArea->AddSpacer(screenInfo->hSideFieldSpacer());
  fieldArea->Add(rightFieldArea);

  wxBoxSizer *thisthing = new wxBoxSizer(wxVERTICAL);
  thisthing->Add(topLogo);
  thisthing->AddSpacer(20);
  thisthing->Add(playerOneLabel);

  upperPortion->Add(thisthing);
  upperPortion->AddSpacer(screenInfo->hSpaceBetweenCardAndHand());
  upperPortion->Add(playerTwoLabel);
  upperPortion->AddSpacer(10);
  upperPortion->Add(playerTwo);
  // wxALIGN_CENTRE_VERTICAL | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

  middlePortion->AddSpacer(screenInfo->hSpaceBetweenCardAndHand());
  // middlePortion->Add(playerOneLabel);
  // middlePortion->AddSpacer(10);
  middlePortion->Add(playerOne);
  //  wxALIGN_BOTTOM | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  middlePortion->AddSpacer(2 * screenInfo->hSpaceBetweenCardAndHand());
  middlePortion->Add(fieldArea);
  middlePortion->AddSpacer(2 * screenInfo->hSpaceBetweenCardAndHand());
  // middlePortion->Add(playerThreeLabel);

  middlePortion->Add(playerThree); //, wxALIGN_BOTTOM,
                                   //  wxRESERVE_SPACE_EVEN_IF_HIDDEN);
                                   // middlePortion->AddSpacer(10);

  middlePortion->Add(playerThreeLabel);

  lowerPortion->AddSpacer(screenInfo->c8LogoDifference());
  lowerPortion->Add(userLabel);
  lowerPortion->AddSpacer(10);
  lowerPortion->Add(yourHand); // wxRESERVE_SPACE_EVEN_IF_HIDDEN);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(screenInfo->hSpaceBetweenCardAndHand());
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);
  SetSizerAndFit(theMainSizer);
}

void heartsArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void heartsArea::playerZero(std::vector<Card> hand) {
  yourHand->Clear(true);
  handCards.clear();
  if (hand.size() > 0) {
    auto firstCard = hand.back();
    hand.pop_back();
    for (auto &&handCard : hand) {
      Card *temp = new Card(handCard.getSuit(), handCard.getValue());
      playerCard *card = new playerCard(
          this->GetParent(), temp, screenInfo->getSmallCardFront(), 14, false);
      card->setMoveFunction(humanMadeMove);
      handCards.push_back(card);
      yourHand->Add(card);
    }
    Card *temp = new Card(firstCard.getSuit(), firstCard.getValue());
    playerCard *card = new playerCard(this->GetParent(), temp,
                                      screenInfo->getCardFront(), 14, TRUE);
    card->setMoveFunction(humanMadeMove);
    handCards.push_back(card);
    yourHand->Add(card);
  }
  yourHand->Layout();
  theMainSizer->Layout();
}

void heartsArea::playerAi(int playerId, int handSize) {
  switch (playerId) {
  case 1:
    // playerOne->Show(this, false, true);
    playerOne->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= handSize) {
        playerOne->Hide(i);
      }
    }
    playerOne->Layout();
    leftFieldArea->Layout();
    break;

  case 2:
    // playerTwo->Show(this, false, true);
    playerTwo->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= handSize) {
        playerTwo->Hide(i);
      }
    }
    playerTwo->Layout();
    midFieldArea->Layout();
    break;
  case 3:
    // playerThree->Show(this, false, true);
    playerThree->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= handSize) {
        playerThree->Hide(i);
      }
    }
    playerThree->Layout();
    rightFieldArea->Layout();
    break;
  }
  fieldArea->Layout();
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
}

void heartsArea::initializePlayArea(std::vector<Card> hand) {
  std::cout << "initializePlayArea" << std::endl;
  int cardBackType = 14;
  playerZero(hand);
  playerAi(1, hand.size());
  playerAi(2, hand.size());
  playerAi(3, hand.size());
  playerZeroChoice->Hide();
  playerOneChoice->Hide();
  playerTwoChoice->Hide();
  playerThreeChoice->Hide();
  this->Refresh();
  this->Update();
}

void heartsArea::updateOnlinePlayArea(std::vector<Card> hand,
                                      std::vector<int> handSizes,
                                      std::vector<Card> field) {
  Freeze();
  playerZero(hand);
  for (int i = 0; i < 4; i++) {
    playerAi(i, handSizes.at(i));
  }
  updateMiddleCards(field);
  // updateFieldArea(FALSE, field.back(), FALSE);
  Thaw();
  Refresh();
  Update();
}

void heartsArea::updatePlayArea(int playerId, std::vector<Card> hand,
                                std::array<Card, 4> centerPile) {
  if (playerId == 0) {
    playerZero(hand);
  } else {
    playerAi(playerId, hand.size());
  }
  // updateMiddleCards(centerPile);
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
}

void heartsArea::updateMiddleCards(std::vector<Card> centerPile) {
  if (centerPile.at(0).getSuit() == UNDEFINED) {
    playerZeroChoice->Hide();
    std::cout << "Hasn't played" << std::endl;
  } else {
    playerZeroChoice->updateCard(centerPile.at(0), TRUE);
    playerZeroChoice->Show();
    playerZeroChoice->Layout();
  }

  if (centerPile.at(1).getSuit() == UNDEFINED) {
    playerOneChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerOneChoice->updateCard(centerPile.at(1), TRUE);
    std::cout << playerOneChoice->Show();
    playerOneChoice->Layout();
  }

  if (centerPile.at(2).getSuit() == UNDEFINED) {
    playerTwoChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerTwoChoice->updateCard(centerPile.at(2), TRUE);
    playerTwoChoice->Show();
    playerTwoChoice->Layout();
  }

  if (centerPile.at(3).getSuit() == UNDEFINED) {
    playerThreeChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerThreeChoice->Show();
    playerThreeChoice->updateCard(centerPile.at(3), TRUE);
    playerThreeChoice->Layout();
  }

  leftFieldArea->Layout();
  midFieldArea->Layout();
  rightFieldArea->Layout();
  fieldArea->Layout();
  theMainSizer->Layout();
  Refresh();
  Update();
}

std::vector<Card> heartsArea::requestCardsPassed(std::vector<Card> hand) {
  wxArrayString choices;
  std::vector<Card> selection;
  for (auto &&card : hand) {
    choices.Add(card.printCard());
  }
  wxString title("Pick 3 Cards to Pass");
  wxMultiChoiceDialog dialog(NULL, title, title, choices);
  auto yes = dialog.ShowModal();
  if (yes == wxID_OK) {
    auto choices = dialog.GetSelections();
    int numChoices = 0;
    for (auto &&c : choices) {
      std::cout << "Picked: " << hand[c].getValue() << " of "
                << hand[c].getSuit() << std::endl;
      selection.push_back(hand[c]);
      numChoices++;
    }
    if (numChoices == 3) {
      return selection;
    } else {
      return requestCardsPassed(hand);
    }
  } else {
    return requestCardsPassed(hand);
  }
}

void heartsArea::invalidMoveDialog() {
  wxMessageDialog dialog(NULL, "You played an invalid card. "
                               "Please try again.",
                         "Invalid Move", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

void heartsArea::brokenHeartsDialog() {
  wxMessageDialog dialog(NULL, "Hearts have been broken.", "Hearts Broken",
                         wxICON_EXCLAMATION);
  dialog.ShowModal();
}

void heartsArea::showLastTrick(std::vector<int> suitsPlayed,
                               std::vector<int> valuesPlayed, int winner,
                               bool brokenHearts) {
  std::vector<std::string> suitsStringPlayed = {"one", "two", "three", "four"};

  for (int i = 0; i < suitsPlayed.size(); i++) {
    if (suitsPlayed[i] == 0) {
      suitsStringPlayed[i] = "Hearts";
    } else if (suitsPlayed[i] == 1) {
      suitsStringPlayed[i] = "Spades";
    } else if (suitsPlayed[i] == 2) {
      suitsStringPlayed[i] = "Clubs";
    } else if (suitsPlayed[i] == 3) {
      suitsStringPlayed[i] = "Diamonds";
    }
  }
  std::string winnerString;
  switch (winner) {
  case 0:
    winnerString = "You";
    break;
  case 1:
    winnerString = "Rocket";
    break;
  case 2:
    winnerString = "Star Lord";
    break;
  case 3:
    winnerString = "Groot";
    break;
  }

  std::string msg = "Cards played last hand: \n\n";
  msg += "You:\t" + std::to_string(valuesPlayed[0]) + " of " +
         suitsStringPlayed[0] + "\n";
  msg += "Rocket Raccoon:\t" + std::to_string(valuesPlayed[1]) + " of " +
         suitsStringPlayed[1] + "\n";
  msg += "Star Lord:\t" + std::to_string(valuesPlayed[2]) + " of " +
         suitsStringPlayed[2] + "\n";
  msg += "Groot:\t" + std::to_string(valuesPlayed[3]) + " of " +
         suitsStringPlayed[3] + "\n\n";
  msg += winnerString + " took the trick!";
  if (brokenHearts) {
    msg += "\n\nHearts are broken!";
  }
  wxMessageDialog dialog(NULL, msg, "Last Trick", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

bool heartsArea::endOfRoundDialog(std::vector<int> playersRoundScores,
                                  std::vector<int> playersOverallScores) {
  std::string msg = "The round is over. Would you like to play again?\n\n";
  msg += "SCORES:\n";
  msg += "YOU:\t";
  msg += "Round Score: " + std::to_string(playersRoundScores[0]) + "\n";
  msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[0]);

  for (int i = 1; i < 4; i++) {
    msg += "\nAI " + std::to_string(i) + ":\t";
    msg += "Round Score: " + std::to_string(playersRoundScores[i]) + "\n";
    msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[i]);
  }

  wxMessageDialog dialog(NULL, msg, "Round Over", wxYES_NO);
  auto decision = dialog.ShowModal();
  if (decision == wxID_YES) {
    return true;
  } else {
    return false;
  }
}

bool heartsArea::endOfGameDialog(std::vector<int> playersRoundScores,
                                 std::vector<int> playersOverallScores) {
  std::string msg = "The Game is over! Here are the final scores:\n \n";
  msg += "SCORES:\n";
  msg += "YOU:\t";
  msg += "Round Score: " + std::to_string(playersRoundScores[0]) + "\n";
  msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[0]);

  for (int i = 1; i < 4; i++) {
    msg += "\nAI " + std::to_string(i) + ":\t";
    msg += "Round Score: " + std::to_string(playersRoundScores[i]) + "\n";
    msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[i]);
  }

  msg += "\n\nWould you like to play again?";

  wxMessageDialog dialog(NULL, msg, "Game Over", wxYES_NO);
  auto decision = dialog.ShowModal();
  if (decision == wxID_YES) {
    return true;
  } else {
    return false;
  }
}

void heartsArea::showGame() { theMainSizer->ShowItems(true); }

void heartsArea::hideGame() { theMainSizer->ShowItems(false); }

heartsArea::~heartsArea() {}

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
