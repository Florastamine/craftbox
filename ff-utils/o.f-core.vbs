Set objFSO = CreateObject("Scripting.FileSystemObject")
Set objFile = objFSO.CreateTextFile("o.f-coret",True)

Const ALL_FILES = "File video (Tat ca)"                  ' Also include all files
Set objDialog = CreateObject("UserAccounts.CommonDialog") ' Use the UserAccounts Common Dialog
Dim mfso : Set mfso = CreateObject("Scripting.FileSystemObject")
objDialog.Filter = ALL_FILES                  ' Apply the filename filters created above
objDialog.FilterIndex = 1                                 ' Default is first item in filter list
objDialog.InitialDir = "D:\"          ' Starting folder/directory

intResult = objDialog.ShowOpen

If intResult Then
objFile.WriteLine objDialog.FileName
End If