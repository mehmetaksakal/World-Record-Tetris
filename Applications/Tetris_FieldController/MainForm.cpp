//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ColorForm.h"
#include "NodeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

static uint8_t FontData[140] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00,
	0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

//---------------------------------------------------------------------------
void TFormMain::OnClickHandler(unsigned int Node_ID)
{
		FormNode->SerialCmdHandler = this->SerialCmdHandler;
		FormNode->Node = tnode[Node_ID - 1];

		if(tnode[Node_ID - 1]->Automatic)
			FormNode->RadioButton1->Checked = true;
		else
			FormNode->RadioButton2->Checked = true;

		if(FormNode->ShowModal() == mrOk)
		{
			tnode[Node_ID - 1]->Automatic = FormNode->RadioButton1->Checked;

			if(FormNode->RadioButton1->Checked)
				this->Shape2->Brush->Color = clGreen;
			else
				this->Shape2->Brush->Color = clRed;
		}
}

void TFormMain::OnMouseDownHandler(unsigned int Node_ID, unsigned int LED_ID)
{
	char Value;
	Value = 0x00;

	FormColor->CheckBox1->Checked = false;
	FormColor->CheckBox2->Checked = false;
	FormColor->CheckBox3->Checked = false;

	if(FormColor->ShowModal() == mrOk)
	{
		if(FormColor->CheckBox1->Checked)
		{
            Value = Value | 0x01;
		}

		if(FormColor->CheckBox2->Checked)
		{
			Value = Value | 0x02;
		}

		if(FormColor->CheckBox3->Checked)
		{
            Value = Value | 0x04;
		}

		SerialCmdHandler->WriteLed(tnode[Node_ID]->devNum, Node_ID, LED_ID, Value);
    }
}
//---------------------------------------------------------------------------
void TFormMain::DrawField()
{
	Panel1->Caption = "";
	Panel1->Height = 1000;
	Panel1->Width = 500;

	for(int i = 0; i < 10; i++)
	{
		tnode[i] = new CTetrisNode(i + 1, 0, i*100, Panel1);
		tnode[i]->OnClick = &(OnClickHandler);
		tnode[i]->OnMouseDown = &(OnMouseDownHandler);
	}

	for(int i = 10; i < 20; i++)
	{
		tnode[i] = new CTetrisNode(i + 1, 100, (i-10)*100, Panel1);
		tnode[i]->OnClick = &(OnClickHandler);
		tnode[i]->OnMouseDown = &(OnMouseDownHandler);
	}

	for(int i = 20; i < 30; i++)
	{
		tnode[i] = new CTetrisNode(i + 1, 200, (i-20)*100, Panel1);
		tnode[i]->OnClick = &(OnClickHandler);
		tnode[i]->OnMouseDown = &(OnMouseDownHandler);
	}

	for(int i = 30; i < 40; i++)
	{
		tnode[i] = new CTetrisNode(i + 1, 300, (i-30)*100, Panel1);
		tnode[i]->OnClick = &(OnClickHandler);
		tnode[i]->OnMouseDown = &(OnMouseDownHandler);
	}

	for(int i = 40; i < 50; i++)
	{
		tnode[i] = new CTetrisNode(i + 1, 400, (i-40)*100, Panel1);
		tnode[i]->OnClick = &(OnClickHandler);
		tnode[i]->OnMouseDown = &(OnMouseDownHandler);
	}
}

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	int MonitorTop, MonitorLeft, MonitorWidth, MonitorHeight;

	Application->OnException = AppException;

	LED1 = 0x00;
	LED2 = 0x00;
	ManualMode = 0x00;
	TrackBar1->Position = 800;
	this->AutomaticMode = false;
	this->UDPClient->Active = false;

	this->SerialSem =  new TLightweightSemaphore(1, 1 /* Max. Count */);

	this->Port1 = 0;
	this->Port2 = 1;
	this->Port3 = 2;
	this->Port4 = 3;
	this->Port5 = 4;


    // Send FormMain to second monitor if present
	if (Screen->MonitorCount > 1) {
		MonitorTop = Screen->Monitors[1]->Top;
		MonitorLeft = Screen->Monitors[1]->Left;
		MonitorWidth = Screen->Monitors[1]->Width;
		MonitorHeight = MonitorTop + Screen->Monitors[1]->Height;
		MonitorWidth = MonitorLeft + Screen->Monitors[1]->Width;

		FormMain->Top = MonitorTop;
		FormMain->Left = MonitorLeft;
		FormMain->Height = MonitorHeight;
		FormMain->Width = MonitorWidth;
		FormMain->BorderStyle = bsNone;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	DrawField();
	DebugConsole = new CDebugConsole(this->RichEdit1);
	DebugConsole->WriteNotification("DEBUG CONSOLE ACTIVE");
	Serial = new CSerial(DebugConsole, SerialSem);
	Serial->Run();
	SerialCmdHandler = new CSerialCmdHandler(DebugConsole, Serial, tnode, SerialSem);
	SerialCmdHandler->Run();
	NetworkServices = new CNetworkServices(SerialCmdHandler, tnode, this->UDPClient);
	NetworkServices->Run();

	this->ServerConnected = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject *Sender)
{
	if(UDPClient->Connected())
	{
		Button1->Caption = "Connect";
		//UDPClient->Disconnect();
		UDPClient->Active = false;
	}
	else
	{
		//IdTelnet1->Connect();
		Button1->Caption = "Disconnect";
		UDPClient->Host = this->MaskEditIP->Text;
		UDPClient->Active = true;
		//UDPClient->Connect();
	}

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	if(this->UDPClient->Connected())
	{
		this->UDPClient->Disconnect();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AppException(TObject *Sender, Exception *E)
{
	this->DebugConsole->WriteError(AnsiString(E->ClassName()) + E->Message);
	if(UDPClient->Connected())
		this->UDPClientDisconnected(NULL);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
	for(int i = 0; i < 50; i++)
	{
		if(tnode[i]->Present == true)
		{
			SerialCmdHandler->ReadHighVoltage(tnode[i]->devNum, i+1);
			SerialCmdHandler->ReadLowVoltage(tnode[i]->devNum, i+1);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button4Click(TObject *Sender)
{
	SerialCmdHandler->ResetController(0);
	SerialCmdHandler->ResetController(1);
	SerialCmdHandler->ResetController(2);
	SerialCmdHandler->ResetController(3);
	SerialCmdHandler->ResetController(4);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button2Click(TObject *Sender)
{
/*	unsigned int i;
	i = 0;

	for(i = 0; i < 50; i++)
	{
		if(tnode[i]->Present == true)
		{
			SerialCmdHandler->ConfigureNode(tnode[i]->devNum, i+1);
		}
	}*/
	unsigned char data;
	unsigned int x, y;
	unsigned char node, led;

	for(y = 1; y < 20; y++)
	{
		for(x = 1; x < 8; x++)
		{
			data = FontData[y*7 + x];
			//SerialCmdHandler->WriteLed()
			NetworkServices->XY2NodeLed(x+3, y, node, led);

			SerialCmdHandler->WriteLed(tnode[node]->devNum, (DWORD)node, (char)led, data);
        }
	}

	this->Timer3->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer2Timer(TObject *Sender)
{
	char tmpLED;

	if(ManualMode != MODE_RUNNING)
	{
		for(unsigned int i = 0; i < 50; i++)
		{
			if(tnode[i]->Present == true)
			{
				if(ManualMode == MODE_RANDOM)
				{
					LED1 = random(7)+1;
					LED2 = random(7)+1;
					LED3 = random(7)+1;
					LED4 = random(7)+1;
				}

				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, LED4);
			}
		}
	} else {
		for(int i = 9; i > -1; i--)
		{
			if(i == 0)
			{
				LED2 = tnode[i]->Cube1Value;
				LED4 = tnode[i]->Cube3Value;

				LED1 = tnode[i]->Cube1Value + 1;
				LED3 = tnode[i]->Cube3Value + 1;

				if(LED1 == 0x08) LED1 = 0x01;
				if(LED3 == 0x08) LED3 = 0x01;
			} else {
				LED2 = tnode[i]->Cube1Value;
				LED4 = tnode[i]->Cube3Value;

				LED1 = tnode[i-1]->Cube2Value;
				LED3 = tnode[i-1]->Cube4Value;
			}

			if(tnode[i]->Present == true)
			{
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, LED4);
			}

			if(tnode[i+10]->Present == true)
			{
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+11, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+11, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+11, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+11, 4, LED4);
			}

			if(tnode[i+20]->Present == true)
			{
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+21, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+21, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+21, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+21, 4, LED4);
			}

			if(tnode[i+30]->Present == true)
			{
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+31, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+31, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+31, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+31, 4, LED4);
			}

			if(tnode[i+40]->Present == true)
			{
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+41, 1, LED1);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+41, 2, LED2);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+41, 3, LED3);
				SerialCmdHandler->WriteLed(tnode[i]->devNum, i+41, 4, LED4);
			}
		}
    }

	switch(ManualMode)
	{
		case MODE_POLICE:
			tmpLED = LED1;
			LED1 = LED3;
			LED3 = tmpLED;

			tmpLED = LED2;
			LED2 = LED4;
			LED4 = tmpLED;
			break;

		case MODE_RGB:
			if(LED1 == 0x01)
				tmpLED = 0x02;
			else if(LED1 == 0x02)
				tmpLED = 0x04;
			else if(LED1 == 0x04)
				tmpLED = 0x01;
			else
				tmpLED = 0x01;

			LED1 = tmpLED;
			LED2 = tmpLED;
			LED3 = tmpLED;
			LED4 = tmpLED;
			break;

		case MODE_RUNNING:
			break;

		case MODE_RANDOM:
			break;

		default:
			break;

	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button5Click(TObject *Sender)
{
	LED1 = 0x01;
	LED2 = 0x01;
	LED3 = 0x04;
	LED4 = 0x04;

	TrackBar1->Position = 700;
	this->AutomaticMode = true;

	ManualMode = MODE_POLICE;

	if(Timer2->Enabled)
	{
		Timer2->Enabled = false;
		Button5->Caption = "Start Police";
	}
	else
	{
		Timer2->Enabled = true;
		Button5->Caption = "Stop Police";
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::Button3Click(TObject *Sender)
{
	unsigned int i;
	i = 0;

	for(i = 0; i < 50; i++)
	{
		//if(tnode[i]->Present)
		//{
			SerialCmdHandler->ResetNode(tnode[i]->devNum, i+1);
        //}
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button6Click(TObject *Sender)
{
	LED1 = 0x01;
	LED2 = 0x01;
	LED3 = 0x01;
	LED4 = 0x01;

	ManualMode = MODE_RGB;
	TrackBar1->Position = 700;
	this->AutomaticMode = false;

	if(Timer2->Enabled)
	{
		Timer2->Enabled = false;
		Button6->Caption = "Start RGB";
	}
	else
	{
		Timer2->Enabled = true;
		Button6->Caption = "Stop RGB";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TrackBar1Change(TObject *Sender)
{
	Edit1->Text = TrackBar1->Position;
	Timer2->Interval = TrackBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit1Change(TObject *Sender)
{
	TrackBar1->Position = Edit1->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button7Click(TObject *Sender)
{
	unsigned int i;
	i = 0;

	ManualMode = MODE_AUTO;
	this->AutomaticMode = true;
	this->Shape2->Brush->Color = clGreen;

	for(i = 0; i < 50; i++)
	{
		if(tnode[i]->Present)
		{
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, 0x00);

		}

		tnode[i]->Automatic = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button9Click(TObject *Sender)
{
	unsigned int i;
	i = 0;

	ManualMode = MODE_AUTO;
	this->AutomaticMode = true;
	this->Shape2->Brush->Color = clRed;

	for(i = 0; i < 50; i++)
	{
		if(tnode[i]->Present)
		{
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, 0x00);

		}

		tnode[i]->Automatic = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button8Click(TObject *Sender)
{
	LED1 = 0x01;
	LED2 = 0x01;
	LED3 = 0x01;
	LED4 = 0x01;

	ManualMode = MODE_RUNNING;
	TrackBar1->Position = 700;
	this->AutomaticMode = false;

	if(Timer2->Enabled)
	{
		Timer2->Enabled = false;
		Button8->Caption = "Start Running Lights";
	}
	else
	{
		Timer2->Enabled = true;
		Button8->Caption = "Stop Running Lights";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button10Click(TObject *Sender)
{
	LED1 = 0x01;
	LED2 = 0x01;
	LED3 = 0x01;
	LED4 = 0x01;

	ManualMode = MODE_RANDOM;
	TrackBar1->Position = 700;
	this->AutomaticMode = false;
	srand(time(NULL));

	if(Timer2->Enabled)
	{
		Timer2->Enabled = false;
		Button10->Caption = "Start Random";
	}
	else
	{
		Timer2->Enabled = true;
		Button10->Caption = "Stop Random";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UDPClientConnected(TObject *Sender)
{
	this->Button1->Caption = "Disconnect";
	this->ServerConnected = true;
	this->Shape1->Brush->Color = clGreen;
	DebugConsole->WriteNotification("Connected to Tetris server");
	Button11->Enabled = true;
	Edit2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UDPClientDisconnected(TObject *Sender)
{
	this->Button1->Caption = "Connect";
	this->ServerConnected = false;
	this->Shape1->Brush->Color = clRed;
	DebugConsole->WriteNotification("Disconnected from Tetris server");
	Button11->Enabled = false;
	Edit2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button11Click(TObject *Sender)
{
//
	UDPClient->Send(this->Edit2->Text);
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::Button12Click(TObject *Sender)
{
	DWORD Port = 0;

	for(unsigned int i = 0; i < 10; i++)
	{
		if(this->tnode[i]->Present)
		{
			Port = this->tnode[i]->devNum;
			this->tnode[i]->Present = false;
			this->Port1 = Port;
		}
	}

	this->SerialCmdHandler->HardOff(Port);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button13Click(TObject *Sender)
{
	DWORD Port = 1;

	for(unsigned int i = 10; i < 20; i++)
	{
		if(this->tnode[i]->Present)
		{
			Port = this->tnode[i]->devNum;
			this->tnode[i]->Present = false;
			this->Port2 = Port;
		}
	}

	this->SerialCmdHandler->HardOff(Port);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button14Click(TObject *Sender)
{
	DWORD Port = 2;

	for(unsigned int i = 20; i < 30; i++)
	{
		if(this->tnode[i]->Present)
		{
			Port = this->tnode[i]->devNum;
			this->tnode[i]->Present = false;
			this->Port3 = Port;
		}
	}

	this->SerialCmdHandler->HardOff(Port);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button15Click(TObject *Sender)
{
	DWORD Port = 3;

	for(unsigned int i = 30; i < 40; i++)
	{
		if(this->tnode[i]->Present)
		{
			Port = this->tnode[i]->devNum;
			this->tnode[i]->Present = false;
			this->Port4 = Port;
		}
	}

	this->SerialCmdHandler->HardOff(Port);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button16Click(TObject *Sender)
{
	DWORD Port = 4;

	for(unsigned int i = 40; i < 50; i++)
	{
		if(this->tnode[i]->Present)
		{
			Port = this->tnode[i]->devNum;
			this->tnode[i]->Present = false;
			this->Port5 = Port;
		}
	}

	this->SerialCmdHandler->HardOff(Port);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button17Click(TObject *Sender)
{
	this->SerialCmdHandler->HardOn(Port1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button18Click(TObject *Sender)
{
	this->SerialCmdHandler->HardOn(Port2);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button19Click(TObject *Sender)
{
	this->SerialCmdHandler->HardOn(Port3);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button20Click(TObject *Sender)
{
	this->SerialCmdHandler->HardOn(Port4);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button21Click(TObject *Sender)
{
	this->SerialCmdHandler->HardOn(Port5);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button23Click(TObject *Sender)
{
	unsigned int i;
	i = 0;

	for(i = 0; i < 50; i++)
	{
		if(tnode[i]->Present == true)
		{
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, 0x00);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, 0x00);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button22Click(TObject *Sender)
{
	unsigned int i;
	i = 0;

	for(i = 0; i < 50; i++)
	{
		if(tnode[i]->Present == true)
		{
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 1, 0x07);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 2, 0x07);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 3, 0x07);
			SerialCmdHandler->WriteLed(tnode[i]->devNum, i+1, 4, 0x07);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer3Timer(TObject *Sender)
{
	unsigned int x;

	for(x = 0; x < 50; x++)
	{
		if(tnode[x]->Cube1Value == 0x00)
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 1, 0x07);
		else
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 1, 0x00);

		if(tnode[x]->Cube2Value == 0x00)
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 2, 0x07);
		else
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 2, 0x00);

		if(tnode[x]->Cube3Value == 0x00)
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 3, 0x07);
		else
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 3, 0x00);

		if(tnode[x]->Cube4Value == 0x00)
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 4, 0x07);
		else
			this->SerialCmdHandler->WriteLed(tnode[x]->devNum, tnode[x]->Node_ID, 4, 0x00);
    }
}
//---------------------------------------------------------------------------

