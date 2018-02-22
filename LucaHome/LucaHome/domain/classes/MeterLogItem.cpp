#include "MeterLogItem.h"

MeterLogItem::MeterLogItem()
{
	MeterLogItem("", "", "", "", "", 0, "", time(0));
}

MeterLogItem::MeterLogItem(
	string uuid,
	string roomUuid,
	string typeUuid,
	string type,
	string meterId,
	double value,
	string imageName,
	time_t saveDateTime)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_typeUuid = typeUuid;
	_type = type;
	_meterId = meterId;
	_value = value;
	_imageName = imageName;
	_saveDateTime = saveDateTime;
}

MeterLogItem::~MeterLogItem()
{
}

void MeterLogItem::SetUuid(string uuid)
{
	_uuid = uuid;
}

string MeterLogItem::GetUuid()
{
	return _uuid;
}

void MeterLogItem::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string MeterLogItem::GetRoomUuid()
{
	return _roomUuid;
}

void MeterLogItem::SetTypeUuid(string typeUuid)
{
	_typeUuid = typeUuid;
}

string MeterLogItem::GetTypeUuid()
{
	return _typeUuid;
}

void MeterLogItem::SetType(string type)
{
	_type = type;
}

string MeterLogItem::GetType()
{
	return _type;
}

void MeterLogItem::SetMeterId(string meterId)
{
	_meterId = meterId;
}

string MeterLogItem::GetMeterId()
{
	return _meterId;
}

void MeterLogItem::SetValue(double value)
{
	_value = value;
}

double MeterLogItem::GetValue()
{
	return _value;
}

void MeterLogItem::SetImageName(string imageName)
{
	_imageName = imageName;
}

string MeterLogItem::GetImageName()
{
	return _imageName;
}

void MeterLogItem::SetSaveDateTime(time_t saveDateTime)
{
	_saveDateTime = saveDateTime;
}

time_t MeterLogItem::GetSaveDateTime()
{
	return _saveDateTime;
}

string MeterLogItem::JsonString()
{
	string str =
		string("{")
		+ string("\"MeterLogItem\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"TypeUuid\":\"") + _typeUuid + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"MeterId\":\"") + _meterId + string("\",")
		+ string("\"Value\":") + Tools::ConvertDoubleToStr(_value) + string(",")
		+ string("\"ImageName\":\"") + _imageName + string("\",")
		+ string("\"SaveDateTime\":") + Tools::ConvertIntToStr(_saveDateTime)
		+ string("}")
		+ string("}");
	return str;
}

string MeterLogItem::ToString()
{
	string str =
		string("MeterLogItem { uuid: ") + _uuid
		+ string("; roomUuid: ") + _roomUuid
		+ string("; typeUuid: ") + _typeUuid
		+ string("; type: ") + _type
		+ string("; meterId: ") + _meterId
		+ string("; value: ") + Tools::ConvertDoubleToStr(_value)
		+ string("; imageName: ") + _imageName
		+ string("; saveDateTime: ") + Tools::ConvertIntToStr(_saveDateTime)
		+ string(" }");
	return str;
}
