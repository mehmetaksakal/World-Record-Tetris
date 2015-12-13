//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NodeForm.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNode *FormNode;
//---------------------------------------------------------------------------
__fastcall TFormNode::TFormNode(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNode::FormShow(TObject *Sender)
{
	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormNode::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormNode::Timer1Timer(TObject *Sender)
{
	this->Edit1->Text = FormatFloat("0.#", Node->LowVoltage) + "v";

	if(Node->HighVoltage == true)
		this->Shape2->Brush->Color = clGreen;
	else
		this->Shape2->Brush->Color = clRed;

	if(Node->Present == true && Node->Connected == false)
		this->Shape1->Brush->Color = clYellow;
	else if(Node->Present == true && Node->Connected == true)
		this->Shape1->Brush->Color = clGreen;
	else
		this->Shape1->Brush->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TFormNode::Button3Click(TObject *Sender)
{
	//
	SerialCmdHandler->ResetNode(Node->devNum, Node->Node_ID);
}
//---------------------------------------------------------------------------
void __fastcall TFormNode::Button4Click(TObject *Sender)
{
	if(Node->Present)
		SerialCmdHandler->ConfigureNode(Node->devNum, Node->Node_ID);
}
//---------------------------------------------------------------------------
