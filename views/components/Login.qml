import QtQuick 2.15
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
				id: login_email
				hint: "email@example.com";
				width: 17*rootWindow.pixel_font_size_24
			}
			MyEditText{
				id: login_password
				hint: "Password";
				echo_mode: TextInput.Password;
				width: 17*rootWindow.pixel_font_size_24
			}
			Text {
				id: output
				text: qsTr("");
				color: rootWindow.critical_button_color;
				font.pixelSize: pixel_font_size_24
			}

			MyButton{
				btn_text: "Login";
				btn_text_color: rootWindow.secondary_text_color;
				btn_font_pixel_size: rootWindow.pixel_font_size_24;
				Keys.onEnterPressed: _auth.login( login_email.text_data, login_password.text_data );
				MouseArea {
					anchors.fill: parent
					onClicked: {
						busy_indicator_popup.open()
						_auth.login( login_email.text_data.toString(), login_password.text_data.toString() );
					}
				}

				Connections {
					target: _auth;
					function onLogedIn(r) {
						txt_notification_text = r
						if (!txt_notification_text.length) {
							login_email.text_data = "";
							login_password.text_data = "";
							stack.pop(null);
							busy_indicator_popup.close();
							stack.push(s_v_component);
							txt_notification_text = _organization_list.refresh();
							if (!txt_notification_text.length) {
								txt_notification_text = "Please select organization in Organizations tab from Organization's list"
								txt_popup_col = red_color
							}
							return;
						}
						busy_indicator_popup.close();
					}
				}
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


/*##^##
Designer {
		D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
