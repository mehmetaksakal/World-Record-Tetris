object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Tetris Field Controller'
  ClientHeight = 1024
  ClientWidth = 1280
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'basis33'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 19
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 500
    Height = 1000
    BevelEdges = []
    BevelOuter = bvNone
    BorderWidth = 1
    Caption = 'DrawPanel'
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 0
  end
  object RichEdit1: TRichEdit
    Left = 832
    Top = 0
    Width = 448
    Height = 1024
    Align = alRight
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'basis33'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
    Zoom = 100
  end
  object GroupBox1: TGroupBox
    Left = 514
    Top = 8
    Width = 312
    Height = 193
    Caption = 'Tetris Server'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Calibri Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Shape1: TShape
      Left = 14
      Top = 29
      Width = 22
      Height = 25
      Brush.Color = clRed
      Shape = stCircle
    end
    object Label1: TLabel
      Left = 49
      Top = 29
      Width = 136
      Height = 23
      Caption = 'Connection status'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 3
      Top = 63
      Width = 35
      Height = 23
      Caption = 'Host'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
    end
    object Button1: TButton
      Left = 2
      Top = 166
      Width = 308
      Height = 25
      Align = alBottom
      Caption = 'Connect'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object MaskEditIP: TMaskEdit
      Left = 51
      Top = 60
      Width = 258
      Height = 31
      Alignment = taCenter
      EditMask = '!099.099.099.099;1;'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      MaxLength = 15
      ParentFont = False
      TabOrder = 1
      Text = '127.0  .0  .1  '
    end
    object Button11: TButton
      Left = 2
      Top = 130
      Width = 308
      Height = 36
      Align = alBottom
      Caption = 'Send'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Button11Click
    end
    object Edit2: TEdit
      Left = 3
      Top = 96
      Width = 306
      Height = 31
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
  end
  object GroupBox2: TGroupBox
    Left = 514
    Top = 207
    Width = 312
    Height = 442
    Caption = 'Node Control'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Calibri Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Shape2: TShape
      Left = 14
      Top = 29
      Width = 22
      Height = 25
      Brush.Color = clRed
      Shape = stCircle
    end
    object Label3: TLabel
      Left = 49
      Top = 29
      Width = 128
      Height = 23
      Caption = 'Automatic Mode'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
    end
    object Button2: TButton
      Left = 3
      Top = 60
      Width = 306
      Height = 36
      Caption = 'Initialize All'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 3
      Top = 102
      Width = 306
      Height = 36
      Caption = 'Reset All'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 3
      Top = 144
      Width = 306
      Height = 36
      Caption = 'Reset Controller'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Button4Click
    end
    object Button7: TButton
      Left = 3
      Top = 186
      Width = 306
      Height = 36
      Caption = 'All Automatic'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = Button7Click
    end
    object Button9: TButton
      Left = 3
      Top = 228
      Width = 306
      Height = 36
      Caption = 'All Manual'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = Button9Click
    end
    object Button12: TButton
      Left = 3
      Top = 286
      Width = 150
      Height = 25
      Caption = 'Port 1 Off'
      TabOrder = 5
      OnClick = Button12Click
    end
    object Button13: TButton
      Left = 3
      Top = 317
      Width = 150
      Height = 25
      Caption = 'Port 2 Off'
      TabOrder = 6
      OnClick = Button13Click
    end
    object Button14: TButton
      Left = 3
      Top = 348
      Width = 150
      Height = 25
      Caption = 'Port 3 Off'
      TabOrder = 7
      OnClick = Button14Click
    end
    object Button15: TButton
      Left = 3
      Top = 379
      Width = 150
      Height = 25
      Caption = 'Port 4 Off'
      TabOrder = 8
      OnClick = Button15Click
    end
    object Button16: TButton
      Left = 3
      Top = 410
      Width = 150
      Height = 25
      Caption = 'Port 5 Off'
      TabOrder = 9
      OnClick = Button16Click
    end
    object Button17: TButton
      Left = 159
      Top = 286
      Width = 150
      Height = 25
      Caption = 'Port 1 On'
      TabOrder = 10
      OnClick = Button17Click
    end
    object Button18: TButton
      Left = 159
      Top = 317
      Width = 150
      Height = 25
      Caption = 'Port 2 On'
      TabOrder = 11
      OnClick = Button18Click
    end
    object Button19: TButton
      Left = 159
      Top = 348
      Width = 150
      Height = 25
      Caption = 'Port 3 On'
      TabOrder = 12
      OnClick = Button19Click
    end
    object Button20: TButton
      Left = 159
      Top = 379
      Width = 150
      Height = 25
      Caption = 'Port 4 On'
      TabOrder = 13
      OnClick = Button20Click
    end
    object Button21: TButton
      Left = 159
      Top = 410
      Width = 150
      Height = 25
      Caption = 'Port 5 On'
      TabOrder = 14
      OnClick = Button21Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 514
    Top = 655
    Width = 312
    Height = 353
    Caption = 'Manual Mode'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Calibri Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object Label2: TLabel
      Left = 3
      Top = 235
      Width = 47
      Height = 23
      Caption = 'Speed'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
    end
    object Button5: TButton
      Left = 3
      Top = 21
      Width = 306
      Height = 36
      Caption = 'Start Police'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 3
      Top = 63
      Width = 306
      Height = 36
      Caption = 'Start RGB'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = Button6Click
    end
    object TrackBar1: TTrackBar
      Left = 3
      Top = 189
      Width = 306
      Height = 48
      LineSize = 10
      Max = 2000
      Min = 100
      Frequency = 10
      Position = 100
      PositionToolTip = ptBottom
      TabOrder = 2
      OnChange = TrackBar1Change
    end
    object Edit1: TEdit
      Left = 72
      Top = 232
      Width = 237
      Height = 31
      Alignment = taRightJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      NumbersOnly = True
      ParentFont = False
      TabOrder = 3
      Text = '100'
      OnChange = Edit1Change
    end
    object Button8: TButton
      Left = 3
      Top = 105
      Width = 306
      Height = 36
      Caption = 'Start Running Lights'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = Button8Click
    end
    object Button10: TButton
      Left = 3
      Top = 147
      Width = 306
      Height = 36
      Caption = 'Start Random'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Calibri Light'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      StyleElements = []
      OnClick = Button10Click
    end
    object Button22: TButton
      Left = 3
      Top = 319
      Width = 306
      Height = 31
      Caption = 'All White'
      TabOrder = 6
      OnClick = Button22Click
    end
    object Button23: TButton
      Left = 3
      Top = 280
      Width = 306
      Height = 33
      Caption = 'All Black'
      TabOrder = 7
      OnClick = Button23Click
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 376
    Top = 8
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 376
    Top = 64
  end
  object UDPClient: TIdUDPClient
    BufferSize = 32786
    BoundIP = '0.0.0.0'
    BoundPort = 15000
    Host = '0.0.0.0'
    Port = 15000
    ReceiveTimeout = 1
    Left = 376
    Top = 128
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer3Timer
    Left = 376
    Top = 208
  end
end
