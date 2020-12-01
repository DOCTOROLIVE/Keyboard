#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* Extern variables ---------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
/* Private functions --------------------------------------------------------- */

/* USB Standard Device Descriptor */
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] = {
	0x12, /* bLength */ USB_DEVICE_DESCRIPTOR_TYPE, /* bDescriptorType */ 0x00,
	/* bcdUSB */ 0x02, 0x00, /* bDeviceClass */ 0x00,
	/* bDeviceSubClass */ 0x00, /* bDeviceProtocol */ 0x40,
	/* bMaxPacketSize40 */ 0x93, /* idVendor (0x0483) */ 0x19, 0x03,
	/* idProduct = 0x5710 */ 0x11, 0x00, /* bcdDevice rel. 2.00 */ 0x02, 1,
	/* Index of string descriptor describing manufacturer */ 2,
	/* Index of string descriptor describing product */ 3,
	/* Index of string descriptor describing the device serial number */ 0x01
		/* bNumConfigurations */ }; /* Joystick_DeviceDescriptor */

/* USB Configuration Descriptor */
/* All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] = {
	0x09, /* bLength: Configuation Descriptor size */
	USB_CONFIGURATION_DESCRIPTOR_TYPE,
	/* bDescriptorType: Configuration */ JOYSTICK_SIZ_CONFIG_DESC,
	/* wTotalLength: Bytes returned */ 0x00, 0x01,
	/* bNumInterfaces: 1 interface */ 0x01,
	/* bConfigurationValue: Configuration value */ 0x00,
	/* iConfiguration: Index of string descriptor describing
	 the configuration */ 0xC0, /* bmAttributes: self powered */ 0x32,
	/* MaxPower 100 mA: this current is used for detecting Vbus */
	// ����Ϊ�ӿ�������
	/************** Descriptor of Joystick Mouse interface *************** */
	/* 09 */ 0x09,
	/* bLength: Interface Descriptor size */ USB_INTERFACE_DESCRIPTOR_TYPE,
	/* bDescriptorType: Interface descriptor type */ 0x00,
	/* bInterfaceNumber: Number of Interface */ 0x00,
	/* bAlternateSetting: Alternate setting */ 0x02, /* bNumEndpoints */ 0x03,
	/* bInterfaceClass: HID */ 0x01,
	/* bInterfaceSubClass : 1=BOOT, 0=no boot */ 0x01,
	/* bInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */ 0,
	/* iInterface: Index of string descriptor */
	// ����ΪHID������
	/******************** Descriptor of Joystick Mouse HID ******************* */
	/* 18 */ 0x09, /* bLength: HID Descriptor size */ HID_DESCRIPTOR_TYPE,
	/* bDescriptorType: HID */ 0x00,
	/* bcdHID: HID Class Spec release number */ 0x01, 0x00,
	/* bCountryCode: Hardware target country */ 0x01,
	/* bNumDescriptors: Number of HID class descriptors to follow */ 0x22,
	/* bDescriptorType */ JOYSTICK_SIZ_REPORT_DESC,
	/* wItemLength: Total length of Report descriptor */ 0x00,

	// ����Ϊ����˵�1������
	/******************** Descriptor of Joystick Mouse endpoint ******************* */
	/* 27 */ 0x07,
	/* bLength: Endpoint Descriptor size */ USB_ENDPOINT_DESCRIPTOR_TYPE,
	/* bDescriptorType: */ 0x81,
	/* bEndpointAddress: Endpoint Address (IN) */ 0x03,
	/* bmAttributes: Interrupt endpoint */ 0x08,
	/* wMaxPacketSize: 8 Byte max */ 0x00, 0x20,
	/* bInterval: Polling Interval (32 ms) */
	// ����Ϊ����˵�1������
	/* 34 */ 0x07,
	/* bLength: Endpoint Descriptor size */ USB_ENDPOINT_DESCRIPTOR_TYPE,
	/* bDescriptorType: */ 0x01,
	/* bEndpointAddress: Endpoint Address (OUT) */ 0x03,
	/* bmAttributes: Interrupt endpoint */ 0x08,
	/* wMaxPacketSize: 8 Byte max */ 0x00, 0x20}; /* MOUSE_ConfigDescriptor */

const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] = {
	0x05, 0x01, // USAGE_PAGE (Generic Desktop)
//��ʾ��;Ϊ����
0x09, 0x06, // USAGE (Keyboard)

//��ʾӦ�ü��ϣ�����Ҫ��END_COLLECTION����������������END_COLLECTION
0xa1, 0x01, // COLLECTION (Application)

//��ʾ��;ҳΪ����
0x05, 0x07, // USAGE_PAGE (Keyboard)
//��;��Сֵ������Ϊ��ctrl��
0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
//��;���ֵ������Ϊ��GUI������window��
0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
//�߼���СֵΪ0
0x15, 0x00, // LOGICAL_MINIMUM (0)
//�߼����ֵΪ1
0x25, 0x01, // LOGICAL_MAXIMUM (1)
//�����С��������ֶεĿ�ȣ�Ϊ1bit������ǰ����߼���СֵΪ0���߼����ֵΪ1
0x75, 0x01, // REPORT_SIZE (1)
//����ĸ���Ϊ8�����ܹ���8��bits
0x95, 0x08, // REPORT_COUNT (8)
//�����ã�������ֵ������ֵ�����������һ�㱨�����ֵ��
//������ƶ��������򱨸����ֵ����ʾ����ƶ�����
0x81, 0x02, // INPUT (Data,Var,Abs)
//�������⼸��������һ�������õ��ֶΣ��ܹ�Ϊ8��bits��ÿ��bit��ʾһ������
//�ֱ����ctrl������GUI������8��bits�պù���һ���ֽڣ���λ�ڱ���ĵ�һ���ֽڡ�
//�������λ����bit-0��Ӧ����ctrl����������ص����ݸ�λΪ1�����ʾ��ctrl�������£�
//������ctrl��û�а��¡����λ����bit-7��ʾ��GUI���İ���������м�ļ���λ��
//��Ҫ����HIDЭ���й涨����;ҳ��HID Usage Tables����ȷ��������ͨ��������ʾ
//�����������ctrl��shift��del����

//���������ݶθ���Ϊ1
0x95, 0x01, // REPORT_COUNT (1)
//ÿ���γ���Ϊ8bits
0x75, 0x08, // REPORT_SIZE (8)
//�����ã�������ֵ������ֵ
0x81, 0x03, // INPUT (Cnst,Var,Abs)

//������8��bit�ǳ������豸���뷵��0

//���������ݶθ���Ϊ5
0x95, 0x05, // REPORT_COUNT (5)
//ÿ���δ�СΪ1bit
0x75, 0x01, // REPORT_SIZE (1)
//��;��LED�����������Ƽ����ϵ�LED�õģ���������˵�����������
0x05, 0x08, // USAGE_PAGE (LEDs)
//��;��Сֵ��Num Lock�������ּ�������
0x19, 0x01, // USAGE_MINIMUM (Num Lock)
//��;���ֵ��Kana�������ʲô����Ҳ�����^_^
0x29, 0x05, // USAGE_MAXIMUM (Kana)
//��ǰ����˵������ֶ�������õģ���������LED��������ֵ������ֵ��
//1��ʾ������0��ʾ����
0x91, 0x02, // OUTPUT (Data,Var,Abs)
//���������ݶθ���Ϊ1
0x95, 0x01, // REPORT_COUNT (1)
//ÿ���δ�СΪ3bits
0x75, 0x03, // REPORT_SIZE (3)
//����ã�������ֵ������
0x91, 0x03, // OUTPUT (Cnst,Var,Abs) 
//����Ҫ���ֽڶ��룬��ǰ�����LED��ֻ����5��bit��
//���Ժ�����Ҫ����3������bit������Ϊ������

//�������Ϊ6
0x95, 0x06, // REPORT_COUNT (6)
//ÿ���δ�СΪ8bits
0x75, 0x08, // REPORT_SIZE (8)
//�߼���Сֵ0
0x15, 0x00, // LOGICAL_MINIMUM (0)
//�߼����ֵ255
0x25, 0xFF, // LOGICAL_MAXIMUM (255)
//��;ҳΪ����
0x05, 0x07, // USAGE_PAGE (Keyboard)
//ʹ����СֵΪ0
0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
//ʹ�����ֵΪ0x65
0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
//�����ã����������飬����ֵ
0x81, 0x00, // INPUT (Data,Ary,Abs)
//���϶�����6��8bit������飬ÿ��8bit����һ���ֽڣ�������ʾһ�����������Կ���ͬʱ
//��6���������¡�û�а�������ʱ��ȫ������0��������µļ�̫�࣬���¼���ɨ��ϵͳ
//�޷����ְ���ʱ����ȫ������0x01����6��0x01�������һ�������£�����6���ֽ��еĵ�һ
//���ֽ�Ϊ��Ӧ�ļ�ֵ�������ֵ�ο�HID Usage Tables����������������£����1��2����

//	0x05, 0x01, // USAGE_PAGE (Generic Desktop)
//	0x09, 0x06, // USAGE (Keyboard)
//	0xa1, 0x01, // COLLECTION (Application)
//	0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)
//	0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
//	0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
//	0x15, 0x00, // LOGICAL_MINIMUM (0)
//	0x25, 0x01, // LOGICAL_MAXIMUM (1)
//	0x95, 0x08, // REPORT_COUNT (8)
//	0x75, 0x01, // REPORT_SIZE (1)
//	0x81, 0x02, // INPUT (Data,Var,Abs)
//	0x95, 0x01, // REPORT_COUNT (1)
//	0x75, 0x08, // REPORT_SIZE (8)
//	0x81, 0x03, // INPUT (Cnst,Var,Abs)
//	0x95, 0x06, // REPORT_COUNT (6)
//	0x75, 0x08, // REPORT_SIZE (8)
//	0x25, 0xFF, // LOGICAL_MAXIMUM (255)
//	0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
//	0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
//	0x81, 0x00, // INPUT (Data,Ary,Abs)
//	0x25, 0x01, // LOGICAL_MAXIMUM (1)
//	0x95, 0x05, // REPORT_COUNT (5)
//	0x75, 0x01, // REPORT_SIZE (1)
//	0x05, 0x08, // USAGE_PAGE (LEDs)
//	0x19, 0x01, // USAGE_MINIMUM (Num Lock)
//	0x29, 0x02, // USAGE_MAXIMUM (Caps Lock)
//	0x91, 0x02, // OUTPUT (Data,Var,Abs)
//	0x95, 0x01, // REPORT_COUNT (1)
//	0x75, 0x06, // REPORT_SIZE (6)
//	0x91, 0x03, // OUTPUT (Cnst,Var,Abs)
	0xc0 // END_COLLECTION
}; /* Joystick_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] = {
	JOYSTICK_SIZ_STRING_LANGID, USB_STRING_DESCRIPTOR_TYPE, 0x09, 0x04
}; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] = {
	JOYSTICK_SIZ_STRING_VENDOR,
	/* Size of Vendor string */ USB_STRING_DESCRIPTOR_TYPE,
	/* bDescriptorType */
	/* Manufacturer: "STMicroelectronics" */ 'S', 0, 'T', 0, 'M', 0, 'i', 0,
	'c', 0, 'r', 0, 'o', 0, 'e', 0, 'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o',
	0, 'n', 0, 'i', 0, 'c', 0, 's', 0};

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] = {
	JOYSTICK_SIZ_STRING_PRODUCT, /* bLength */ USB_STRING_DESCRIPTOR_TYPE,
	/* bDescriptorType */ 'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'K',
	0, 'e', 0, 'y', 0, 'B', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0};
uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] = {
	JOYSTICK_SIZ_STRING_SERIAL, /* bLength */ USB_STRING_DESCRIPTOR_TYPE,
	/* bDescriptorType */ 'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*** */
