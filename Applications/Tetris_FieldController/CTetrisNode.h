//---------------------------------------------------------------------------

#ifndef CTetrisNodeH
#define CTetrisNodeH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------//

class CTetrisNode
{
	public:
		CTetrisNode(unsigned int Node_ID, unsigned int x, unsigned int y, TWinControl *Owner);

		__property unsigned int Node_ID = {read=GetNodeID, write=SetNodeID};
		__property bool Present = {read=GetPresent, write=SetPresent};
		__property bool Connected = {read=GetConnected, write=SetConnected};
		__property bool Automatic = {read=GetAutomatic, write=SetAutomatic};
		__property bool HighVoltage = {read=GetHV, write=SetHV};
		__property double LowVoltage = {read=Get12V, write=Set12V};

		__property TColor Cube1Color = {read=GetCube1, write=SetCube1};
		__property char Cube1Value = {read=GetCube1Value, write=SetCube1Value};
		__property TColor Cube2Color = {read=GetCube2, write=SetCube2};
		__property char Cube2Value = {read=GetCube2Value, write=SetCube2Value};
		__property TColor Cube3Color = {read=GetCube3, write=SetCube3};
		__property char Cube3Value = {read=GetCube3Value, write=SetCube3Value};
		__property TColor Cube4Color = {read=GetCube4, write=SetCube4};
		__property char Cube4Value = {read=GetCube4Value, write=SetCube4Value};

		__property TColor LED1Color = {read=GetLED1, write=SetLED1};
		__property TColor LED2Color = {read=GetLED2, write=SetLED2};
		__property TColor LED3Color = {read=GetLED3, write=SetLED3};

		inline void IncreaseErrorCount()
		{
			error_count++;

			if(this->error_count > 11)
			{
				present = false;
				connected = false;
			}
		}

		void ResetErrorCount()
		{
			error_count = 0;
		}



		void (__closure *OnClick)        (unsigned int);
		void (__closure *OnMouseDown)    (unsigned int, unsigned int);

		DWORD devNum;

	private:
		TShape *Cube1;
		TShape *Cube2;
		TShape *Cube3;
		TShape *Cube4;

		char valCube1;
		char valCube2;
		char valCube3;
		char valCube4;

		TShape *LED1;
		TShape *LED2;
		TShape *LED3;
		TShape *Controller;
		TLabel *LabelID;
		TLabel *Label12V;

		TWinControl *MyOwner;

		unsigned int x_pos;
		unsigned int y_pos;

		unsigned int tsize;;

		unsigned int id;
		bool present;
		bool connected;
		bool automatic;
		double v12_level;
		bool highvoltage;

		unsigned int error_count;

		TColor Val2Color(char Value);
		char Color2Val(TColor myColor);


		void SetCube1 (TColor myColor) {
			Cube1->Brush->Color = myColor;
			valCube1 = Color2Val(myColor);
		}

		TColor GetCube1( ) const {
				return Cube1->Brush->Color;
		}

		void SetCube1Value (char myColor) {
			valCube1 = myColor;
			Cube1->Brush->Color = Val2Color(myColor);
		}

		char GetCube1Value( ) const {
				return valCube1;
		}

		void SetCube2 (TColor myColor) {
			Cube2->Brush->Color = myColor;
			valCube2 = Color2Val(myColor);
		}

		TColor GetCube2( ) const {
				return Cube2->Brush->Color;
		}

		void SetCube2Value (char myColor) {
			valCube2 = myColor;
			Cube2->Brush->Color = Val2Color(myColor);
		}

		char GetCube2Value( ) const {
				return valCube2;
		}

		void SetCube3 (TColor myColor) {
			Cube3->Brush->Color = myColor;
			valCube3 = Color2Val(myColor);
		}

		TColor GetCube3( ) const {
				return Cube3->Brush->Color;
		}

		void SetCube3Value (char myColor) {
			valCube3 = myColor;
			Cube3->Brush->Color = Val2Color(myColor);
		}

		char GetCube3Value( ) const {
				return valCube3;
		}

		void SetCube4 (TColor myColor) {
			Cube4->Brush->Color = myColor;
			valCube4 = Color2Val(myColor);
		}

		TColor GetCube4( ) const {
				return Cube4->Brush->Color;
		}

		void SetCube4Value (char myColor) {
			valCube4 = myColor;
			Cube4->Brush->Color = Val2Color(myColor);
		}

		char GetCube4Value( ) const {
				return valCube4;
		}

		void SetLED1 (TColor myColor) {
			LED1->Brush->Color = myColor;
		}

		TColor GetLED1( ) const {
				return LED1->Brush->Color;
		}

		void SetLED2 (TColor myColor) {
			LED2->Brush->Color = myColor;
		}

		TColor GetLED2( ) const {
				return LED2->Brush->Color;
		}

		void SetLED3 (TColor myColor) {
			LED3->Brush->Color = myColor;
		}

		TColor GetLED3( ) const {
				return LED3->Brush->Color;
		}

		void SetNodeID (unsigned int ID ) {
			id = ID;
		}

		int GetNodeID( ) const {
				return id;
		}

		void SetPresent (bool state) {
			present = state;
			connected = false;

			if(state == true) LED1Color = clYellow;
			else LED1Color = clRed;
		}

		bool GetPresent() const {
				return present;
		}

		void SetAutomatic (bool state) {
			automatic = state;

			if(state)
			{
				LED3->Brush->Color = clGreen;
			}
			else
			{
				LED3->Brush->Color = clRed;
			}

		}

		bool GetAutomatic() const {
				return automatic;
		}

		void SetConnected (bool state) {
			connected = state;

			if(state == true) LED1Color = clGreen;
			else LED1Color = clRed;
		}

		bool GetConnected() const {
				return connected;
		}

		void SetHV (bool present) {
			highvoltage = present;

			if(present) LED2Color = clGreen;
			else LED2Color = clRed;
		}

		bool GetHV( ) const {
				return highvoltage;
		}

		void Set12V (double voltage) {
			v12_level = voltage;
			Label12V->Caption = FormatFloat("0.#", voltage) + "v";
		}

		double Get12V( ) const {
				return v12_level;
		}

		void __fastcall OnClickHandler(TObject *Sender)
		{
			if(OnClick != NULL)
				OnClick(id);


			return;
		}

		void __fastcall OnMouseDownCube1Handler(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
		{
			if(OnMouseDown != NULL)
				OnMouseDown(id, 1);


			return;
		}

		void __fastcall OnMouseDownCube2Handler(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
		{
			if(OnMouseDown != NULL)
				OnMouseDown(id, 2);


			return;
		}

		void __fastcall OnMouseDownCube3Handler(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
		{
			if(OnMouseDown != NULL)
				OnMouseDown(id, 3);


			return;
		}

		void __fastcall OnMouseDownCube4Handler(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
		{
			if(OnMouseDown != NULL)
				OnMouseDown(id, 4);


			return;
		}
};

//---------------------------------------------------------------------------//
#endif
