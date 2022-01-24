import QtQuick 2.15
import QtQuick.Controls 2.15

//Rectangle {
//	property var lv_model
//	property bool view_btn_item: false
//	property bool sell_btn_item: false

//	color: rootWindow.primary_color
//	radius: rootWindow.pixel_font_size * 10
//	width: rootWindow.pixel_font_size * 540
//	anchors{
//		bottom:  parent.bottom
//		bottomMargin: rootWindow.pixel_font_size*20
//	}

	ListView {
		property bool view_btn_item: false
		property bool sell_btn_item: false

		id: lv
		anchors.topMargin: rootWindow.pixel_font_size * 20
		anchors.bottomMargin: rootWindow.pixel_font_size * 20
		cacheBuffer: rootWindow.pixel_font_size * 40
		spacing: rootWindow.pixel_font_size*6
		clip: true

		ScrollBar.vertical: ScrollBar{  }

		delegate: ItemDelegate{
			padding: 0
			width: lv.width
			implicitWidth: lvd_row.implicitWidth
			implicitHeight: lvd_row.implicitHeight
			Row {
				id: lvd_row
				anchors.centerIn: parent
				spacing: rootWindow.pixel_font_size * 10
				Text {
					readonly property int vibtnw: view_item_btn.visible ? view_item_btn.width : 0
					readonly property int sibtnw: sell_item_btn.visible ? sell_item_btn.sibw : 0
					width: lv.width - vibtnw - sibtnw - 100*rootWindow.pixel_font_size
					height: parent.height
					text: model.name
					font.pixelSize: rootWindow.pixel_font_size_24
					elide: Text.ElideLeft
					verticalAlignment: Text.AlignVCenter
					horizontalAlignment: Text.AlignLeft
					color: rootWindow.primary_text_color
				}
				Image {
					id: view_item_btn;
					source: "qrc:/icons/icons/view 1.svg";
					visible: view_btn_item;
					width: rootWindow.pixel_font_size * sourceSize.width/2
					height: rootWindow.pixel_font_size * sourceSize.height/2
					anchors.verticalCenter: lvd_row.verticalCenter
				}
				Image {
					readonly property int sibw: width
					id: sell_item_btn;
					source: "qrc:/icons/icons/sell-label 1.svg";
					visible: sell_btn_item;
					width: rootWindow.pixel_font_size * sourceSize.width/2
					height: rootWindow.pixel_font_size * sourceSize.height/2
					anchors.verticalCenter: lvd_row.verticalCenter
				}
			}

			hoverEnabled: true

			background: Rectangle {
				anchors.fill: lvd_row;
				color: parent.hovered?secondary_color:primary_color
			}
		}

	}

//}


