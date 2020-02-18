#include <Windows.h>
#include "Resource.h"
#include "gamestruct.h"

static void CustomGetNumber(int* threesome, TCHAR * buf, int length, int index);

INT_PTR CALLBACK CustomDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndEditH;
    static HWND hwndEditW;
    static HWND hwndEditM;
    static int* ptint;
    PGAMESTRUCT pgs;
    TCHAR buffer[20];
    int length;

    switch (message)
    {
    case WM_INITDIALOG:
        hwndEditH = GetDlgItem(hDlg, IDC_EDITH);
        hwndEditW = GetDlgItem(hDlg, IDC_EDITW);
        hwndEditM = GetDlgItem(hDlg, IDC_EDITM);
        pgs = GetPGS();
        //three argument
        _itow_s(pgs->icRow, buffer, 20, 10);
        SetWindowText(hwndEditH, buffer);
        _itow_s(pgs->icCol, buffer, 20, 10);
        SetWindowText(hwndEditW, buffer);
        _itow_s(pgs->icMines, buffer, 20, 10);
        SetWindowText(hwndEditM, buffer);

        //get the number array
        ptint = (PINT)lParam;

        //release pgs
        ReleasePGS(pgs);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            //deal with the input number
            //height
            *((PWORD)buffer) = 10;
            length = SendMessage(hwndEditH, EM_GETLINE, 0, (LPARAM)buffer);
            buffer[length] = TEXT('\0');
            CustomGetNumber(ptint, buffer, length, 0); //here use 0 to get height
            //width
            *((PWORD)buffer) = 10;
            buffer[length] = TEXT('\0');
            length = SendMessage(hwndEditW, EM_GETLINE, 0, (LPARAM)buffer);
            CustomGetNumber(ptint, buffer, length, 1); //here use 1 to get width
            //mines
            *((PWORD)buffer) = 10;
            length = SendMessage(hwndEditM, EM_GETLINE, 0, (LPARAM)buffer);
            buffer[length] = TEXT('\0');
            CustomGetNumber(ptint, buffer, length, 2); // 2

            //finish
            EndDialog(hDlg, 1);
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, 0);
        }
        break;
    }
    return FALSE;
}

//CustomGetNumber
void CustomGetNumber(int* threesome, TCHAR* buf, int length, int index)
{
    int i;
    int itemp;
    if (buf == NULL || threesome == NULL)
    {
        MessageBox(NULL, TEXT("null pointer"), TEXT("CustomGetNumber"), MB_ICONERROR);
        exit(0);
    }

    if (index == 0 || index == 1) //deal with height or width
    {
        if (iswdigit(buf[0])) //require digit
        {
            for (i = 0; i < length; i++)
            {
                if (!iswdigit(buf[i]))
                {
                    break;
                }
            }

            if (i < length) //not all digit i.e. error input
            {
                threesome[index] = 9; // the default value: 9
            }
            else
            {
                buf[length] = TEXT('\0');
                itemp = _wtoi(buf);
                if (index == 0) //height
                {
                    if (itemp < 9)
                    {
                        threesome[index] = 9;
                    }
                    else if (itemp > 30)
                    {
                        threesome[index] = 30;
                    }
                    else
                    {
                        threesome[index] = itemp;
                    }
                }
                else //width
                {
                    if (itemp < 9)
                    {
                        threesome[index] = 9;
                    }
                    else if (itemp > 24)
                    {
                        threesome[index] = 24;
                    }
                    else
                    {
                        threesome[index] = itemp;
                    }
                }
            }
        }
        else
        {
            threesome[index] = 9; //default value
        }
    }
    else
    {
        if (length == 0)
        {
            threesome[index] = 10; //no string; default value 10
            return;
        }
        for (i = 0; i < length; i++)
        {
            if (!iswdigit(buf[i]))
            {
                break;
            }
        }

        if (i < length) //not a number
        {
            threesome[index] = 10; //default mine value
        }
        else
        {
            buf[length] = TEXT('\0');
            itemp = _wtoi(buf);

            if (itemp < 10)
            {
                threesome[index] = itemp;
            }
            else //this situation depends on the row and col
            {
                if (itemp > (threesome[0] - 1)* (threesome[1] - 1))
                {
                    threesome[index] = (threesome[0] - 1) * (threesome[1] - 1);
                }
                else
                {
                    threesome[index] = itemp;
                }
            }
        }
    }
}