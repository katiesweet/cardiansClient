#ifndef IMAGEINSERT_H
#define IMAGEINSERT_H

#include <wx/sizer.h>
#include <wx/wx.h>

class imageInsert : public wxPanel {
public:
  imageInsert(wxPanel *parent, const wxString file, wxBitmapType format,
              int maxHeight, int maxWidth);
  ~imageInsert();
  void paintEvent(wxPaintEvent &event);
  void paintNow();

private:
  wxBitmap theImage;
  DECLARE_EVENT_TABLE()
};

#endif

// https://forums.wxwidgets.org/viewtopic.php?t=3911
// This guide heavily influenced and guided me in producting a class we could
// use
// to add any image to our application.
