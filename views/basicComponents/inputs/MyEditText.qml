import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {

	property string hint: "text input"
	property int echo_mode: TextInput.Normal
	property int input_type: Qt.ImhSensitiveData
	property string text_data: ""

	implicitWidth: textField.implicitWidth
	implicitHeight: textField.implicitHeight

	color: rootWindow.secondary_color
	border {
		color: rootWindow.primary_color
		width: rootWindow.wr < rootWindow.hr ? rootWindow.wr * 2 : rootWindow.hr * 2
	}
	radius: rootWindow.wr * 5

	TextField {
		id: textField
		placeholderText: qsTr(hint)
		inputMethodHints: input_type
		text: text_data
		selectByMouse: true
		selectionColor: primary_text_color
		selectedTextColor: secondary_text_color
		anchors.verticalCenter: parent.verticalCenter
		font.family: rootWindow.font.family
		font.pixelSize: rootWindow.pixel_font_size_24
		width: parent.width
		maximumLength: 90
//		validator: validator_prop
		placeholderTextColor: rootWindow.secondary_text_color
		background: Rectangle {
			anchors.fill: parent;
			color: rootWindow.transparent_color
		}
		color: rootWindow.primary_text_color
		echoMode: echo_mode

		onTextChanged: {
			text_data = text
		}

	}

}

/*##^##
Designer {
		D{i:0;formeditorZoom:6}
}
##^##*/
