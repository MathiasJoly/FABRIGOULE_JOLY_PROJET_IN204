#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef _LISEUSEAPP_H_
#define _LISEUSEAPP_H_

#define APP_NAME "Liseuse de Partition"

class LiseuseApp : public wxApp
{
public:
	virtual bool OnInit(); //OnInit = fonction main
};

#endif
