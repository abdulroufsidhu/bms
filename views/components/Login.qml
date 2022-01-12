import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import "../basicComponents/buttons"
import "../basicComponents/inputs"

Rectangle {
	color: rootWindow.secondary_color
	implicitHeight: auth_rect.implicitHeight
	implicitWidth: auth_rect.implicitWidth
	Rectangle {
		id: auth_rect
		implicitHeight: login_form_column_positioner.implicitHeight + rootWindow.wr*60
		implicitWidth: login_form_column_positioner.implicitWidth + rootWindow.wr*60
		anchors.centerIn: parent
		color: rootWindow.secondary_color
		radius: 20

		Column {
			id: login_form_column_positioner
			spacing: 10
			anchors {
				fill: parent
				margins: rootWindow.wr * 30
			}

			MyEditText{
				hint: "email@example.com";
				width: 17*rootWindow.pixel_font_size_24
			}
			MyEditText{
				hint: "Password";
				echo_mode: TextInput.Password;
				width: 17*rootWindow.pixel_font_size_24
			}
			MyButton{
				btn_text: "Login";
				btn_text_color: rootWindow.secondary_text_color;
				btn_font_pixel_size: rootWindow.pixel_font_size_24
			}
		}
	}

	DropShadow {
		anchors.fill: auth_rect
		source: auth_rect
		samples: 65
		radius: 32
		spread: 0
		color: "#cc000000"
	}
}

