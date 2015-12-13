//---------------------------------------------------------------------------

#ifndef CDebugConsoleH
#define CDebugConsoleH
#include <vcl.h>
//---------------------------------------------------------------------------

class CDebugConsole
{
	private:
		TRichEdit * RE;
		unsigned long LineCounter;
	public:
		CDebugConsole(TRichEdit *RichEdit);
		void WriteNotification(AnsiString txt);
		void WriteError(AnsiString txt);
		void WriteMessage(AnsiString txt);

};
#endif
