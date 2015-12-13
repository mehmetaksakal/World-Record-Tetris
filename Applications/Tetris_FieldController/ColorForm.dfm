object FormColor: TFormColor
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Color'
  ClientHeight = 113
  ClientWidth = 170
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 89
    Top = 85
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 0
  end
  object Button2: TButton
    Left = 8
    Top = 85
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object CheckBox1: TCheckBox
    Left = 42
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Red'
    TabOrder = 2
  end
  object CheckBox2: TCheckBox
    Left = 42
    Top = 39
    Width = 97
    Height = 17
    Caption = 'Green'
    TabOrder = 3
  end
  object CheckBox3: TCheckBox
    Left = 42
    Top = 62
    Width = 97
    Height = 17
    Caption = 'Blue'
    TabOrder = 4
  end
end
