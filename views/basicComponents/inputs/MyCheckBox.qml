import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0

CheckBox {

	property string cb_text: ""
	property string cb_text_col: rootWindow.primary_text_color
	property string cb_color: rootWindow.secondary_color
	property string cb_border_color: rootWindow.primary_color

	indicator: Rectangle {
		anchors.verticalCenter: parent.verticalCenter
		width: pixel_font_size_24 * 1.5
		height: pixel_font_size_24 * 1.5
		color: cb_color
		radius: parent.width
		border{
			color: cb_border_color
			width: pixel_font_size*2
		}
		Text {
			visible: parent.parent.checked
			text: qsTr("✔️");
			anchors.centerIn: parent
			color: primary_text_color;
			font: rootWindow.font
		}
	}
	contentItem: Text{
		text: qsTr(cb_text);
		font: parent.font;
		color: cb_text_col;
		leftPadding: parent.indicator.width + parent.spacing
		anchors.verticalCenter: parent.verticalCenter
	}
}
