#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>
#include <vector>

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  int cardWidth = 20;
  int cardHeight = 100;
  int cardBackType = 14;
  Card *dummyCard = new Card(HEARTS, TWO);
  int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  heightLeft -= 850;

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
      this, wxID_ANY, wxBitmap("../../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  playerCard *Deck = new playerCard(this->GetParent(), cardBackType, wxSize(100, 70),
      TRUE);

  playerCard *Discard = new playerCard(parent, dummyCard, wxSize(80, 120),cardBackType);

  for (int i = 0; i < 13; i++) {
    playerCard *card = new playerCard(parent, dummyCard, wxSize(70, 100),cardBackType);
    card->Raise();
    yourHand->Add(card);
    card->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent &event) {
      std::cout<<"Touched Card"<<std::endl;},wxID_ANY);
    handCards.push_back(card);
    if(i>=thePlayerHandSize){
      yourHand->Hide(i);
    }
  }

  playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
    wxSize(100, 70));
  playerOne->Add(card);
  for (int i = 0; i < 13; i++) {
    playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
      wxSize(100, 20),false);
    playerOne->Add(card);
    if(i>=playerOneHandSize){
      playerOne->Hide(i);
    }
  }

  playerCard *card1 = new playerCard(this->GetParent(), 3, cardBackType,
    wxSize(70, 100));
  playerTwo->Add(card1);
  for (int i = 0; i < 13; i++) {
    playerCard *card = new playerCard(this->GetParent(), 3, cardBackType,
      wxSize(20, 100), false);
    playerTwo->Add(card);
    if(i>=playerTwoHandSize){
      playerTwo->Hide(i);
    }
  }

  playerCard *card2 = new playerCard(this->GetParent(), 4, cardBackType,
    wxSize(100, 70));
  playerThree->Add(card2);
  for (int i = 0; i < 13; i++) {
    playerCard *card = new playerCard(this->GetParent(), 4, cardBackType,
      wxSize(100, 20), false);
    playerThree->Add(card);
    if(i>=playerThreeHandSize){
      playerThree->Hide(i);
    }
  }

  fieldArea->Add(Deck);
  fieldArea->Add(Discard);

  verticalfieldArea->AddSpacer(180);
  verticalfieldArea->Add(fieldArea);  //  Deck->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
  //    humanDrewCard();});
  verticalfieldArea->AddSpacer(180);

  upperPortion->Add(topLogo);
  upperPortion->AddSpacer(20);
  upperPortion->Add(playerTwo, wxALIGN_CENTRE_VERTICAL);
  upperPortion->AddSpacer(80);

  middlePortion->AddSpacer(20);
  middlePortion->Add(playerOne, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(270);
  middlePortion->Add(verticalfieldArea);
  middlePortion->AddSpacer(270);
  middlePortion->Add(playerThree, wxALIGN_BOTTOM);

  lowerPortion->AddSpacer(100);
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);
  SetSizerAndFit(theMainSizer);
}

void playArea::setDrewCardFunction(std::function<void()> f) {
  humanDrewCard = f;
}

void playArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void playArea::playerZero(std::vector<Card> hand) {
  yourHand->Show(this,false,true);
  yourHand->ShowItems(true);
  for(int i= hand.size() ; i< thePlayerHandSize; i++){
        yourHand->Hide(i);
  }
 yourHand->Layout();
 theMainSizer->Layout();
 this->Lower();
 this->Refresh();
}

void playArea::playerAi(int playerId, std::vector<Card> hand) {
  switch (playerId) {
  case 1:
      playerOne->Show(this,false,true);
    	playerOne->ShowItems(true);
    for(int i=0; i<13; i++){
      if(i>=hand.size()){
        playerOne->Hide(i);
      }
    }
    break;

  case 2:
    playerTwo->Show(this,false,true);
  	playerTwo->ShowItems(true);
    for(int i=0; i<13; i++){
      if(i>=hand.size()){
        playerTwo->Hide(i);
      }
    }
    break;

  case 3:
    playerThree->Show(this,false,true);
  	playerThree->ShowItems(true);
    for(int i=0; i<13; i++){
      if(i>=hand.size()){
        playerThree->Hide(i);
      }
    }
    break;
  }
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {
  int cardBackType = 14;
  switch (playerId) {
  case 0:
    playerZero(hand);
    break;
  case 1:
  case 2:
  case 3:
    playerAi(playerId, hand);
    std::cout<<"Computer Played" <<std::endl;
    break;
  }
  verticalfieldArea->Clear(true);
  fieldArea= new wxBoxSizer(wxHORIZONTAL);
  verticalfieldArea->AddSpacer(180);
  if(!deckEmpty){
    Deck = new playerCard(this->GetParent(), cardBackType, wxSize(80, 120),
        FALSE);
    Deck->Raise();
  }
  else{
    Deck = new playerCard(this->GetParent(), cardBackType, wxSize(80, 120));
    Deck->Raise();
  }
  Deck->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent &event) {
    std::cout<<"Drew Card"<<std::endl;
     humanDrewCard();},wxID_ANY);

  fieldArea->Add(Deck);
  Card *tempest =
      new Card(topOfDiscardPile.getSuit(), topOfDiscardPile.getValue());
  playerCard *Discard =
      new playerCard(this->GetParent(), tempest, wxSize(80, 120),14);
  fieldArea->Add(Discard);

  verticalfieldArea->Add(fieldArea);
  verticalfieldArea->AddSpacer(180);
  verticalfieldArea->Layout();
  middlePortion->Layout();
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
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
  dialog.ShowModal();
  int choice = dialog.GetSelection();
  return static_cast<Suit>(choice);
}

void playArea::aiPickedSuitDialog(Suit suitSpecified) {
  std::string msg = "The computer played an eight and have chosen the suit ";
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

void playArea::getCardPlayed(wxMouseEvent& event){
  // playerCard *cardSelected = wxDynamicCast(event.GetEventObject(),playerCard);
  // std::cout<<cardSelected<<std::endl;
  // humanMadeMove(Card(HEARTS,TWO));
  return;
}

void playArea::getDeckCard(wxMouseEvent& event){
  humanDrewCard();
}

playArea::~playArea() {}

// wxBEGIN_EVENT_TABLE (playArea, wxPanel)
//     EVT_MOUSE_EVENTS(playArea::getDeckCard)
// wxEND_EVENT_TABLE()

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
