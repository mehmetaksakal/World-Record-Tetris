//---------------------------------------------------------------------------

#pragma hdrstop

#include "CTetrisNode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

CTetrisNode::CTetrisNode(unsigned int Node_ID, unsigned int x, unsigned int y, TWinControl *Owner)
{
	this->MyOwner = Owner;
	this->x_pos = x;
	this->y_pos = y;
	this->id = Node_ID;
	this->tsize = 50;
	this->OnClick = NULL;
	this->connected = false;
	this->present = false;
	this->automatic = false;
	this->v12_level = 0;
	this->error_count = 0;

	Owner->DoubleBuffered = true;

	this->Cube1 = new TShape(NULL);
	this->Cube1->Visible = true;
	this->Cube1->Name = "Cube1_" + AnsiString(Node_ID);
	this->Cube1->Parent = Owner;
	this->Cube1->Shape = stSquare;
	this->Cube1->Height = tsize;
	this->Cube1->Width = tsize;
	this->Cube1->Left = 0 + x;
	this->Cube1->Top = 0 + y;
	this->Cube1->Brush->Color = clLtGray;
	this->Cube1->Show();
	this->Cube1->OnMouseDown = OnMouseDownCube1Handler;
	this->valCube1 = 0x00;

	this->Cube2 = new TShape(NULL);
	this->Cube2->Visible = true;
	this->Cube2->Name = "Cube2_" + AnsiString(Node_ID);
	this->Cube2->Parent = Owner;
	this->Cube2->Shape = stSquare;
	this->Cube2->Height = tsize;
	this->Cube2->Width = tsize;
	this->Cube2->Left = 0 + x;
	this->Cube2->Top = tsize + y;
	this->Cube2->Brush->Color = clLtGray;
	this->Cube2->Show();
	this->Cube2->OnMouseDown = OnMouseDownCube2Handler;
	this->valCube2 = 0x00;

	this->Cube3 = new TShape(NULL);
	this->Cube3->Visible = true;
	this->Cube3->Name = "Cube3_" + AnsiString(Node_ID);
	this->Cube3->Parent = Owner;
	this->Cube3->Shape = stSquare;
	this->Cube3->Height = tsize;
	this->Cube3->Width = tsize;
	this->Cube3->Left = tsize + x;
	this->Cube3->Top = 0 + y;
	this->Cube3->Brush->Color = clLtGray;
	this->Cube3->Show();
	this->Cube3->OnMouseDown = OnMouseDownCube3Handler;
	this->valCube3 = 0x00;

	this->Cube4 = new TShape(NULL);
	this->Cube4->Visible = true;
	this->Cube4->Name = "Cube4_" + AnsiString(Node_ID);
	this->Cube4->Parent = Owner;
	this->Cube4->Shape = stSquare;
	this->Cube4->Height = tsize;
	this->Cube4->Width = tsize;
	this->Cube4->Left = tsize + x;
	this->Cube4->Top = tsize + y;
	this->Cube4->Brush->Color = clLtGray;
	this->Cube4->Show();
	this->Cube4->OnMouseDown = OnMouseDownCube4Handler;
	this->valCube4 = 0x00;

	this->Controller = new TShape(NULL);
	this->Controller->Visible = true;
	this->Controller->Name = "Control_" + AnsiString(Node_ID);
	this->Controller->Parent = Owner;
	this->Controller->Shape = stSquare;
	this->Controller->Height = tsize;
	this->Controller->Width = tsize;
	this->Controller->Left = (tsize/2) + x;
	this->Controller->Top = (tsize/2)+ y;
	this->Controller->Brush->Color = clWhite;
	this->Controller->Show();

	this->Label12V = new TLabel(Owner);
	this->Label12V->Parent = Owner;
	this->Label12V->Name = "Label12V_" + AnsiString(Node_ID);
	this->Label12V->Caption = AnsiString(this->v12_level) + "v";
	this->Label12V->AutoSize = false;
	this->Label12V->Alignment = taCenter;
	this->Label12V->Font->Size = 16;
	//this->Label12V->Font->Style = TFontStyles() << fsBold << fsUnderline;
	this->Label12V->Height = tsize;
	this->Label12V->Width = tsize;
	this->Label12V->Left = (tsize/2)+x;
	this->Label12V->Top = (tsize/2)+y+16;
	this->Label12V->Show();

	this->LabelID = new TLabel(Owner);
	this->LabelID->Parent = Owner;
	this->LabelID->Name = "LabelID_" + AnsiString(Node_ID);
	this->LabelID->Caption = AnsiString(Node_ID);
	this->LabelID->AutoSize = false;
	this->LabelID->Alignment = taCenter;
	this->LabelID->Font->Size = 12;
	this->LabelID->Height = tsize;
	this->LabelID->Width = tsize;
	this->LabelID->Left = (tsize/2)+x;
	this->LabelID->Top = (tsize/2)+y;
	this->LabelID->Show();
	this->LabelID->OnClick = OnClickHandler;

	this->LED1 = new TShape(NULL);
	this->LED1->Visible = true;
	this->LED1->Name = "LED1_" + AnsiString(Node_ID);
	this->LED1->Parent = Owner;
	this->LED1->Shape = stCircle;
	this->LED1->Height = 10;
	this->LED1->Width = 10;
	this->LED1->Left = (tsize/2)+4 + x;
	this->LED1->Top = 28 + y;
	this->LED1->Brush->Color = clRed;
	this->LED1->Show();

	this->LED2 = new TShape(NULL);
	this->LED2->Visible = true;
	this->LED2->Name = "LED2_" + AnsiString(Node_ID);
	this->LED2->Parent = Owner;
	this->LED2->Shape = stCircle;
	this->LED2->Height = 10;
	this->LED2->Width = 10;
	this->LED2->Left = (tsize * 1.5)-14 + x;
	this->LED2->Top = 28 + y;
	this->LED2->Brush->Color = clRed;
	this->LED2->Show();

	this->LED3 = new TShape(NULL);
	this->LED3->Visible = true;
	this->LED3->Name = "LED3_" + AnsiString(Node_ID);
	this->LED3->Parent = Owner;
	this->LED3->Shape = stCircle;
	this->LED3->Height = 10;
	this->LED3->Width = 10;
	this->LED3->Left = tsize + x - 5;
	this->LED3->Top = tsize + 13 + y;
	this->LED3->Brush->Color = clRed;
	this->LED3->Show();
}

TColor CTetrisNode::Val2Color(char Value)
{
	TColor CubeColor;

	switch (Value)
	{
	case 0x00:
		CubeColor = clLtGray;
		break;

	case 0x01:
		CubeColor = clRed;
		break;

	case 0x02:
		CubeColor = clGreen;
		break;

	case 0x03:
		CubeColor = clYellow;
		break;

	case 0x04:
		CubeColor = clBlue;
		break;

	case 0x05:
		CubeColor = clPurple;
		break;

	case 0x06:
		CubeColor = clSkyBlue;
		break;

	case 0x07:
		CubeColor = clWhite;
		break;

	default:
		CubeColor = clBlack;
		break;
	}

	return CubeColor;
}

char CTetrisNode::Color2Val(TColor myColor)
{
	char Value;

	switch (myColor)
	{
	case clLtGray:
		Value = 0x00;
		break;

	case clRed:
		Value = 0x01;
		break;

	case clGreen:
		Value = 0x02;
		break;

	case clYellow:
		Value = 0x03;
		break;

	case clBlue:
		Value = 0x04;
		break;

	case clPurple:
		Value = 0x05;
		break;

	case clSkyBlue:
		Value = 0x06;
		break;

	case clWhite:
		Value = 0x07;
		break;

	default:
		Value = 0x00;
		break;
	}

	return Value;
}

