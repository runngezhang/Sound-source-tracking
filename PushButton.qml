import QtQuick 1.1

QPushButton
{
    color: rgb(255, 255, 255);
    background-color: rgb(167, 205, 255);
    border:none;
    padding: 3px;
    font-family: "Verdana";
    font-size: 15px;
    text-align: center;
}
QPushButton:hover, QPushButton:pressed , QPushButton:checked
{
    background-color: rgb(85, 170, 255);
    text-align: right;
    padding-right: 20px;
    font-weight:100
}
QPushButton:hover
{
    background-repeat:no-repeat;
    background-position: center left;
}
QPushButton:pressed, QPushButton:checked
{
    background-repeat:no-repeat;
    background-position: center left;
}
