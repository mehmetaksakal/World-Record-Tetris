//---------------------------------------------------------------------------

#ifndef ColorFormH
#define ColorFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormColor : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
private:	// User declarations
public:		// User declarations
	__fastcall TFormColor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormColor *FormColor;
//---------------------------------------------------------------------------
#endif
