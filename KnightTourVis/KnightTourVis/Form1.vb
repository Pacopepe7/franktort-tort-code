


Public Class Form1
    'Define picturebox 'array'
    Dim pics As New List(Of PictureBox)
    Dim paths As New List(Of String)
    Dim currentpath
    Dim currentstep
    Dim pathcount
    Dim values(64)
    Dim notation() = {
         "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
         "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
         "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
         "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
         "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
         "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
         "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
         "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"}

    Private Function GetIndex(ByRef square As String)
        For x = 0 To 63
            If square.Contains(notation(x)) Then
                Return x
            End If
        Next
        Return -1
    End Function


    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        currentpath = 0
        currentstep = 0
        pathcount = 0
        For x = 0 To 63
            ' Create all picture boxes
            Dim PB As New PictureBox
            PB.Parent = Me
            pics.Add(PB)
            Dim XX = x Mod 8
            Dim YY = Int(x / 8)
            ' Setup boxes and load image
            pics(x).SizeMode = PictureBoxSizeMode.StretchImage
            pics(x).Size = New Size(60, 60)
            pics(x).Location = New Point(60 + (60 * XX), 500 - (60 * YY))
            Dim index As Integer = x Mod 2 + YY Mod 2
            If index = 2 Then
                index = 0
            End If
            values(x) = index
            pics(x).Image = ImageList1.Images.Item(index)

        Next (x)
        ParseFile()
        RichTextBox1.Text = "Path # " & currentpath + 1 & vbNewLine & paths(currentpath)

    End Sub

    Private Sub ParseFile()

        Dim fileReader As System.IO.StreamReader
        Dim line As String
        'fileReader = My.Computer.FileSystem.ReadAllText("C:\temp\KnightsTourShort.txt")
        ' fileReader = My.Computer.FileSystem.OpenTextFileReader("C:\temp\KnightsTourShort.txt")
        fileReader = My.Computer.FileSystem.OpenTextFileReader("C:\temp\KnightsTourShort.txt")
        While Not fileReader.EndOfStream


            line = fileReader.ReadLine()
            If line.Contains("path #") = True Then
                pathcount = pathcount + 1
            ElseIf line.Contains("a1, ") = True Then
                paths.Add(line)
                pathcount = pathcount + 1
            End If

        End While



    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If currentpath = pathcount - 1 Then
            Return
        End If
        currentpath = currentpath + 1
        RichTextBox1.Text = "Path # " & currentpath + 1 & vbNewLine & paths(currentpath)
        resetboard()
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        If currentpath = 0 Then
            Return
        End If
        currentpath = currentpath - 1
        RichTextBox1.Text = "Path # " & currentpath + 1 & vbNewLine & paths(currentpath)
        resetboard()

    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Timer1.Enabled = True
        currentstep = 0
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        'MsgBox("stepping")
        If currentstep * 4 > paths(currentpath).Length - 4 Then
            Return
        End If
        Dim sq = paths(currentpath).Substring(currentstep * 4, 3)
        Dim index = GetIndex(sq)
        pics(index).Image = ImageList1.Images.Item(values(index) + 2)
        currentstep = currentstep + 1

    End Sub
    Private Sub resetboard()
        Timer1.Enabled = False
        currentstep = 0
        For x = 0 To 63
            pics(x).Image = ImageList1.Images.Item(values(x))
        Next
    End Sub
End Class