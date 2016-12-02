#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>
#include <vector>
#include <wx/notifmsg.h>

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = new clientInfo();
  int cardWidth = 20;
  int cardHeight = 100;
  cardBackType = 14;
  Card *dummyCard = new Card(HEARTS, TWO);
  maxHandSize = 31;

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 5;

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  verticalfieldArea = new wxBoxSizer(wxVERTICAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);
  theMainSizer = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      GetParent(), wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  Deck = new playerCard(GetParent(), cardBackType,
                        screenInfo->getLargeCardSize(), TRUE);
  Deck->setDrewCardFunction(humanDrewCard);
  Deck->Hide();

  Discard = new playerCard(parent, dummyCard, screenInfo->getLargeCardSize(),
                           cardBackType, TRUE);
  Discard->Hide();

  playerCard *yourCard =
      new playerCard(GetParent(), dummyCard, screenInfo->getLargeCardSize(),
                     cardBackType, TRUE);
  handCards.push_back(yourCard);
  yourHand->Add(yourCard);

  for (int i = 0; i < maxHandSize; i++) {
    playerCard *card = new playerCard(
        GetParent(), dummyCard, screenInfo->getSmallCardSize(), 14, FALSE);
    handCards.push_back(card);
    yourHand->Add(card);
    if (i >= thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }
  yourHand->ShowItems(false);

  playerCard *card = new playerCard(GetParent(), 2, cardBackType,
                                    screenInfo->getLargeHorCardSize());
  playerOne->Add(card, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(GetParent(), 2, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerOne->Add(card);
    if (i >= playerOneHandSize) {
      playerOne->Hide(i);
    }
  }
  playerOne->ShowItems(false);

  std::cout << "PlayerTwo Set Up" << std::endl;
  playerCard *card1 = new playerCard(GetParent(), 3, cardBackType,
                                     screenInfo->getLargeCardSize());
  playerTwo->Add(card1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(GetParent(), 3, cardBackType,
                                      screenInfo->getSmallCardSize(), false);
    playerTwo->Add(card);
    if (i >= playerTwoHandSize) {
      playerTwo->Hide(i);
    }
  }
  playerTwo->ShowItems(false);
  std::cout << "Player Two Done" << std::endl;

  playerCard *card2 = new playerCard(GetParent(), 4, cardBackType,
                                     screenInfo->getLargeHorCardSize());
  playerThree->Add(card2, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(GetParent(), 4, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerThree->Add(card);
    if (i >= playerThreeHandSize) {
      playerThree->Hide(i);
    }
  }
  playerThree->ShowItems(false);

  int temporary = screenInfo->c8middleVerSpace();

  fieldArea->Add(Deck);
  fieldArea->Add(Discard);

  verticalfieldArea->AddSpacer(screenInfo->c8middleVerSpace());
  verticalfieldArea->Add(fieldArea);
  verticalfieldArea->AddSpacer(screenInfo->c8middleVerSpace());

  upperPortion->Add(topLogo);
  upperPortion->AddSpacer(screenInfo->c8StrandardBorder()); //
  upperPortion->Add(playerTwo, wxALIGN_CENTRE_VERTICAL);

  middlePortion->AddSpacer(screenInfo->c8StrandardBorder()); //
  middlePortion->Add(playerOne, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(screenInfo->c8MiddleHorSpace());
  middlePortion->Add(verticalfieldArea);
  middlePortion->AddSpacer(screenInfo->c8MiddleHorSpace());
  middlePortion->Add(playerThree, wxALIGN_BOTTOM);

  lowerPortion->AddSpacer(screenInfo->c8LogoDifference()); //
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10); //
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20); //
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);
  SetSizerAndFit(theMainSizer);
  Hide();
}

void playArea::setDrewCardFunction(std::function<void()> f) {
  humanDrewCard = f;
}

void playArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void playArea::playerZero(std::vector<Card> hand) {
  yourHand->Clear(true);
  handCards.clear();
  if (hand.size() > 0) {
    auto firstCard = hand.back();
    hand.pop_back();
    for (auto &&handCard : hand) {
      Card *temp = new Card(handCard.getSuit(), handCard.getValue());
      playerCard *card = new playerCard(
          GetParent(), temp, screenInfo->getSmallCardFront(), 14, false);
      card->setMoveFunction(humanMadeMove);
      handCards.push_back(card);
      yourHand->Add(card);
    }
    Card *temp = new Card(firstCard.getSuit(), firstCard.getValue());
    playerCard *card =
        new playerCard(GetParent(), temp, screenInfo->getCardFront(), 14, TRUE);
    card->setMoveFunction(humanMadeMove);
    handCards.push_back(card);
    yourHand->Add(card);
  }
  yourHand->Layout();
  theMainSizer->Layout();
}

void playArea::playerAi(int playerId, int handSize) {
  std::cout << "Player " << playerId << " has " << handSize << " cards."
            << std::endl;
  switch (playerId) {
  case 1:
    updatePlayerOne(handSize);
    break;

  case 2:
    updatePlayerTwo(handSize);
    break;

  case 3:
    updatePlayerThree(handSize);
    break;
  }
  theMainSizer->Layout();
}

void playArea::updatePlayerOne(int handSize) {
  playerOne->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      // std::cout << "Hiding card number " << i << std::endl;
      playerOne->Hide(i);
    }
  }
  playerOne->Layout();
  // middlePortion->Layout();
}

void playArea::updatePlayerTwo(int handSize) {
  playerTwo->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      playerTwo->Hide(i);
    }
  }
  playerTwo->Layout();
}

void playArea::updatePlayerThree(int handSize) {
  playerThree->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      playerThree->Hide(i);
    }
  }
  playerThree->Layout();
}

void playArea::initializePlayArea(std::vector<Card> humanHand,
                                  Card topOfDiscardPile) {
  std::cout << "Creating area" << std::endl;
  Show();
  // Freeze();
  playerZero(humanHand);
  for (int i = 1; i < 4; i++) {
    playerAi(i, humanHand.size());
  }
  updateFieldArea(false, topOfDiscardPile, true);
  Refresh();
  Update();
  // Thaw();
}

// void playArea::OnFire

void playArea::dummyFunction() {
  std::cout << "dummy" << std::endl;
  wxWakeUpIdle();
  wxNotificationMessage *msg =
      new wxNotificationMessage("Dummy", "Blah", GetParent());
  // msg->ProcessPendingEvents();
  msg->Show(0.1);
  // Deck->Show();
  // Discard->Show();
  // GetParent()->Refresh();
  // GetParent()->Update();
  // Refresh();
  // Update();
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {
  GetParent()->Freeze();
  switch (playerId) {
  case 0:
    playerZero(hand);
    break;
  case 1:
  case 2:
  case 3:
    playerAi(playerId, hand.size());
    std::cout << "Computer Played" << std::endl;
    break;
  }
  updateFieldArea(deckEmpty, topOfDiscardPile, false);
  GetParent()->Thaw();
  GetParent()->Refresh();
  GetParent()->Update();
}

void playArea::updateFieldArea(bool deckEmpty, Card topOfDiscardPile,
                               bool initialize) {
  Deck->updateDeck(deckEmpty, screenInfo->getcardBackType());
  Deck->setDrewCardFunction(humanDrewCard);
  Discard->updateCard(topOfDiscardPile, TRUE);
  fieldArea->Show(true);
  fieldArea->Layout();
}

void playArea::invalidMoveDialog() {
  wxMessageDialog dialog(NULL, "You played an invalid card. You must match "
                               "either the suit or the value of the card at "
                               "the top of the discard pile. Please try again.",
                         "Invalid Move", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

Suit playArea::userPickSuitDialog() {
  wxArrayString choices;
  choices.Add("Hearts");
  choices.Add("Spades");
  choices.Add("Clubs");
  choices.Add("Diamonds");
  wxString title("Pick a Suit");
  wxSingleChoiceDialog dialog(NULL, title, title, choices);
  auto yes = dialog.ShowModal();
  if (yes == wxID_OK) {
    int choice = dialog.GetSelection();
    return static_cast<Suit>(choice);
  } else {
    return UNDEFINED;
  }
}

void playArea::aiPickedSuitDialog(Suit suitSpecified) {
  std::string msg = "The computer played an eight and has chosen the suit ";
  if (suitSpecified == HEARTS) {
    msg += "hearts.";
  } else if (suitSpecified == SPADES) {
    msg += "spades.";
  } else if (suitSpecified == CLUBS) {
    msg += "clubs.";
  } else {
    msg += "diamonds.";
  }
  wxMessageDialog dialog(NULL, msg, "Computer Played an Eight");
  dialog.ShowModal();
}

bool playArea::endOfRoundDialog(std::vector<int> playersRoundScores,
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

bool playArea::endOfGameDialog(std::vector<int> playersRoundScores,
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

void playArea::hideGame() { theMainSizer->Show(false); }

playArea::~playArea() {}

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
