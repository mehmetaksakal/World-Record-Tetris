//---------------------------------------------------------------------------

#pragma hdrstop

#include "CDebugConsole.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

CDebugConsole::CDebugConsole(TRichEdit *RichEdit)
{
	this->RE = RichEdit;
	this->LineCounter = 0;
}

void CDebugConsole::WriteNotification(AnsiString txt)
{
	CHARFORMAT2 cfm2;
	cfm2.cbSize = sizeof(CHARFORMAT2);

	cfm2.cbSize = sizeof(cfm2);
	cfm2.dwMask = CFM_BACKCOLOR;
	cfm2.crBackColor = clLime;
	SendMessage(this->RE->Handle, EM_SETCHARFORMAT,
		static_cast<WPARAM>(SCF_SELECTION),
		reinterpret_cast<LPARAM>(&cfm2));

	RE->SelStart = RE->GetTextLen();
	RE->SelLength = 0;
	RE->SelAttributes->Name = "basis33";

	RE->SelText = (AnsiString(LineCounter) + " NFY: " + txt + "\r\n");
	RE->Font->Name = "basis33";
	this->LineCounter++;

	//RE->SetFocus();
	RE->SelStart = RE->GetTextLen();
	RE->Perform(EM_SCROLLCARET, 0, 0);
}

void CDebugConsole::WriteError(AnsiString txt)
{
	CHARFORMAT2 cfm2;
	cfm2.cbSize = sizeof(CHARFORMAT2);

	cfm2.cbSize = sizeof(cfm2);
	cfm2.dwMask = CFM_BACKCOLOR;
	cfm2.crBackColor = clRed;
	SendMessage(this->RE->Handle, EM_SETCHARFORMAT,
		static_cast<WPARAM>(SCF_SELECTION),
		reinterpret_cast<LPARAM>(&cfm2));

	RE->SelStart = RE->GetTextLen();
	RE->SelLength = 0;
	RE->SelAttributes->Name = "basis33";

	RE->SelText = (AnsiString(LineCounter) + " ERR: " + txt + "\r\n");
	this->LineCounter++;

	//RE->SetFocus();
	RE->SelStart = RE->GetTextLen();
	RE->Perform(EM_SCROLLCARET, 0, 0);
}

void CDebugConsole::WriteMessage(AnsiString txt)
{
	RE->SelText = (AnsiString(LineCounter) + " MSG: " + txt + "\r\n");
	this->LineCounter++;

	//RE->SetFocus();
	RE->SelStart = RE->GetTextLen();
	RE->Perform(EM_SCROLLCARET, 0, 0);
}
