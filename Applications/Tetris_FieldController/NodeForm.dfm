object FormNode: TFormNode
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Node control'
  ClientHeight = 220
  ClientWidth = 182
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 99
    Top = 142
    Width = 38
    Height = 41
    Brush.Color = clRed
  end
  object Shape2: TShape
    Left = 136
    Top = 142
    Width = 38
    Height = 41
    Brush.Color = clRed
  end
  object Button1: TButton
    Left = 8
    Top = 189
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
  object Button2: TButton
    Left = 99
    Top = 189
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 1
  end
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 8
    Width = 166
    Height = 73
    Caption = 'Control Type'
    TabOrder = 2
  end
  object RadioButton1: TRadioButton
    Left = 24
    Top = 32
    Width = 113
    Height = 17
    Caption = 'Automatic'
    TabOrder = 3
  end
  object RadioButton2: TRadioButton
    Left = 24
    Top = 55
    Width = 113
    Height = 17
    Caption = 'Manual'
    TabOrder = 4
  end
  object Button3: TButton
    Left = 8
    Top = 87
    Width = 166
    Height = 25
    Caption = 'Reset Node'
    ModalResult = 4
    TabOrder = 5
    OnClick = Button3Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 142
    Width = 75
    Height = 21
    TabOrder = 6
  end
  object Button4: TButton
    Left = 8
    Top = 111
    Width = 166
    Height = 25
    Caption = 'Initialize Node'
    TabOrder = 7
    OnClick = Button4Click
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 136
    Top = 24
  end
end
