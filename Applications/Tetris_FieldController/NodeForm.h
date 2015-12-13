//---------------------------------------------------------------------------

#ifndef NodeFormH
#define NodeFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "CSerialCmdHandler.h"
#include "CTetrisNode.h"
//---------------------------------------------------------------------------
class TFormNode : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TButton *Button3;
	TEdit *Edit1;
	TShape *Shape1;
	TShape *Shape2;
	TTimer *Timer1;
	TButton *Button4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormNode(TComponent* Owner);
	CSerialCmdHandler *SerialCmdHandler;
	CTetrisNode *Node;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNode *FormNode;
//---------------------------------------------------------------------------
#endif
