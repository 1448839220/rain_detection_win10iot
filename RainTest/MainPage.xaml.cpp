//第25课 配套示例程序
//http://www.mineserver.top

//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace App1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Devices::Gpio;

GpioController ^控制器;
GpioPin ^传感器针,^LED针;
const int 传感器针脚号 = 6, LED针脚号=5;

MainPage::MainPage()
{
	InitializeComponent();
	控制器 = 控制器->GetDefault();
	传感器针 = 控制器->OpenPin(传感器针脚号);
	LED针 = 控制器->OpenPin(LED针脚号);
	传感器针->SetDriveMode(GpioPinDriveMode::InputPullUp);
	LED针->SetDriveMode(GpioPinDriveMode::Output);

}


void App1::MainPage::button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto 传感器针电平 = 传感器针->Read();
	if (传感器针电平 == GpioPinValue::Low) {
		auto 红笔刷 = ref new SolidColorBrush(Windows::UI::Colors::Red);
		ellipse->Fill = 红笔刷;
		textBlock->Text = "检测到雨水";
		LED针->Write(GpioPinValue::Low);
	}
	else {
		auto 灰笔刷 = ref new SolidColorBrush(Windows::UI::Colors::Gray);
		ellipse->Fill = 灰笔刷;
		textBlock->Text = "天气晴朗";
		LED针->Write(GpioPinValue::High);
	}

}
